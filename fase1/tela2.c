#include <stdio.h>
#include "raylib.h"
#include "fase1.h"

#define LARGURA_BASE 1920
#define ALTURA_BASE 1080


void executar_2(Pizza pizza){

    Texture2D fundo = LoadTexture("imagens/fogao_fase1.png");

    float tempo_inicial = GetTime();
    float tempo_atual = GetTime();
    float tempo_cronometro = tempo_atual - tempo_inicial;
    bool botao_pressionado = false;

    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE;

    Rectangle botao_parar_cozimento = {1000 * escala_x, 1000 * escala_y, 80 * escala_x, 80 * escala_y};
    
    while(!WindowShouldClose && !botao_pressionado){
        tempo_cronometro = tempo_atual - tempo_inicial;

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangleRec(botao_parar_cozimento, GREEN);

        EndDrawing();
    }
}