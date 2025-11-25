#include <stdio.h>
#include "raylib.h"
#include "player.h"

void carregar_casa_florinda(Player jogador, Camera2D camera) {

    Image imagem_casa_florinda = LoadImage("./imagens/casaFlorinda.png");
    Texture cenario_casa_florinda = LoadTextureFromImage(imagem_casa_florinda);
    UnloadImage(imagem_casa_florinda);

    Vector2 pos_chaves = {641, 1636}; // testando

    setarjogador(&jogador, pos_chaves);

    while(!WindowShouldClose()) {
        
        
        // entradas do teclado ou atualizações
        atualizarjogador(&jogador);
        camera.target = jogador.pos;
        

        // desenho

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                DrawTexture(cenario_casa_florinda, 0, 0, WHITE);

                desenharjogador(&jogador);

            EndMode2D();

            DrawText("CASA DA DONA FLORINDA", 10, 10, 20, BLACK); // testando

        EndDrawing();

    }

    UnloadTexture(cenario_casa_florinda);

}