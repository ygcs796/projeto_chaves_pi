#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "vila.h"
#include "player.h"

Acao_tomada executar_vila() {

    Acao_tomada acao_tomada = erro; // coloca como erro para caso nada seja selecionado
    bool selecionado = false;

    Vector2 pos_chaves = {960, 540};
    float velocidade_chaves = 20.0f;

    Player chaves;
    setarjogador(&chaves, pos_chaves, velocidade_chaves);

    while (!selecionado && !WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) { // flag e encerramento da janela

        atualizarjogador(&chaves);

        Rectangle porta_dona_florinda = { 1150, 510, 100, 100 }; // seta a colisao da porta da dona florinda

        if (CheckCollisionRecs(porta_dona_florinda, chaves.hitbox)) { // verifica se a colisao com a porta da dona florinda ocorreu
            acao_tomada = porta_florinda;
            selecionado = true;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(chaves.pos, 50, MAROON);     // jogador
            DrawCircle(1200, 560, 50, GREEN);        // porta
            DrawRectangleLines(chaves.hitbox.x, chaves.hitbox.y, chaves.hitbox.width, chaves.hitbox.height, BLUE);
            DrawRectangleLines(porta_dona_florinda.x, porta_dona_florinda.y, porta_dona_florinda.width, porta_dona_florinda.height, BLUE);

        EndDrawing();
    }

    return acao_tomada;
}
