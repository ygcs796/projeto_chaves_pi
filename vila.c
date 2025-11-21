#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "vila.h"
#include "player.h"

Fase_selecionada executar_vila() {

    Fase_selecionada fase_selecionada = erro; // coloca como erro para caso nada seja selecionado
    bool selecionado = false;

    Vector2 pos_chaves = {960, 540};
    float velocidade_chaves = 1.0f;

    Player chaves;
    setarjogador(&chaves, pos_chaves, velocidade_chaves);

    while (!selecionado && !WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) { // flag e encerramento da janela

        atualizarjogador(&chaves);

        Rectangle porta_dona_florinda = { 1150, 510, 100, 100 }; // seta a colisao da porta da dona florinda

        if (CheckCollisionRecs(porta_dona_florinda, chaves.hitbox)) { // verifica se a colisao com a porta da dona florinda ocorreu
            fase_selecionada = porta_florinda;
            selecionado = true;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            desenharjogador(&chaves);
            DrawCircle(1200, 560, 50, GREEN);        // porta
            DrawRectangleLines(porta_dona_florinda.x, porta_dona_florinda.y, porta_dona_florinda.width, porta_dona_florinda.height, BLUE);

        EndDrawing();
    }
    descarregarjogador(&chaves);

    return fase_selecionada;
}
