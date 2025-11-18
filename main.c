#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "./arquivos_h/estadojogo.h"

int main(void) {

    const int largura_tela = 1920;
    const int altura_tela = 1080;
    InitWindow(largura_tela, altura_tela, "Chaves: em busca da chave perdida");

    SetTargetFPS(60);

    EstadoJogo tela_atual = MENU;

    InitAudioDevice();

    while (!WindowShouldClose())
    {
        
        if (tela_atual == MENU)
        {
            /* code */
            tela_atual = rodarMenu(largura_tela, altura_tela);

        } else if (tela_atual == CREDITOS) {
            
            tela_atual = rodar_creditos(largura_tela, altura_tela);

        } else if (tela_atual == GAMEPLAY) {

            if (IsKeyPressed(KEY_ENTER))
            {
                /* code */
                tela_atual = 0;

            }
            
            
            BeginDrawing();

                ClearBackground(RAYWHITE);
                DrawText("TELA DE GAMEPLAY", 900, altura_tela/2, 30, BLACK);

            EndDrawing();

        }

    }
    
    CloseWindow();

    return 0;
}