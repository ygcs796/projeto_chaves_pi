#include "raylib.h"
#include <stdio.h>

int rodarMenu(int larguraJanela, int alturaJanela) {

    int opcao_selecionada = 1; // A opção que já vai vir selecionada vai ser o START
    int tela_do_jogo = 0; // configuração para dizer que estamos no MENU
    int quero_sair_do_menu = 0;

    // Sfx == Sound Effect
    Sound sfx_selecao = LoadSound("./efeitos_sonoros/som_selecao_opcoes_menu_8bit.wav");
    SetSoundVolume(sfx_selecao, 0.10);

    Sound sfx_start = LoadSound("./efeitos_sonoros/som_start_8bit.wav");
    SetSoundVolume(sfx_start, 0.40);

    Image telaFundo = LoadImage("imagens/telaFundo.png");
    Image titulo = LoadImage("imagens/titulo.png");
    Image subtitulo = LoadImage("imagens/subtitulo.png");
    Image chaves = LoadImage("imagens/chaves.png");
    Image botaoCreditos = LoadImage("imagens/botaoCreditos.png");
    Image botaoStart = LoadImage("imagens/botaoStart.png");
    Image chaveSeletora = LoadImage("imagens/chaveSeletora.png");

    ImageResize(&telaFundo, larguraJanela, alturaJanela);
    ImageResize(&titulo, 600, 300);
    ImageResize(&subtitulo, 400, 200);
    ImageResize(&chaves, 300, 500);
    ImageResize(&botaoCreditos, 350, 100);
    ImageResize(&botaoStart, 300, 100);
    ImageResize(&chaveSeletora, 100, 50);

    Texture2D telaFundoTex = LoadTextureFromImage(telaFundo);
    Texture2D tituloTex = LoadTextureFromImage(titulo);
    Texture2D subtituloTex = LoadTextureFromImage(subtitulo);
    Texture2D chavesTex = LoadTextureFromImage(chaves);
    Texture2D botaoCreditosTex = LoadTextureFromImage(botaoCreditos);
    Texture2D botaoStartTex = LoadTextureFromImage(botaoStart);
    Texture2D chaveSeletoraTex = LoadTextureFromImage(chaveSeletora);
    int alturaChave = 725;


    Music musicaMenu = LoadMusicStream("musicas/musicaMenu.ogg");
    PlayMusicStream(musicaMenu);

    while (!WindowShouldClose() && !(quero_sair_do_menu))
    {
        UpdateMusicStream(musicaMenu);
        
        if (IsKeyPressed(KEY_UP)){

            opcao_selecionada--;

            if (opcao_selecionada < 0)
            {
                
                opcao_selecionada = 1;

            }
            PlaySound(sfx_selecao);

        } else if (IsKeyPressed(KEY_DOWN))
        {

            opcao_selecionada++;

            if (opcao_selecionada > 1)
            {
                
                opcao_selecionada = 0;

            }
            
            PlaySound(sfx_selecao);
            
        } else if (IsKeyPressed(KEY_ENTER))
        {
            if (opcao_selecionada == 0)
            {
                /* code */
                tela_do_jogo = 1;
                quero_sair_do_menu = 1;

                PlaySound(sfx_selecao);

            } else if (opcao_selecionada == 1)
            {
                /* code */
                tela_do_jogo = 2;
                quero_sair_do_menu = 1;

                PlaySound(sfx_start);
            }
            
        }
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            DrawTexture(telaFundoTex, 0, 0, WHITE);
            DrawTexture(tituloTex, 575, 25, WHITE);
            DrawTexture(subtituloTex, 700, 300, WHITE);
            DrawTexture(chavesTex, 200, 450, WHITE);
            DrawTexture(botaoCreditosTex, 725, 700, WHITE);
            DrawTexture(botaoStartTex, 750, 850, WHITE);

            if (opcao_selecionada == 0)
            {
                alturaChave = 725;
            } else if (opcao_selecionada == 1) {

                alturaChave = 880;
            }
            
            DrawTexture(chaveSeletoraTex, 630, alturaChave, WHITE);
        
        EndDrawing();
    }
    
    UnloadImage(telaFundo);
    UnloadImage(titulo);
    UnloadImage(subtitulo);
    UnloadImage(chaves);
    UnloadImage(botaoCreditos);
    UnloadImage(botaoStart);
    UnloadImage(chaveSeletora);
    
    UnloadMusicStream(musicaMenu);
    
    // Loops para esperar o som terminar para eu dar free nele
    while(IsSoundPlaying(sfx_selecao)) {}
    UnloadSound(sfx_selecao);
    
    while (IsSoundPlaying(sfx_start)) {}
    UnloadSound(sfx_start);

    if (!(quero_sair_do_menu))
    {
        /* code */

        CloseWindow();

    }
    

    return tela_do_jogo;
}