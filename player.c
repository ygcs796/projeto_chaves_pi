#include "player.h"
#include "raylib.h"
#include "raymath.h"

void atualizarjogador(Player *p) {
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

        p->startPos = p->pos;

        // avalia o movimento do jogador e define a direção dele
        if (IsKeyDown(KEY_RIGHT)) {
            p->targetPos.x = p->pos.x + p->tileSize;
            p->direcao = DIREITA;
            p->isMoving = true;
        } else if (IsKeyDown(KEY_LEFT)){
            p->targetPos.x = p->pos.x - p->tileSize;
            p->direcao = ESQUERDA;
            p->isMoving = true;
        } else if (IsKeyDown(KEY_UP)){
            p->targetPos.y = p->pos.y - p->tileSize;
            p->direcao = CIMA;
            p->isMoving = true;    
        } else if (IsKeyDown(KEY_DOWN)){
            p->targetPos.y = p->pos.y + p->tileSize;
            p->direcao = BAIXO;
            p->isMoving = true;
        }

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
    p->alturaFrame = 200;

    // Configuração da animação
    p->direcao = BAIXO;
    p->contadorFrame = 0;
    p->velocidadeFrame = velocidade; 
    p->frameAtual = 0; // frame inicial/base (Chaves parado)
    p->pernaParaAndar = 1;

    // Define o tamanho da hitbox
    p->hitbox.width = (float) p->larguraFrame;
    p->hitbox.height = (float) p->alturaFrame;

    // Ajusta hitbox ao centro do player
    p->hitbox.x = pos.x - p->hitbox.width / 2;
    p->hitbox.y = pos.y - p->hitbox.height / 2;

    // INICIALIZAÇÃO DO MOVIMENTO POR BLOCOS
    p->isMoving = false;
    p->targetPos = pos;
    p->moveTimer = 0.0f;
    p->moveTime = 0.5f;
    p->tileSize = p->larguraFrame; 
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
    // DrawRectangleLinesEx(p->hitbox, 1, RED);

}

void descarregarjogador(Player *p) {
    UnloadImage(p->imagemSprites);
}
