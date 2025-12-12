#include "raylib.h"
#include <string.h>
#include "cena_inicial_contexto_jogo.h"

void RodarContextoJogo() {

    // Carregando a fonte (ajuste o caminho se necessário)
    Font fonte = LoadFontEx("fase1/fontes/VCR_OSD_MONO_1.001.ttf", 32, 0, 250);
    Font fonteTitulo = LoadFontEx("fase1/fontes/VCR_OSD_MONO_1.001.ttf", 80, 0, 250); // Fonte maior para o título

    bool cena_acabou = false;

    // O TEXTO DA HISTÓRIA
    static const char *textoHistoria = 
        "Mais um dia ensolarado desponta na Vila.\n"
        "A aparente tranquilidade, entretanto, não passa de um engano:\n"
        "Há um rebuliço nas casas, um vai e vem furtivo, um cochicho perene, um espírito de sobressalto...\n"
        "De todos os moradores, Chaves parece ser o único sereno...\n"
        "Pior ainda, parece que há um esforço para que ele permaneça assim, alheio à correria que lhe rodeia...\n"
        "Por que será? O que os moradores estão aprontando dessa vez que o Chaves não pode saber?\n"
        "Bem, ele não pode saber e, por ora, você também não, caro jogador...\n"
        "Mas deixa isso pra lá por enquanto! Aperta enter e vem curtir um dia com o Chaves na vila!";

    static int letrasAtuais = 0;
    static int frameCounter = 0;
    static int estado = 0; // 0 = escrevendo, 1 = terminou de escrever
    static int piscadaCursor = 0; 

    int velocidade = 3; // Quanto menor, mais rápido escreve
    int totalLetras = strlen(textoHistoria);

    while(!WindowShouldClose() && !cena_acabou) {

        // Lógica de digitar (Igual ao tutorial)
        if (estado == 0) {
            frameCounter++;
            if (frameCounter >= velocidade) {
                letrasAtuais++;
                frameCounter = 0;
            }

            if (letrasAtuais >= totalLetras) {
                letrasAtuais = totalLetras;
                estado = 1; 
            }
        }

        // Pular ou Avançar
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            if (estado == 0) {
                // Se apertar enquanto digita, termina de digitar tudo na hora
                letrasAtuais = totalLetras;
                estado = 1;
            } else {
                // Se apertar depois de acabar, encerra a cena
                cena_acabou = true;
            }
        }

        piscadaCursor++; 

        BeginDrawing();
            ClearBackground(BLACK);

            // 1. Desenhando o Título (Centralizado)
            const char* titulo = "CHAVES: O JOGO";
            Vector2 tamanhoTexto = MeasureTextEx(fonteTitulo, titulo, 80, 5);
            int posTituloX = (GetScreenWidth() - tamanhoTexto.x) / 2;
            
            DrawTextEx(fonteTitulo, titulo, (Vector2){posTituloX, 50}, 80, 5, YELLOW);

            // 2. Desenhando o Texto da História
            Vector2 pos = {50, 180}; // Posição abaixo do título
            float tamanhoFonte = 28.0f;     
            float espacamento = 2.0f;

            DrawTextEx(fonte, TextSubtext(textoHistoria, 0, letrasAtuais), pos, tamanhoFonte, espacamento, WHITE); 

            // 3. Cursor Piscando
            if (estado == 0 && (piscadaCursor / 20) % 2 == 0) {
                // Calcula onde desenhar o quadrado verde baseado no tamanho do texto atual
                // (Simplificado: desenha no canto inferior direito para dar estilo retro)
                DrawRectangle(GetScreenWidth() - 40, GetScreenHeight() - 40, 20, 20, GREEN);
            }

            // 4. Aviso para começar
            if (estado == 1) {
                if ((piscadaCursor / 30) % 2 == 0) { 
                    const char* msg = "Pressione ENTER para jogar";
                    int larguraMsg = MeasureText(msg, 20);
                    DrawText(msg, (GetScreenWidth() - larguraMsg)/2, 550, 20, GREEN);
                }
            }

            // 5. Aviso de pular (discreto)
            if (estado == 0) {
                DrawText("SPACE para pular", GetScreenWidth() - 150, GetScreenHeight() - 30, 10, DARKGRAY);
            }

        EndDrawing();
    } 

    UnloadFont(fonte);
    UnloadFont(fonteTitulo);
}

