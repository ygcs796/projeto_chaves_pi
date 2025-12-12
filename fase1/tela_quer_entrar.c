#include "raylib.h"
#include "tela_quer_entrar.h"

int RodarTelaPergunta(int largura, int altura){

    int escolha = 0;
    while(!WindowShouldClose() && escolha == 0){

        if(IsKeyPressed(KEY_Y)){
            escolha = 1;
        }

        else if(IsKeyPressed(KEY_N)){
            escolha = 2;
        }
    
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("Voce esta na casa de Dona Florinda. Deseja continuar nela, entrando para a fase 1?", largura/2, altura/2, 30, WHITE);
    DrawText("Y - vamos para a próxima fase!", largura/2 + 20, altura/2 + 20, 30, WHITE);
    DrawText("N - fica pra próxima!", largura/2 + 40, altura/2 + 40, 30, WHITE);

    EndDrawing();
    }

    return escolha;
}