#include "raylib.h"
#include "./arquivos_h/estadojogo.h"

int rodar_creditos(int larguraTela, int alturaTela) {

    int tela_atual_jogo = CREDITOS; // Isso significa que estamos nos créditos
    int quero_sair_dos_creditos = 0;

    // carregando a imagem de fundo
    Image tela_fundo = LoadImage("imagens/imagem_creditos.png");
    ImageResize(&tela_fundo, larguraTela, alturaTela);
    Texture2D tela_fundo_tex = LoadTextureFromImage(tela_fundo);

    // carregando a música
    Music musica_creditos = LoadMusicStream("musicas/musica_creditos.ogg");
    PlayMusicStream(musica_creditos);

    while (!WindowShouldClose() && !(quero_sair_dos_creditos))
    {
        
        UpdateMusicStream(musica_creditos);

        if(IsKeyPressed(KEY_ENTER)) {

            quero_sair_dos_creditos = 1;
            tela_atual_jogo = MENU;

        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(tela_fundo_tex, 0, 0, WHITE);

        EndDrawing();

    }

    UnloadImage(tela_fundo);
    UnloadMusicStream(musica_creditos);

    if (!(quero_sair_dos_creditos))
    {
        /* code */
        CloseWindow();

    }

    return tela_atual_jogo;
}