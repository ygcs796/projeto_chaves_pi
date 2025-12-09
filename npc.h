#ifndef NPC_H
#define NPC_H
#include "raylib.h"

typedef struct {
    // variáveis de movimentação
    Vector2 position;
    Rectangle hitbox;

    // variáveis de gráficos
    Image SpriteImage;
    Texture2D TexSprite;
    int larguraFrame;
    int alturaFrame;

} NPC;

#endif
