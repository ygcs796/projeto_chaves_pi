#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "player.h"

int main(void) {

    const int largura_tela = 1920; 
    const int altura_tela = 1080;
    InitWindow(largura_tela, altura_tela, "Chaves: em busca da chave perdida"); // abre a janela

    Vector2 pos_chaves = {960, 540};
    float velocidade_chaves = 20.0f;

    Player chaves;
    setarjogador(&chaves, pos_chaves, velocidade_chaves);

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

        } else if (tela_atual == 2) { // tela de gameplay

            if (IsKeyPressed(KEY_ENTER))
            {
                /* code */
                tela_atual = 0;

            }

            atualizarjogador(&chaves); // atualiza os dados do chaves
            Rectangle porta_florinda = { 1150, 510, 100, 100}; // hitbox da porta da dona florinda
    
            
            BeginDrawing();

                ClearBackground(RAYWHITE);
                
                // -------------------primeiro ambiente
                DrawCircleV(chaves.pos, 50, MAROON); // desenha o personagem chaves
                DrawCircle(1200, 560, 50, GREEN); // desenha a porta da dona florinda
                DrawRectangleLines(chaves.hitbox.x, chaves.hitbox.y, chaves.hitbox.width, chaves.hitbox.height, BLUE); // desenha a hitbox do chaves
                DrawRectangleLines(1150, 510, 100, 100, BLUE); // desenha a hitbox da dona florinda
                if(CheckCollisionRecs(porta_florinda, chaves.hitbox))
                    DrawText("Colidiu", 1000, 560, 30, BLACK); // aviso de colisao
                // --------------------------------

            EndDrawing();

        }

    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}