#ifndef TELA1_H
#define TELA1_H

#include <stdio.h>
#include "raylib.h"
#include "fase1.h"
#include "tela1funcoes.h"

#define LARGURA_BASE_FULL 1920
#define ALTURA_BASE_FULL 1080

bool executar_tela_2(Info_rodada info_rodada);
void printar_imagens_correto_comanda(bool ingredientes[], Texture2D imagem_correto);
void printar_cronometro(float tempo_cronometro, float escala_x, float escala_y, int tempo_de_cozimento[]);
void printar_vida_e_dinheiro(int vida, int dinheiro, float escala_x, float escala_y);

#endif