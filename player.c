#include "player.h"
#include "raylib.h"

void atualizarjogador(Player *p) {
    // Movimento do player
    if (IsKeyDown(KEY_RIGHT)) p->pos.x += p->velocidade;
    if (IsKeyDown(KEY_LEFT))  p->pos.x -= p->velocidade;
    if (IsKeyDown(KEY_UP))    p->pos.y -= p->velocidade;
    if (IsKeyDown(KEY_DOWN))  p->pos.y += p->velocidade;

    // Atualizar hitbox baseado no centro
    p->hitbox.x = p->pos.x - p->hitbox.width / 2;
    p->hitbox.y = p->pos.y - p->hitbox.height / 2;
}

void setarjogador(Player *p, Vector2 pos, float velocidade) {
    p->pos = pos;
    p->velocidade = velocidade;

    // Define o tamanho da hitbox
    p->hitbox.width = 100;
    p->hitbox.height = 100;

    // Ajusta hitbox ao centro do player
    p->hitbox.x = pos.x - p->hitbox.width / 2;
    p->hitbox.y = pos.y - p->hitbox.height / 2;
}
