#include <stdio.h>
#include <math.h>
#include "tela1funcoes.h"
#include "fase1.h"

int gerar_bool_aleatorio(void) {
    return GetRandomValue(0, 1);
}

void gerar_config_de_igredientes(bool ingredientes_temp[]) {
    printf("\n --------------- Valor Alterado ---------------- \n");

    int qtd_ingredientes = 0;

    for (int i = 0; i < numero_de_ingredientes - 2; i++) { // o "-2" se refere às duas bebidas que serao tratadas como caso especial na funcao
        bool temp = gerar_bool_aleatorio();
        ingredientes_temp[i] = temp;
        if (temp) qtd_ingredientes++; // se o booleano temporario for 1(ou seja ingrediente adicionado) entao aumenta o contador de ingredientes
    }

    ingredientes_temp[suco] = gerar_bool_aleatorio();
    ingredientes_temp[refri] = !ingredientes_temp[suco]; // garante que um deles sempre ocorra mas nao juntos


    if (qtd_ingredientes < 2)
        gerar_config_de_igredientes(ingredientes_temp); // recusao para garantir ao menos dois ingredientes
}

void printar_ingredientes(bool ingredientes[], Texture2D lista_imagens_pizza[], Texture2D x_bebidas) {
    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE;

    if (ingredientes[Champion])
        DrawTexture(lista_imagens_pizza[Champion], 354 * escala_x, 57 * escala_y, WHITE);

    if (ingredientes[Presunto])
        DrawTexture(lista_imagens_pizza[Presunto], 354 * escala_x, 57 * escala_y, WHITE);

    if (ingredientes[Calabresa])
        DrawTexture(lista_imagens_pizza[Calabresa], 354 * escala_x, 57 * escala_y, WHITE);

    if (ingredientes[Frango])
        DrawTexture(lista_imagens_pizza[Frango], 354 * escala_x, 57 * escala_y, WHITE);

    if (ingredientes[Cebola])
        DrawTexture(lista_imagens_pizza[Cebola], 354 * escala_x, 57 * escala_y, WHITE);
    
    if (ingredientes[suco])
        DrawTexture(x_bebidas, 75 * escala_x, 577 * escala_y, WHITE);

    if (ingredientes[refri])
        DrawTexture(x_bebidas, 216 * escala_x, 577 * escala_y, WHITE);
}

void desenhar_conf_ingredientes(bool ingredientes_temp[], Texture2D img) {
    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE;

    if (ingredientes_temp[Champion])
        DrawTexture(img, 1182 * escala_x, 259 * escala_y, WHITE);

    if (ingredientes_temp[Presunto])
        DrawTexture(img, 1182 * escala_x, 297 * escala_y, WHITE);

    if (ingredientes_temp[Calabresa])
        DrawTexture(img, 1182 * escala_x, 336 * escala_y, WHITE);

    if (ingredientes_temp[Frango])
        DrawTexture(img, 1182 * escala_x, 371 * escala_y, WHITE);

    if (ingredientes_temp[Cebola])
        DrawTexture(img, 1182 * escala_x, 413 * escala_y, WHITE);

    if (ingredientes_temp[suco])
        DrawTexture(img, 1182 * escala_x, 451 * escala_y, WHITE);

    if (ingredientes_temp[refri])
        DrawTexture(img, 1182 * escala_x, 490 * escala_y, WHITE);
}

float desenhar_e_retornar_cronometro(float tempo_base_cronometro) {
    float tempo_atual = GetTime();

    char texto[16];
    float cronometro = (tempo_base_cronometro + 10.0f) - tempo_atual;

    sprintf(texto, "%.2f", cronometro);

    DrawText(texto, 1300, 50, 20, BLACK);

    return cronometro;
}

bool verificar_vitoria(bool ingredientes[], bool ingredientes_temp[]) {
    for (int i = 0; i < numero_de_ingredientes; i++) {
        if (ingredientes[i] != ingredientes_temp[i])
            return false;
    }
    return true;
}

int retornar_dinheiro_rodada(bool ingredientes[]) {
    int dinheiro_final = 0;

    for (int i = 0; i < numero_de_ingredientes; i++)
        dinheiro_final += ingredientes[i] * 10;

    return dinheiro_final;
}

void desenhar_dinheiro_e_vida(int dinheiro, int vida) {
    char texto[16];

    sprintf(texto, "%d", dinheiro);
    DrawText(texto, 1200, 50, 20, BLACK);

    sprintf(texto, "%d", vida);
    DrawText(texto, 1100, 50, 20, BLACK);
}

void DesenharImagemFit(Texture2D img) {

    float sw = GetScreenWidth();
    float sh = GetScreenHeight();

    float iw = img.width;
    float ih = img.height;

    float scale = fminf(sw / iw, sh / ih);

    float largura_final = iw * scale;
    float altura_final  = ih * scale;

    float x = (sw - largura_final) / 2.0f;
    float y = (sh - altura_final) / 2.0f;

    DrawTexturePro(
        img,
        (Rectangle){0, 0, iw, ih},
        (Rectangle){x, y, largura_final, altura_final},
        (Vector2){0,0},
        0,
        WHITE
    );
}




