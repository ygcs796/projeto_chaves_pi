#ifndef FASE1_H
#define FASE1_H
#define numero_de_ingredientes 7

#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>

typedef enum {
    Champion,
    Presunto,
    Calabresa,
    Frango,
    Cebola,
    suco,
    refri
} Tipo_de_ingrediente;

typedef struct{
    bool ingredientes[numero_de_ingredientes];
    int tempo_de_cozimento[2]; // intervalo int1 - int2
}Pizza;

typedef struct{
    int vidas;
    int dinheiro;
    Pizza pizza_atual;
    bool vitoria_parte_1;
}Info_rodada;


void Executar_fase_1();
void printar_vitoria();
void printar_derrota();


#endif
