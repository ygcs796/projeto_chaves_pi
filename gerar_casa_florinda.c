#include <stdio.h>
#include "raylib.h"
#include "player.h"

void carregar_casa_florinda(Player jogador, Camera2D camera) {

    Image imagem_casa_florinda = LoadImage("./imagens/casaFlorinda.png");
    Texture cenario_casa_florinda = LoadTextureFromImage(imagem_casa_florinda);
    UnloadImage(imagem_casa_florinda);

    Rectangle barreiras_casa[] = {
        {0, 580, 850, 320}, // PAREDE SUPERIOR (até a porta da cozinha)
        {0, 580, 45, 1260}, // PAREDE ESQUERDA
        {0, 1800, 850, 40}, // PAREDE INFERIOR
        {805, 580, 45, 1260} // PAREDE DIREITA
    };

    const int quant_barreiras_casa = sizeof(barreiras_casa) / sizeof(barreiras_casa[0]);

    Vector2 pos_chaves = {641, 1636}; // testando

    setarjogador(&jogador, pos_chaves);

    jogador.direcao = CIMA;

    while(!WindowShouldClose()) {
        
        
        // entradas do teclado ou atualizações
        atualizarjogador(&jogador, barreiras_casa, quant_barreiras_casa);
        camera.target = jogador.pos;
        

        // desenho

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                DrawTexture(cenario_casa_florinda, 0, 0, WHITE);

                desenharjogador(&jogador);
                
                // desenhando as barreiras da casa para debug
                for (int i = 0; i < quant_barreiras_casa; i++) {

                    DrawRectangleLinesEx(barreiras_casa[i], 2, RED);

                }

            EndMode2D();

            DrawText("CASA DA DONA FLORINDA", 10, 10, 20, BLACK); // testando

        EndDrawing();

    }

    UnloadTexture(cenario_casa_florinda);
    descarregarjogador(&jogador);

}