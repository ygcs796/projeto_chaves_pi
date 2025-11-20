#include "player.h"
#include "raylib.h"

void atualizarjogador(Player *p) {
    bool JogadorSeMovendo = false;

    // avalia o movimento do jogador
    if (IsKeyDown(KEY_RIGHT)) {
        p->pos.x += p->velocidade;
        p->direcao = DIREITA;
        JogadorSeMovendo = true;
    }
    if (IsKeyDown(KEY_LEFT)){
        p->pos.x -= p->velocidade;
        p->direcao = ESQUERDA;
        JogadorSeMovendo = true;
    }
    if (IsKeyDown(KEY_UP)){
        p->pos.y -= p->velocidade;
        p->direcao = CIMA;
        JogadorSeMovendo = true;    
    }
    if (IsKeyDown(KEY_DOWN)){
        p->pos.y += p->velocidade;
        p->direcao = BAIXO;
        JogadorSeMovendo = true;
    }

    // LÓGICA DE ANIMAÇÃO
    if (JogadorSeMovendo) {

        p->contadorFrame++;

        // lógica da mudança de quadros ao longo do tempo
        if (p->contadorFrame >= (60 / p->velocidadeFrame)) {

            p->contadorFrame = 0;
            p->frameAtual++;
            
            // lógica circular da mudança de frames
            if (p->frameAtual > 3) p->frameAtual = 0;

        }

    } else { // se o jogador estiver parado

        p->frameAtual = 0;
        p->contadorFrame = 0;

    }

    // atualiza a hitbox(centralizada)
    p->hitbox.x = p->pos.x - p->hitbox.width / 2;
    p->hitbox.y = p->pos.y - p->hitbox.height / 2;
}

void setarjogador(Player *p, Vector2 pos, float velocidade) {
    p->pos = pos;
    p->velocidade = velocidade;

    // CARREGAMENTO DA IMAGEM DOS SPRITES E CONFIG DAS DIMENSÕES DE 1 ÚNICO FRAME
    p->imagemSprites = LoadImage("imagens/chavinho_movimentacao.png");
    p->texSprites = LoadTextureFromImage(p->imagemSprites);
    p->larguraFrame = 160;
    p->alturaFrame = 240;

    // Configuração da animação
    p->direcao = BAIXO;
    p->contadorFrame = 0;
    p->velocidadeFrame = velocidade * 2; 
    p->frameAtual = 0; // frame inicial/base (Chaves parado)

    // Define o tamanho da hitbox
    p->hitbox.width = (float) p->larguraFrame;
    p->hitbox.height = (float) p->alturaFrame;

    // Ajusta hitbox ao centro do player
    p->hitbox.x = pos.x - p->hitbox.width / 2;
    p->hitbox.y = pos.y - p->hitbox.height / 2;
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
