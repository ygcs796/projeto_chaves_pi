#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "creditos.h"
#include "player.h"
#include "vila.h"
#include "fase1/fase1.h"
#include "cena_inicial_contexto_jogo.h"
#include "fase2/executar_batalha.h"

typedef enum {
    MENU = 0,
    CREDITOS,
    GAMEPLAY,
    INTRO_HISTORIA,
    FIM_DE_JOGO
} GameState;

int main(void) {

    // INICIALIZANDO A TELA
    const int largura_tela = 1920; //GetMonitorWidth(0);  1366;
    const int altura_tela = 1080; //GetMonitorHeight(0); 768;
    InitWindow(largura_tela, altura_tela, "Chaves: em busca da chave perdida"); // abre a janela
    
    SetTargetFPS(60);

    GameState tela_atual = MENU;

    Image imagem_final = LoadImage("./imagens/imagem_final.png");
    Texture2D final = LoadTextureFromImage(imagem_final);
    UnloadImage(imagem_final);

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
        
            executar_vila();
            tela_atual = FIM_DE_JOGO;
            break;
        case FIM_DE_JOGO:

            if (IsKeyPressed(KEY_ENTER)) {

                tela_atual = MENU;

            }

            if (!WindowShouldClose()) {

                BeginDrawing();

                    DrawTexture(final, 0, 0, WHITE);
            
                EndDrawing();

            }    

            break;
        default:
            break;
        }

    }
    UnloadTexture(final);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}