#include <stdio.h>
#include "player.h"
#include "raylib.h"
#include "raymath.h"

void atualizarjogador(Player *p, Rectangle* barreiras, int quant_barreiras) {
    
    Vector2 movimento = { 0.0f, 0.0f };
    bool estaAndando = false;

    // MOVIMENTAÇÃO SUAVE (CONTÍNUA)
    if (IsKeyDown(KEY_RIGHT)) {
        movimento.x += p->velocidade * GetFrameTime();
        p->direcao = DIREITA;
        estaAndando = true;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        movimento.x -= p->velocidade * GetFrameTime();
        p->direcao = ESQUERDA;
        estaAndando = true;
    }
    else if (IsKeyDown(KEY_UP)) {
        movimento.y -= p->velocidade * GetFrameTime();
        p->direcao = CIMA;
        estaAndando = true;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        movimento.y += p->velocidade * GetFrameTime();
        p->direcao = BAIXO;
        estaAndando = true;
    }

    // COLISÃO EIXO X
    p->hitbox.x += movimento.x; 
    bool colidiuX = false;
    for (int i = 0; i < quant_barreiras; i++) {
        if (CheckCollisionRecs(p->hitbox, barreiras[i])) {
            colidiuX = true;
            break;
        }
    }
    if (colidiuX) {
        p->hitbox.x -= movimento.x; // Desfaz movimento X se bateu
    } else {
        p->pos.x += movimento.x;    // Aplica movimento X se livre
    }

    // COLISÃO EIXO Y
    p->hitbox.y += movimento.y; 
    bool colidiuY = false;
    for (int i = 0; i < quant_barreiras; i++) {
        if (CheckCollisionRecs(p->hitbox, barreiras[i])) {
            colidiuY = true;
            break;
        }
    }
    if (colidiuY) {
        p->hitbox.y -= movimento.y; // Desfaz movimento Y se bateu
    } else {
        p->pos.y += movimento.y;    // Aplica movimento Y se livre
    }

    // ATUALIZAÇÃO DA HITBOX (MANTÉM NOS PÉS)
    float compensacao_x = 0.0f; 
    p->hitbox.x = (p->pos.x - (p->hitbox.width / 2)) + compensacao_x;
    p->hitbox.y = (p->pos.y + p->alturaFrame / 2.0f) - p->hitbox.height;


    // ANIMAÇÃO DE CAMINHADA (CICLO DE 4 PASSOS)
    if (estaAndando) {
        p->moveTimer += GetFrameTime();
        
        // A cada 0.15s troca o frame
        if (p->moveTimer >= 0.15f) { 
            p->moveTimer = 0.0f; 
            
            // Ciclo: 0 -> 1 -> 2 -> 3 -> 0...
            p->pernaParaAndar++; 
            if (p->pernaParaAndar > 3) p->pernaParaAndar = 0;

            // Mapeamento do ciclo para os frames corretos
            switch (p->pernaParaAndar) {
                case 1: p->frameAtual = 1; break; // Perna Esquerda
                case 2: p->frameAtual = 2; break; // Centro
                case 3: p->frameAtual = 3; break; // Perna Direita
                case 0: p->frameAtual = 0; break; // Centro
            }
        }
    } else {
        // Reseta para parado
        p->frameAtual = 0;
        p->pernaParaAndar = 0;
        p->moveTimer = 0.0f;
    }
}


void setarjogador(Player *p, Vector2 pos) {
    p->pos = pos;
    p->precisa_ficar_parado = false;

    // Carregamento
    p->imagemSprites = LoadImage("imagens/chavinho_movimentacao.png");
    p->texSprites = LoadTextureFromImage(p->imagemSprites);
    p->larguraFrame = 160;
    p->alturaFrame = 200;

    // Configuração inicial
    p->direcao = BAIXO;
    p->frameAtual = 0; 
    p->pernaParaAndar = 0; // Inicializa ciclo de animação
    p->moveTimer = 0.0f;   // Inicializa timer
    p->velocidade = 250.0f; // Define velocidade em pixels/segundo

    // Hitbox (Pés)
    p->hitbox.width = 90;
    p->hitbox.height = 50;

    float compensacao_x = 0.0f; // Mesmo valor usado no update!
    p->hitbox.x = (pos.x - (p->hitbox.width / 2)) + compensacao_x;
    p->hitbox.y = (pos.y + p->alturaFrame / 2.0f) - p->hitbox.height;
    
    p->isMoving = false; 
}


void desenharjogador(Player *p) {

    // definindo a área que vou pegar na imagem dos sprites
    Rectangle FonteRec = {
        (float)p->frameAtual * p->larguraFrame,
        (float)p->direcao * p->alturaFrame,
        (float)p->larguraFrame,
        (float)p->alturaFrame
    };

    // definindo onde vou desenhar na tela
    Rectangle destinoRec = {
        p->pos.x,
        p->pos.y,
        (float)p->larguraFrame,
        (float)p->alturaFrame
    };

    // criando um vetor 2D para que o programe sempre desenhe o player pelo centro
    Vector2 origem = {destinoRec.width / 2, destinoRec.height / 2};

    DrawTexturePro(p->texSprites, FonteRec, destinoRec, origem, 0.0f, WHITE);

    // desenhando a hitbox para debugar
    DrawRectangleLinesEx(p->hitbox, 1, RED);

}

void descarregarjogador(Player *p) {
    UnloadImage(p->imagemSprites);
}
