#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "npc.h"

// void setar_dona_florinda(NPC* florinda, Vector2 pos) {

//     florinda->position = pos;
//     florinda->alturaFrame =

// }

// a função abaixo indica as coordenadas do ponto em que o mouse está (aparece no canto superior esquerdo da tela, em vermelho)
void desenhar_debug_mouse(Camera2D camera) { // debug, tirar depois
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("X: %.0f Y: %.0f", mouseWorld.x, mouseWorld.y), 
             GetScreenToWorld2D((Vector2){10, 10}, camera).x, 
             GetScreenToWorld2D((Vector2){10, 50}, camera).y, 
             20, RED);
}

void carregar_casa_florinda(Player jogador, Camera2D camera) {

    Image imagem_casa_florinda = LoadImage("./imagens/casaFlorinda.png");
    Texture cenario_casa_florinda = LoadTextureFromImage(imagem_casa_florinda);
    UnloadImage(imagem_casa_florinda);

    Rectangle barreiras_casa[] = {
        {0, 580, 850, 320}, // PAREDE SUPERIOR (até a porta da cozinha)
        {0, 580, 45, 1260}, // PAREDE ESQUERDA
        {0, 1800, 850, 40}, // PAREDE INFERIOR
        {805, 580, 45, 1260}, // PAREDE DIREITA
        {216, 1012, 144, 243}, // MESA DA COZINHA
        {61, 1006, 66, 222}, // MOVEL DE MADEIRA DA COZINHA
        {365, 1041, 40, 140}, // CADEIRA COZINHA (DIREITA)
        {250, 935, 75, 75}, // CADEIRA COZINHA (CIMA) 
        {260, 1327, 100, 120}, // POLTRONA
        {106, 1526, 80, 180}, // SOFÁ
        {463, 1550, 55, 100} // MÓVEL DE MADEIRA DA SALA 
    };

    const int quant_barreiras_casa = sizeof(barreiras_casa) / sizeof(barreiras_casa[0]);

    Vector2 pos_chaves = {641, 1636}; // testando

    setarjogador(&jogador, pos_chaves);

    jogador.direcao = CIMA;

    while(!WindowShouldClose()) {
        
        
        // entradas do teclado ou atualizações
        atualizarjogador(&jogador, barreiras_casa, quant_barreiras_casa);
        camera.target = jogador.pos;
        

        // desenho

        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                DrawTexture(cenario_casa_florinda, 0, 0, WHITE);

                desenharjogador(&jogador);
                
                // desenhando as barreiras da casa para debug, tirar depois
                for (int i = 0; i < quant_barreiras_casa; i++) {

                    DrawRectangleLinesEx(barreiras_casa[i], 2, RED);

                }

                desenhar_debug_mouse(camera); // debug, tirar depois

            EndMode2D();

            DrawText("CASA DA DONA FLORINDA", 10, 10, 20, BLACK); // testando

        EndDrawing();

    }

    UnloadTexture(cenario_casa_florinda);
    descarregarjogador(&jogador);

}