#ifndef FASE1_H
#define FASE1_H
#define numero_de_ingredientes 5

#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>

typedef enum {
    Queijo,
    Molho_de_tomate,
    Calabresa,
    Frango,
    Cebola
} Tipo_de_ingrediente;

void Executar_fase_1(void);
int gerar_bool_aleatorio();
void gerar_config_de_igredientes(bool ingredientes_temp[]);
void printar_mensagens(bool ingredientes[]);
void desenhar_conf_ingredientes(bool ingredientes_temp[]);
float desenhar_e_retornar_cronometro(float tempo_base_cronometro);
bool verificar_vitória(bool ingredientes[], bool ingredientes_temp[]);
int retornar_dinheiro_rodada(bool ingredientes[]);
void desenhar_dinheiro_e_vida(int dinheiro, int vida);

#endif
