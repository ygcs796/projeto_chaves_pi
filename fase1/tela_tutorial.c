#include <raylib.h>
#include <string.h>

int RodarTutorial(Font fonte) {
    
    static const char *textoIntro = 
        "Bem-vindo à fase 1: O Restaurante de Dona Florinda!\n"
        "Sua missão é:\n"
        "1) Olhar, atentamente, à direita, os ingredientes\nindicados pelo tick verde\n"
        "2) Clicar, agilmente, nesses ingredientes\n"
        "3) Fazer o máximo de pizzas antes que o tempo acabe\n"
        "Se eu fosse você, não deixaria o cronômetro ficar vermelho...\n"
        "Tá fazendo o que aqui ainda? Aperta ENTER pra começar!";

    
    static int letrasAtuais = 0;
    static int frameCounter = 0;
    static int estado = 0; 
    static int piscadaCursor = 0; 

    int velocidade = 4; 
    int totalLetras = strlen(textoIntro);

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

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        if (estado == 0) {
            
            letrasAtuais = totalLetras;
            estado = 1;
        } else {
           
            letrasAtuais = 0;
            estado = 0;
            return 1;
        }
    }

    piscadaCursor++; 

    BeginDrawing();
        ClearBackground(BLACK);

        Vector2 pos = {30, 50}; // margem
        float tamanho = 20.0f;     
        float espacamento = 3.0f;

        // Desenha o texto parcial (Subtext)
        DrawTextEx(fonte, TextSubtext(textoIntro, 0, letrasAtuais), pos, tamanho, espacamento, WHITE); 
        

        // Desenha o Cursor piscando no final do texto (Efeito Retro)
        // Só desenha se não acabou o texto
        if (estado == 0 && (piscadaCursor / 20) % 2 == 0) {
            
            DrawRectangle(GetScreenWidth() - 30, GetScreenHeight() - 30, 15, 15, GREEN);
        }

        // Se acabou, mostra aviso para continuar
        if (estado == 1) {
            if ((piscadaCursor / 30) % 2 == 0) { // Pisca a cada meio segundo
                DrawText("Pressione ENTER para comecar", 250, 400, 20, DARKGREEN);
            }
        }

        // Opção de Pular (sempre visível fraco)
        if (estado == 0) {
            DrawText("SPACE para pular", GetScreenWidth() - 150, GetScreenHeight() - 20, 10, DARKGRAY);
        }

    EndDrawing();

    return 0; // Ainda não acabou
}

// int main(void) {
//     // Inicializa janela maiorzinha para caber o texto
//     InitWindow(1000, 600, "TESTE DA INTRODUCAO");
//     SetTargetFPS(60);


//     Font fonteRetro = LoadFontEx("fase1/fontes/VCR_OSD_MONO_1.001.ttf", 64, 0, 250);
    
//     // Filtro para ficar pixelado bonito
//     SetTextureFilter(fonteRetro.texture, TEXTURE_FILTER_POINT);

//     while (!WindowShouldClose()) {
        
//         // Chama a função
//         int resultado = RodarTutorial(fonteRetro);

//         // Se a intro acabou (retornou 1), fechamos a janela de teste
//         if (resultado == 1) {
//             break; 
//         }
//     }

    
//     UnloadFont(fonteRetro);
//     CloseWindow();
    
//     return 0;
// }