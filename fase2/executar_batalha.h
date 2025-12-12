#ifndef EXECUTARBATALHA_H
#define EXECUTARBATALHA_H

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <stdbool.h>

typedef enum{
    Cura,
    PP
}TipoItem;

typedef struct{
    char nome[20]; // nome do ataque
    int pp_MAX; // maximo de pp de um ataque
    int pp; // quantidade de vezes que pode ser usado
    int dano;
}Ataque;

typedef struct{
    char nome[30];
    int vida; // vida do bixomon
    int vida_MAX;
    int nivel; // nivel do bixomon
    int velocidade; // poder de ataque 
    Ataque ataques[4]; // os 4 ataques do bixomon
}Bixomon;

typedef enum{
    NaoAcao = -1,
    Menu = 0,
    selecionarAtaques = 1,
    Mochila = 2,
    Mochila_PP = 3
}Tela;

typedef struct{
    char nome[20];
    int qtd;
    int module;
    TipoItem tipoItem;
}Item;

void executarBatalha(Bixomon *player, Bixomon *oponente);
int receber_ataque(Bixomon **player, Bixomon **oponente, Rectangle botoesAtaques[], Vector2 posicaoMouse, bool *botaoEmPressao, Texture2D fundoBatalha);
void PausarMs(int ms);
int menu_batalha(Bixomon *player, Bixomon *oponente, Vector2 posicao_mouse, Rectangle botao_ataque, bool *botaoEmPressao, Rectangle botao_mochila, Texture2D fundoBatalha);
int executar_mochila(Bixomon **player, Item itens[], int numItens, Vector2 posicaoMouse);
void printarFundoBatalha(Bixomon *player, Bixomon *oponente, Texture2D fundoBatalha);

#endif
