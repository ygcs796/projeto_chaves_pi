#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef struct {
    Vector2 pos;
    float velocidade;
    Rectangle hitbox;
} Player;

void atualizarjogador(Player *p);
void setarjogador(Player *p, Vector2 pos, float velocidade);

#endif
