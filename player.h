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
    Rectangle hitbox;

    // VARIÁVEIS PARA MOVIMENTO POR BLOCOS NO JOGO
    bool isMoving; // indica se está ocorrendo o movimento de 1 BLOCO
    Vector2 startPos; // posição inicial do movimento de 1 bloco
    Vector2 targetPos; // posição final do movimento de 1 BLOCO
    float moveTimer; // contador para coordenar a velocidade de transição
    float moveTime; // tempo para o personagem se mover em 1 bloco;
    int tileSize; // tamanho de 1 bloco de movimentação

    // CAMPOS PARA ANIMAÇÃO
    Image imagemSprites;
    Texture2D texSprites;
    int larguraFrame; // largura de 1 único quadro dos sprites do Chaves
    int alturaFrame; // altura de 1 único quadro dos sprites do Chaves
    int direcao; 
    int frameAtual;

    int pernaParaAndar; // variável para animação
    
} Player;

void atualizarjogador(Player *p);
void setarjogador(Player *p, Vector2 pos);
void desenharjogador(Player *p);
void descarregarjogador(Player *p);

#endif
