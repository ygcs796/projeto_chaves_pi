#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "vila.h"
#include "player.h"

Fase_selecionada executar_vila() {

    Fase_selecionada fase_selecionada = erro; // coloca como erro para caso nada seja selecionado
    bool selecionado = false;

    Vector2 pos_chaves = {562, 1270};

    Player chaves;
    setarjogador(&chaves, pos_chaves);

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

    // criando a hitbox da porta da dona florinda
    Rectangle porta_dona_florinda = { 1820, 515, 115, 230}; // seta a colisao da porta da dona florinda

    while (!selecionado && !WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)) { // flag e encerramento da janela

        atualizarjogador(&chaves);

        camera.target = chaves.pos;


        if (CheckCollisionRecs(porta_dona_florinda, chaves.hitbox) && !(selecionado)) { // verifica se a colisao com a porta da dona florinda ocorreu
            
            chaves.precisa_ficar_parado = true;

            

            if (IsKeyDown(KEY_ENTER)) {

                fase_selecionada = porta_florinda;
                selecionado = true;

            } else if (IsKeyDown(KEY_BACKSPACE)) {

                chaves.pos.y -= chaves.tileSize;

            }
            
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

                // desenhando o mapa
                DrawTexture(mapa_vila, 0, 0, WHITE);

                desenharjogador(&chaves);
                DrawRectangleLinesEx(porta_dona_florinda, 1, RED);        // comando para verificar a hitbox
                DrawRectangleLines(porta_dona_florinda.x, porta_dona_florinda.y, porta_dona_florinda.width, porta_dona_florinda.height, BLUE);

            EndMode2D();

            DrawText("VILA CENTRAL", 10, 10, 20, BLACK);

        EndDrawing();
    }
    descarregarjogador(&chaves);

    UnloadTexture(mapa_vila);

    return fase_selecionada;
}
