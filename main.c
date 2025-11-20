#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "player.h"
#include "vila.h"
#include "fase1.h"

int main(void) {

    const int largura_tela = 1920; //GetMonitorWidth(0);  1366;
    const int altura_tela =  1080; //GetMonitorHeight(0); 768;
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

            /*if (IsKeyPressed(KEY_ENTER))
            {
                 code
                tela_atual = 0;

            }*/

            Fase_selecionada fase_selecionada = executar_vila(); // executa a  vila e retorna um enum Fase_selcionada do arquivo vila.h
            printf("porta selecionada: %d", fase_selecionada);

            if (fase_selecionada == porta_florinda){
                Executar_fase_1();
            }
            
    
            
            /*BeginDrawing();

                ClearBackground(RAYWHITE);

            EndDrawing();*/

        }

    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}