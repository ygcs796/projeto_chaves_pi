#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef enum {
    BAIXO = 0,
    DIREITA = 1,
    CIMA = 2,
    ESQUERDA = 3,
} DirecaoJogador;
typedef struct {
    Vector2 pos;
    float velocidade;
    Rectangle hitbox;

    // CAMPOS PARA ANIMAÇÃO
    Image imagemSprites;
    Texture2D texSprites;
    int larguraFrame; // largura de 1 único quadro dos sprites do Chaves
    int alturaFrame; // altura de 1 único quadro dos sprites do Chaves
    int direcao;
    int contadorFrame;
    int velocidadeFrame;
    int frameAtual;
    
} Player;

void atualizarjogador(Player *p);
void setarjogador(Player *p, Vector2 pos, float velocidade);
void desenharjogador(Player *p);
void descarregarjogador(Player *p);

#endif
