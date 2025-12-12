#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "player.h"
#include "vila.h"
#include "fase1/fase1.h"
#include "cena_inicial_contexto_jogo.h"

typedef enum {
    MENU = 0,
    CREDITOS,
    GAMEPLAY,
    INTRO_HISTORIA
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
        
            // próxima tela que o menu quer ir
            GameState proxima_do_menu = (GameState)rodarMenu(largura_tela, altura_tela);
            
            // se o menu mandou ir pro jogo, nós desviamos para a intro primeiro
            if (proxima_do_menu == GAMEPLAY) {
                tela_atual = INTRO_HISTORIA;
            } else {
                tela_atual = proxima_do_menu;
            }
            break;

        case CREDITOS:
            
            tela_atual = rodar_creditos(largura_tela, altura_tela);
            break;

        case INTRO_HISTORIA:

            RodarContextoJogo(); // roda até acabar (tem loop próprio)
            
            // rodando o loop do contexto do jogo, passamos para a tela gameplay
            tela_atual = GAMEPLAY;
            break;

        case GAMEPLAY:
        
            executar_vila(); // executa a  vila e retorna um enum Fase_selcionada do arquivo vila.h
            break;
        default:
            break;
        }

        // if (tela_atual == 0)
        // {
        //     /* code */
            

        // } else if (tela_atual == 1) {
            
            

        // } 
        // else if (tela_atual == 2) { // tela de gameplay

        //     /*if (IsKeyPressed(KEY_ENTER))
        //     {
        //          code
        //         tela_atual = 0;

        //     }*/

        //     printf("porta selecionada: %d", fase_selecionada);

        //     if (fase_selecionada == porta_florinda){
        //         Executar_fase_1();
        //     }
            

        // }

    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}