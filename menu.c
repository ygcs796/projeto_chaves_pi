#include <stdio.h>
#include "raylib.h"
#include "./arquivos_h/estadojogo.h"

int rodarMenu(int larguraJanela, int alturaJanela) {

    int opcao_selecionada = 1; // A opção que já vai vir selecionada vai ser o START
    EstadoJogo tela_do_jogo = MENU; // configuração para dizer que estamos no MENU
    int quero_sair_do_menu = 0;

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
            

        } else if (IsKeyPressed(KEY_DOWN))
        {
            
            opcao_selecionada++;

            if (opcao_selecionada > 1)
            {
                
                opcao_selecionada = 0;

            }
            
        } else if (IsKeyPressed(KEY_ENTER))
        {
            if (opcao_selecionada == 0)
            {
                /* code */
                tela_do_jogo = CREDITOS;
                quero_sair_do_menu = 1;

            } else if (opcao_selecionada == 1)
            {
                /* code */
                tela_do_jogo = GAMEPLAY;
                quero_sair_do_menu = 1;

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

            // printando a chave seletora de acordo com a posição dela
            if (opcao_selecionada == 0)
            {
                alturaChave = 725;
            } else if (opcao_selecionada == 1) {

                alturaChave = 880;
            }
            
            DrawTexture(chaveSeletoraTex, 630, alturaChave, WHITE);
        
        EndDrawing();
    }

    if (!(quero_sair_do_menu))
    { 
        /* code */
        UnloadImage(telaFundo);
        UnloadImage(titulo);
        UnloadImage(subtitulo);
        UnloadImage(chaves);
        UnloadImage(botaoCreditos);
        UnloadImage(botaoStart);
        UnloadImage(chaveSeletora);

        UnloadMusicStream(musicaMenu);
        
        CloseWindow();

    }
    

    return tela_do_jogo;
}