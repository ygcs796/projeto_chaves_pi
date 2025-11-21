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

    // carregamento do mapa
    Image imagem_vila = LoadImage("imagens/mapa_vila.png");
    Texture2D mapa_vila = LoadTextureFromImage(imagem_vila);
    UnloadImage(imagem_vila); // liberando a imagem da RAM
    
    // inicialização da câmera 2D
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 1920 / 2.0f, 1080 / 2.0f }; //TODO mudar o 1920 e o 1080 para variáveis de largura e altura da tela
    camera.target = chaves.pos; // a câmera mira na posição do Chaves
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!selecionado && !WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) { // flag e encerramento da janela

        atualizarjogador(&chaves);

        camera.target = chaves.pos;

        Rectangle porta_dona_florinda = { 1150, 510, 100, 100 }; // seta a colisao da porta da dona florinda

        if (CheckCollisionRecs(porta_dona_florinda, chaves.hitbox)) { // verifica se a colisao com a porta da dona florinda ocorreu
            fase_selecionada = porta_florinda;
            selecionado = true;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                // desenhando o mapa
                DrawTexture(mapa_vila, 0, 0, WHITE);

                desenharjogador(&chaves);
                DrawCircle(1200, 560, 50, GREEN);        // porta
                DrawRectangleLines(porta_dona_florinda.x, porta_dona_florinda.y, porta_dona_florinda.width, porta_dona_florinda.height, BLUE);

            EndMode2D();

            DrawText("VILA CENTRAL", 10, 10, 20, BLACK);

        EndDrawing();
    }
    descarregarjogador(&chaves);

    UnloadTexture(mapa_vila);

    return fase_selecionada;
}
