#include "fase1.h"
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>
#include "tela1main.h"
#include "tela2.h"

void Executar_fase_1() {

    Info_rodada info_rodada;
    info_rodada.vidas = 3;
    info_rodada.dinheiro = 0;
    bool vitoria_parte_2;

    info_rodada = executartela1(info_rodada);

    if (info_rodada.vitoria_parte_1){
        vitoria_parte_2 = executar_tela_2(info_rodada);
        if (vitoria_parte_2){ // se vencer a rodada
            info_rodada.dinheiro += retornar_dinheiro_rodada(info_rodada.pizza_atual.ingredientes); // adiciona o dinheiro pela vitoria
        }else{ // se perder
            info_rodada.vidas--; // retira uma vida
        }
                
    }else // se perder logo na parte1
        info_rodada.vidas--;


    while(!WindowShouldClose() && (info_rodada.vidas > 0 && info_rodada.dinheiro < 100)){ // codicao de derrota && condicao de vitoria
        info_rodada = executartela1(info_rodada);
        if (info_rodada.vitoria_parte_1){
            vitoria_parte_2 = executar_tela_2(info_rodada);
            if (vitoria_parte_2){ // se vencer a rodada
                info_rodada.dinheiro += retornar_dinheiro_rodada(info_rodada.pizza_atual.ingredientes); // adiciona o dinheiro pela vitoria
            }else{ // se perder
                info_rodada.vidas--; // retira uma vida
            }
                    
        }else // se perder logo na parte 1
            info_rodada.vidas--;
    }

    if(info_rodada.vidas == 0)
        printar_derrota();
    else
        printar_vitoria();
    
}

void printar_vitoria() {

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Vitoria!. Aperte ENTER para continuar.", 200, 200, 30, GREEN);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

void printar_derrota() {

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Derrota!. Aperte ENTER para continuar.", 200, 200, 30, RED);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}


