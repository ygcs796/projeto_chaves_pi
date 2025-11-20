#include "raylib.h"

int rodar_creditos(int larguraTela, int alturaTela) {

    int tela_atual_jogo = 1; // Isso significa que estamos nos créditos
    int quero_sair_dos_creditos = 0;

    // sfx = Sound Effect
    Sound sfx_enter = LoadSound("./efeitos_sonoros/som_selecao_opcoes_menu_8bit.wav");
    SetSoundVolume(sfx_enter, 0.10);

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
            tela_atual_jogo = 0;

            PlaySound(sfx_enter);
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(tela_fundo_tex, 0, 0, WHITE);

        EndDrawing();

    }

    // fazendo esse loop para o programa só dar free quando o efeito sonoro acabar
    while (IsSoundPlaying(sfx_enter)){}
    UnloadSound(sfx_enter);

    UnloadImage(tela_fundo);
    UnloadMusicStream(musica_creditos);

    if (!(quero_sair_dos_creditos))
    {
        /* code */
        CloseWindow();

    }

    return tela_atual_jogo;
}