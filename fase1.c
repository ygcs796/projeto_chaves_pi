#include "fase1.h"
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>

void Executar_fase_1() {

    SetRandomSeed(time(NULL));

    bool ingredientes[numero_de_ingredientes] = {false}; // vetor original dos vetores
    bool ingredientes_temp[numero_de_ingredientes] = {false}; // vetor dos ingredientes de cada config aleatoria

    Rectangle botao_queijo    = { 200, 100, 80, 80 };
    Rectangle botao_molho     = { 200, 200, 80, 80 };
    Rectangle botao_calabresa = { 200, 300, 80, 80 };
    Rectangle botao_frango    = { 200, 400, 80, 80 };
    Rectangle botao_cebola    = { 200, 500, 80, 80 };
    Rectangle botao_de_selecao= { 400, 600, 80, 80 };
    
    gerar_config_de_igredientes(ingredientes_temp); // primeira geracao dos ingredientes

    float tempo_base_cronometro = GetTime(); // seta o primeiro tempo no relogio
    float cronometro = 0.0f; // define o cronometro
    bool ganhou = false; // tenho que tirar isso depois
    int vidas = 3;
    bool primeiro_loop = true;
    int dinheiro = 0;
    bool venceu_jogo = false;

    while (!WindowShouldClose() && vidas > 0 && !venceu_jogo) {

        Vector2 mouse = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

            // muda para os estados opostos
            if (CheckCollisionPointRec(mouse, botao_queijo))
                ingredientes[Queijo] = !ingredientes[Queijo];

            else if (CheckCollisionPointRec(mouse, botao_molho))
                ingredientes[Molho_de_tomate] = !ingredientes[Molho_de_tomate];

            else if (CheckCollisionPointRec(mouse, botao_calabresa))
                ingredientes[Calabresa] = !ingredientes[Calabresa];

            else if (CheckCollisionPointRec(mouse, botao_frango))
                ingredientes[Frango] = !ingredientes[Frango];

            else if (CheckCollisionPointRec(mouse, botao_cebola))
                ingredientes[Cebola] = !ingredientes[Cebola];
        }

        if((cronometro < 0.1f || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, botao_de_selecao))) && !primeiro_loop){ // condicoes de encerramento
            ganhou = verificar_vitória(ingredientes, ingredientes_temp);

                if(ganhou){ // se ganhou a rodada
                    dinheiro += retornar_dinheiro_rodada(ingredientes);
                }else{ // se perdeu
                    printf("perdeu vida");
                    vidas--;
                }
            gerar_config_de_igredientes(ingredientes_temp); // muda a config caso o tempo acabe
            tempo_base_cronometro = GetTime(); // muda o tempo base do cronometro(zera)

        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

            DrawRectangleRec(botao_queijo, YELLOW);
            DrawRectangleRec(botao_molho, RED);
            DrawRectangleRec(botao_calabresa, ORANGE);
            DrawRectangleRec(botao_frango, BLACK);
            DrawRectangleRec(botao_cebola, LIGHTGRAY);
            DrawRectangleRec(botao_de_selecao, GREEN);

            printar_mensagens(ingredientes);
            cronometro = desenhar_e_retornar_cronometro(tempo_base_cronometro);
            desenhar_dinheiro_e_vida(dinheiro, vidas);

            desenhar_conf_ingredientes(ingredientes_temp);

        EndDrawing();

        if (dinheiro >= 200)
            venceu_jogo = true;

        primeiro_loop = false; // encerra a imunidade de tirar vida 
    }
}

int gerar_bool_aleatorio(){

    return GetRandomValue(0, 1);
}

void gerar_config_de_igredientes(bool ingredientes_temp[]){

    printf("\n --------------- Valor Alterado ---------------- \n");
    int qtd_igredientes = 0;
    bool temp;

    for(int i =  0; i < numero_de_ingredientes; i++){
        temp = gerar_bool_aleatorio();
        ingredientes_temp[i] = temp; // retorna aleatoriamente se inclui ou nao o igrediente
        if(temp)
        qtd_igredientes++;
    }

    if (qtd_igredientes < 2)
        gerar_config_de_igredientes(ingredientes_temp); //  recursao no caso de ter menos de 2 ingredientes
}

void printar_mensagens(bool ingredientes[]){
    if (ingredientes[Queijo])
        DrawText("Queijo selecionado", 400, 100, 30, BLACK);

    if (ingredientes[Molho_de_tomate])
        DrawText("Molho selecionado", 400, 200, 30, BLACK);

    if (ingredientes[Calabresa])
        DrawText("Calabresa selecionada", 400, 300, 30, BLACK);

    if (ingredientes[Frango])
        DrawText("Frango selecionado", 400, 400, 30, BLACK);

    if (ingredientes[Cebola])
        DrawText("Cebola selecionada", 400, 500, 30, BLACK);
}

void desenhar_conf_ingredientes(bool ingredientes_temp[]){
    if (ingredientes_temp[Queijo])
        DrawText("Queijo selecionado", 900, 100, 30, BLACK);

    if (ingredientes_temp[Molho_de_tomate])
        DrawText("Molho selecionado", 900, 200, 30, BLACK);

    if (ingredientes_temp[Calabresa])
        DrawText("Calabresa selecionada", 900, 300, 30, BLACK);

    if (ingredientes_temp[Frango])
        DrawText("Frango selecionado", 900, 400, 30, BLACK);

    if (ingredientes_temp[Cebola])
        DrawText("Cebola selecionada", 900, 500, 30, BLACK);
    
}

float desenhar_e_retornar_cronometro(float tempo_base_cronometro){
    float tempo_atual_cronometro = GetTime();

    char texto[5];
    float cronometro = (tempo_base_cronometro + 5.0f) - tempo_atual_cronometro;
    sprintf(texto, "%.2f", cronometro);

    DrawText(texto, 1300, 50, 20, BLACK);

    return cronometro;
}

bool verificar_vitória(bool ingredientes[], bool ingredientes_temp[]){
    bool vitoria = true;
    for(int i = 0; i < numero_de_ingredientes; i++){
        if (ingredientes[i] != ingredientes_temp[i]){
            vitoria = false;
        }
    }

    return vitoria;
}

int retornar_dinheiro_rodada(bool ingredientes[]){
    int dinheiro_final = 0;

    for(int i = 0; i < numero_de_ingredientes; i++)
        dinheiro_final += ingredientes[i] * 10; // da 10 dinheiros para cada ingrediente

    return dinheiro_final;
}

void desenhar_dinheiro_e_vida(int dinheiro, int vida){
    char texto[5];
    sprintf(texto, "%d", dinheiro);
    DrawText(texto, 1200, 50, 20, BLACK);

    sprintf(texto, "%d", vida);
    DrawText(texto, 1100, 50, 20, BLACK);
}

