#ifndef FASE1_H
#define FASE1_H

#include <raylib.h>
#include <stdbool.h>

typedef enum {
    Queijo,
    Molho_de_tomate,
    Calabresa,
    Frango,
    Cebola
} Tipo_de_ingrediente;

void Executar_fase_1(void);

#endif
