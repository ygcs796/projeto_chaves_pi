#include <stdio.h>
#include "raylib.h"
#include "fase1.h"
#include "tela1funcoes.h"
#include "tela2.h"

bool executar_tela_2(Info_rodada info_rodada){

    Texture2D fundo = LoadTexture("imagens/fogao_fase1.png");
    Texture2D imagem_correto_comanda = LoadTexture("imagens/sinal_de_correto_comanda_fase1.png");

    Pizza pizza = info_rodada.pizza_atual;

    float tempo_inicial = GetTime();
    bool botao_pressionado = false;

    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE_FULL;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE_FULL;

    Rectangle botao_parar_cozimento = {1200 * escala_x, 700 * escala_y, 80 * escala_x, 80 * escala_y};

    Texture2D lista_imagens_pizza[6];
    lista_imagens_pizza[5] = LoadTexture("imagens/pizza_queijo_e_molho.png");
    lista_imagens_pizza[0] = LoadTexture("imagens/cogumelos.png");
    lista_imagens_pizza[1] = LoadTexture("imagens/presunto (2).png");
    lista_imagens_pizza[2] = LoadTexture("imagens/calabresa.png");
    lista_imagens_pizza[3] = LoadTexture("imagens/frango2.png");
    lista_imagens_pizza[4] = LoadTexture("imagens/cebola (2).png");

    char texto_tempo_comanda[10];

    sprintf(texto_tempo_comanda, "%02d - %02d", pizza.tempo_de_cozimento[0], pizza.tempo_de_cozimento[1]); // defino a string que contem os intervalos de tempo de cozimento da pizza
    float tempo_atual = GetTime();
    float tempo_cronometro = tempo_atual - tempo_inicial;
    Vector2 mouse = GetMousePosition();
    float nivel_queimado = 0.0f;
    
    while(!WindowShouldClose() && !botao_pressionado){
        nivel_queimado += 0.2361f;

        tempo_atual = GetTime();
        tempo_cronometro = tempo_atual - tempo_inicial;
        mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, botao_parar_cozimento) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            if(tempo_cronometro >= pizza.tempo_de_cozimento[0] && tempo_cronometro <= pizza.tempo_de_cozimento[1])
                return true; // apertou o botao no tempo certo
            else
                return false; // apertou o botao no tempo errado
        else if (tempo_cronometro >= 18) // se o tempo do cronometro for 5 segs maior que o tempo maximo
            return false; 
            

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DesenharImagemFit(fundo);
            DrawTexture(lista_imagens_pizza[5], 433 * escala_x, 291 * escala_y, WHITE);
            DrawTexture(lista_imagens_pizza[5], 433 * escala_x, 291 * escala_y, (Color){0, 0, 0, (int)nivel_queimado}); // desenha outra imagem da pizza por cima para dar a ideia de queimado
            printar_imagens_correto_comanda(pizza.ingredientes, imagem_correto_comanda);
            DrawText(texto_tempo_comanda, 1753 * escala_x, 842 * escala_y, 40 * escala_x, BLACK); // printa o intervalo de cozimnto da pizza
            printar_cronometro(tempo_cronometro, escala_x, escala_y, pizza.tempo_de_cozimento);
            printar_vida_e_dinheiro(info_rodada.vidas, info_rodada.dinheiro, escala_x, escala_y);

            DrawRectangleRec(botao_parar_cozimento, GREEN);
            

        EndDrawing();
    }

    return false; // retorna falso em qualquer codicao adversa que possa ocorrer
}

void printar_imagens_correto_comanda(bool ingredientes[], Texture2D imagem_correto) {
    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE_FULL;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE_FULL;

    if (ingredientes[Champion])
        DrawTexture(imagem_correto, 1749 * escala_x, 397 * escala_y, WHITE);

    if (ingredientes[Presunto])
        DrawTexture(imagem_correto, 1749 * escala_x, 456 * escala_y, WHITE);

    if (ingredientes[Calabresa])
        DrawTexture(imagem_correto, 1749 * escala_x, 515 * escala_y, WHITE);

    if (ingredientes[Frango])
        DrawTexture(imagem_correto, 1749 * escala_x, 574 * escala_y, WHITE);

    if (ingredientes[Cebola])
        DrawTexture(imagem_correto, 1749 * escala_x, 633 * escala_y, WHITE);

    if (ingredientes[suco])
        DrawTexture(imagem_correto, 1749 * escala_x, 692 * escala_y, WHITE);

    if (ingredientes[refri])
        DrawTexture(imagem_correto, 1749 * escala_x, 751 * escala_y, WHITE);
}

void printar_cronometro(float tempo_cronometro, float escala_x, float escala_y, int tempo_de_cozimento[]){

    char texto_cronometro[10];
    sprintf(texto_cronometro,"%02.2f", tempo_cronometro);

    if (tempo_cronometro >= tempo_de_cozimento[0] && tempo_cronometro <= tempo_de_cozimento[1]) // se for menor que o tempo final, o texto e verde, se nao, vermelho
        DrawText(texto_cronometro, 1623 * escala_x, 202 * escala_y, 40 * escala_x, GREEN);
    else if (tempo_cronometro > tempo_de_cozimento[1])
        DrawText(texto_cronometro, 1623 * escala_x, 202 * escala_y, 40 * escala_x, RED);
    else if (tempo_cronometro < tempo_de_cozimento[0])
        DrawText(texto_cronometro, 1623 * escala_x, 202 * escala_y, 40 * escala_x, BLUE);
}

void printar_vida_e_dinheiro(int vida, int dinheiro, float escala_x, float escala_y){

    char texto[5];

    sprintf(texto, "%d", dinheiro);
    DrawText(texto, 1600 * escala_x, 959 * escala_y, 60 * escala_x, WHITE);

    sprintf(texto, "%d", vida);
    DrawText(texto, 1783 * escala_x, 959 * escala_y, 60 * escala_x, WHITE);
}

