#ifndef CASA_FLORINDA_H
#define CASA_FLORINDA_H

#include <raylib.h>
#include <string.h>

int RodarDialogo(Texture2D imgA, Texture2D imgB, Texture2D imgCaixa, Font fonte, const char *falas[], int totalLinhas, const char *nomes[]);
int RodarCenaInicial(void);

#endif
