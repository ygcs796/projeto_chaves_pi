#include <stdio.h>
#include "player.h"
#include "raylib.h"
#include "raymath.h"

void atualizarjogador(Player *p, Rectangle* barreiras, int quant_barreiras) {

    if (p->isMoving)
    { // condição que não aceita entradas do teclado enquanto a movimentação de 1 bloco não acabar
        /* code */
        p->moveTimer += GetFrameTime();
        
        float progress = p->moveTimer / p->moveTime;
        if (progress > 1.0f) progress = 1.0f;
        
        p->pos = Vector2Lerp(p->startPos, p->targetPos, progress);
        
        // SINCRONIZAÇÃO DA ANIMAÇÃO COM O MOVIMENTO
        if (progress < (1.0f / 2.0f))
        {
            /* code */
            // verificação para variar as pernas a cada andada do Chaves
            if (p->pernaParaAndar == 1)
            {
                /* code */
                p->frameAtual = 1;
                
            } else {
                
                p->frameAtual = 3;
                
            }
        } else if (progress < 1.0f){
            
            p->frameAtual = 0; // Chaves parado;
            
        } else if (progress == 1.0f) { // quando o Chaves tiver acabado o movimento de 1 bloco para uma direção definida
            p->pos = p->targetPos;
            p->isMoving = false;
            p->moveTimer = 0.0f;
            
            
            // decidi a próxima perna (sprite) do movimento do Chaves
            if (p->pernaParaAndar == 1)
            {
                /* code */
                p->pernaParaAndar = 2;
                
            } else {
                
                p->pernaParaAndar = 1;
                
            }
            
            
        } 
        
    } else {
        
        // p->startPos = p->pos;
        
        // criando variáveis para verificar se haverá colisão entre a futura posição do chaves e alguma barrreira de movimentação
        Vector2 proximaPosicaoCandidata = p->pos;
        DirecaoJogador proximaDirecao = p->direcao;

        // avalia o movimento do jogador e define a direção dele
        if (IsKeyDown(KEY_RIGHT)) {
            // p->targetPos.x = p->pos.x + p->tileSize;
            // p->direcao = DIREITA;
            // p->isMoving = true;

            proximaDirecao = DIREITA;
            proximaPosicaoCandidata.x += p->tileSize;

        } else if (IsKeyDown(KEY_LEFT)){
            // p->targetPos.x = p->pos.x - p->tileSize;
            // p->direcao = ESQUERDA;
            // p->isMoving = true;

            proximaDirecao = ESQUERDA;
            proximaPosicaoCandidata.x -= p->tileSize;

        } else if (IsKeyDown(KEY_UP)){
            // p->targetPos.y = p->pos.y - p->tileSize;
            // p->direcao = CIMA;
            // p->isMoving = true;    

            proximaDirecao = CIMA;
            proximaPosicaoCandidata.y -= p->tileSize;

        } else if (IsKeyDown(KEY_DOWN)){
            // p->targetPos.y = p->pos.y + p->tileSize;
            // p->direcao = BAIXO;
            // p->isMoving = true;

            proximaDirecao = BAIXO;
            proximaPosicaoCandidata.y += p->tileSize;

        }
        
        // LÓGICA DE COLISÃO
        if (proximaPosicaoCandidata.x != p->pos.x || proximaPosicaoCandidata.y != p->pos.y) { // caso alguma tecla tenha sido pressionada;

            // criando uma hitbox temporária da próxima posição do Chaves
            Rectangle proximaHitbox = {
                proximaPosicaoCandidata.x - (p->hitbox.width / 2),
                proximaPosicaoCandidata.y - (p->hitbox.height / 2),
                p->hitbox.width,
                p->hitbox.height
            };

            bool colidiu = false;

            // FOR para verificar se ele colidiu com algum dos retângulos da array que foi passada como parâmetro
            for (int i = 0; (i < quant_barreiras) && (!colidiu); i++) {

                if(CheckCollisionRecs(proximaHitbox, barreiras[i])) {
                    
                    colidiu = true; // se o jogador colidir com qualquer uma das barreiras, o FOR vai quebrar (sem usar break)
                    
                }

            }

            if (!colidiu) { // caso NÃO HAJA COLISÃO
                p->direcao = proximaDirecao;
                p->startPos = p->pos;
                p->targetPos = proximaPosicaoCandidata;
                p->isMoving = true;
                p->moveTimer = 0.0f;
                p->frameAtual = 1; //TODO verificar se isso aqui dá certo

            } else { // caso HAJA COLISÃO

                p->frameAtual = 0; // player parado

            }

        } else { // caso nenhuma tecla seja clicada

            p->frameAtual = 0; // player parado
            
        }
            


    }
    
    // atualiza a hitbox(centralizada)
    p->hitbox.x = p->pos.x - p->hitbox.width / 2;
    p->hitbox.y = p->pos.y - p->hitbox.height / 2;
}
    
void setarjogador(Player *p, Vector2 pos) {
    p->pos = pos;
    p->precisa_ficar_parado = false;

    // CARREGAMENTO DA IMAGEM DOS SPRITES E CONFIG DAS DIMENSÕES DE 1 ÚNICO FRAME
    p->imagemSprites = LoadImage("imagens/chavinho_movimentacao.png");
    p->texSprites = LoadTextureFromImage(p->imagemSprites);
    p->larguraFrame = 160;
    p->alturaFrame = 200;

    // Configuração da animação
    p->direcao = BAIXO;
    p->frameAtual = 0; // frame inicial/base (Chaves parado)
    p->pernaParaAndar = 1;

    // Define o tamanho da hitbox
    p->hitbox.width = (float) p->larguraFrame;
    p->hitbox.height = (float) p->alturaFrame / 10;

    // Ajusta hitbox ao centro do player
    p->hitbox.x = pos.x - p->hitbox.width / 2;
    p->hitbox.y = pos.y;

    // INICIALIZAÇÃO DO MOVIMENTO POR BLOCOS
    p->isMoving = false;
    p->targetPos = pos;
    p->moveTimer = 0.0f;
    p->moveTime = 0.5f;
    p->tileSize = p->larguraFrame * 0.75;
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
