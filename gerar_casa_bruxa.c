#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "npc.h"
#include "gerar_bruxa_71.h"
#include "fase1/fase1.h"

int gerar_casa_bruxa(Player* jogador, Camera2D* camera) {

    bool ganhou_fase_2 = false;
    bool fase_acabou = false;

    // Rectangle hitbox_florinda = {365, 980, jogador->hitbox.width, jogador->hitbox.height};

    NPC bruxa_71;
    
    Image imagem_casa_bruxa = LoadImage("./imagens/casaBruxa.png");
    Texture cenario_casa_bruxa = LoadTextureFromImage(imagem_casa_bruxa);
    UnloadImage(imagem_casa_bruxa);

    // Rectangle barreiras_casa[] = {
    //     {0, 580, 850, 320}, // PAREDE SUPERIOR (até a porta da cozinha)
    //     {0, 580, 45, 1260}, // PAREDE ESQUERDA
    //     {0, 1800, 850, 40}, // PAREDE INFERIOR
    //     {805, 580, 45, 1260}, // PAREDE DIREITA
    //     {216, 1012, 144, 243}, // MESA DA COZINHA
    //     {61, 1006, 66, 222}, // MOVEL DE MADEIRA DA COZINHA
    //     {365, 1041, 40, 140}, // CADEIRA COZINHA (DIREITA)
    //     {250, 935, 75, 75}, // CADEIRA COZINHA (CIMA) 
    //     {260, 1327, 100, 120}, // POLTRONA
    //     {106, 1526, 80, 180}, // SOFÁ
    //     {463, 1550, 55, 100} // MÓVEL DE MADEIRA DA SALA 
    // };

    // const int quant_barreiras_casa = sizeof(barreiras_casa) / sizeof(barreiras_casa[0]);

    Vector2 pos_chaves = {160, 267}; // testando

    setarjogador(jogador, pos_chaves);
    setar_bruxa_71(&bruxa_71);

    jogador->direcao = BAIXO;
    bool cutscene_iniciada = false;

    while(!WindowShouldClose() && !fase_acabou) {
        
        bool colisao_chaves_bruxa = CheckCollisionRecs(jogador->hitbox, bruxa_71.hitbox);

        // 2. ATUALIZE A TRAVA
        // Se colidiu E AINDA NÃO tinha iniciado a cutscene, trava agora.
        if (colisao_chaves_bruxa && !cutscene_iniciada) {
            cutscene_iniciada = true;
            
            // Força a parada imediatamente UMA ÚNICA VEZ
            jogador->frameAtual = 0;
            jogador->interagindo = 1;
            jogador->moveTimer = 0.0f;
            jogador->pernaParaAndar = 0;
        }

        // 3. USE A TRAVA PARA DECIDIR O MOVIMENTO
        // Se a cutscene NÃO foi iniciada, ele pode andar.
        if (!cutscene_iniciada) {
            atualizarjogador(jogador, NULL, 0);
            camera->target = jogador->pos;
        } 
        // Não precisa de 'else' aqui porque a gente já setou as variáveis no passo 2
        
        BeginDrawing();
            ClearBackground(BLACK);
                BeginMode2D(*camera);
                    DrawTexture(cenario_casa_bruxa, 0, 0, WHITE);
                    desenhar_bruxa_71(&bruxa_71, *jogador);
                    desenharjogador(jogador);
                    // ... desenhar hitboxes ...
                EndMode2D();
            DrawText("CASA DA BRUXA DO 71", 10, 10, 20, BLACK);
        EndDrawing();

        // 4. VERIFICA A TRAVA PARA RODAR A PRÓXIMA FASE
        if (cutscene_iniciada) {
            ganhou_fase_2 = Executar_fase_1();
            fase_acabou = true;
        }
    }

    UnloadTexture(cenario_casa_bruxa);

    jogador->interagindo = 0; // para destravar o movimento
    jogador->frameAtual = 0; // reseta visualmente para parado
    jogador->direcao = BAIXO; // para ele olhar para fora da casa quando sair dela

    descarregarjogador(jogador);
    descarregar_bruxa_71(&bruxa_71);

    return ganhou_fase_2;
}
