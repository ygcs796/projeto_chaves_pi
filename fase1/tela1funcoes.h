#ifndef TELA1_FUNCOES_H
#define TELA1_FUNCOES_H

#include <stdbool.h>
#include "raylib.h"
#include "fase1.h"  

#define LARGURA_BASE   1280
#define ALTURA_BASE    720

int gerar_bool_aleatorio(void);
void gerar_config_de_igredientes(bool ingredientes_temp[]);
void printar_ingredientes(bool ingredientes[], Texture2D lista_imagens_pizza[], Texture2D x_bebidas);
void desenhar_conf_ingredientes(bool ingredientes_temp[], Texture2D img);
float desenhar_e_retornar_cronometro(float tempo_base_cronometro);
bool verificar_vitoria(bool ingredientes[], bool ingredientes_temp[]);
int retornar_dinheiro_rodada(bool ingredientes[]);
void desenhar_dinheiro_e_vida(int dinheiro, int vida);
void DesenharImagemFit(Texture2D img);

#endif