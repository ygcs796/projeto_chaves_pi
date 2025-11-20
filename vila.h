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
} Acao_tomada;

// Executa a lógica da vila e retorna a ação escolhida
Acao_tomada executar_vila(void);

#endif
