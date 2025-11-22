#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"

int main(void) {

    const int largura_tela = 1920;
    const int altura_tela = 1080;
    InitWindow(largura_tela, altura_tela, "Chaves: em busca da chave perdida");

    SetTargetFPS(60);

    int tela_atual = 0;

    InitAudioDevice();

    while (!WindowShouldClose())
    {
        
        if (tela_atual == 0)
        {
            /* code */
            tela_atual = rodarMenu(largura_tela, altura_tela);

        } else if (tela_atual == 1) {
            
            tela_atual = rodar_creditos(largura_tela, altura_tela);

        } else if (tela_atual == 2) {

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