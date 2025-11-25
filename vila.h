#ifndef VILA_H
#define VILA_H

#include <stdbool.h>
#include "raylib.h"
#include "player.h"

typedef enum {
    erro,
    porta_florinda,
    porta_2,
    porta_3
} Fase_selecionada;

// Executa a lógica da vila e retorna a ação escolhida
Fase_selecionada executar_vila();

#endif
