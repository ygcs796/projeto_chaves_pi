#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "player.h"
#include "vila.h"
#include "fase1/fase1.h"

typedef enum {
    MENU = 0,
    CREDITOS,
    GAMEPLAY
} GameState;

int main(void) {

    // INICIALIZANDO A TELA
    const int largura_tela = 1920;//1920; //GetMonitorWidth(0);  1366;
    const int altura_tela = 1080;//1080; //GetMonitorHeight(0); 768;
    InitWindow(largura_tela, altura_tela, "Chaves: em busca da chave perdida"); // abre a janela
    
    ToggleFullscreen();

    SetTargetFPS(60);

    GameState tela_atual = MENU;

    InitAudioDevice();

    while (!WindowShouldClose())
    {
        switch (tela_atual)
        {
        case MENU:
            /* code */
            tela_atual = rodarMenu(largura_tela, altura_tela);
            break;
        case CREDITOS:
            /* code */
            tela_atual = rodar_creditos(largura_tela, altura_tela);
            break;
        case GAMEPLAY:
            /* code */
            executar_vila(); // executa a  vila e retorna um enum Fase_selcionada do arquivo vila.h
            break;
        default:
            break;
        }

    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}