#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "npc.h"
#include "fase1/fase1.h"
#include "fase1/tela_tutorial.h"
#include "gerar_florinda.h"

// a função abaixo indica as coordenadas do ponto em que o mouse está (aparece no canto superior esquerdo da tela, em vermelho)
void desenhar_debug_mouse(Camera2D camera) { // debug, tirar depois
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("X: %.0f Y: %.0f", mouseWorld.x, mouseWorld.y), 
             GetScreenToWorld2D((Vector2){10, 10}, camera).x, 
             GetScreenToWorld2D((Vector2){10, 50}, camera).y, 
             20, RED);
}

void carregar_casa_florinda(Player* jogador, Camera2D* camera) {

    bool fase_acabou = false;

    // Rectangle hitbox_florinda = {365, 980, jogador->hitbox.width, jogador->hitbox.height};

    NPC dona_florinda;
    
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

    setarjogador(jogador, pos_chaves);
    setar_dona_florinda(&dona_florinda);

    jogador->direcao = CIMA;
    bool cutscene_iniciada = false;

    while(!WindowShouldClose() && !fase_acabou) {
        
        bool colisao_chaves_florinda = CheckCollisionRecs(jogador->hitbox, dona_florinda.hitbox);

        // 2. ATUALIZE A TRAVA
        // Se colidiu E AINDA NÃO tinha iniciado a cutscene, trava agora.
        if (colisao_chaves_florinda && !cutscene_iniciada) {
            cutscene_iniciada = true;
            
            // Força a parada imediatamente UMA ÚNICA VEZ
            jogador->frameAtual = 0;
            jogador->interagindo = 1;
            jogador->moveTimer = 0.0f;
            jogador->pernaParaAndar = 0;
        }

        // 3. USE A TRAVA PARA DECIDIR O MOVIMENTO
        // Se a cutscene NÃO foi iniciada, ele pode andar.
        if (!cutscene_iniciada) {
            atualizarjogador(jogador, barreiras_casa, quant_barreiras_casa);
            camera->target = jogador->pos;
        } 
        // Não precisa de 'else' aqui porque a gente já setou as variáveis no passo 2
        
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(*camera);
                DrawTexture(cenario_casa_florinda, 0, 0, WHITE);
                desenharjogador(jogador);
                desenhar_dona_florinda(&dona_florinda, *jogador);
                // ... desenhar hitboxes ...
                desenhar_debug_mouse(*camera);
            EndMode2D();
            DrawText("CASA DA DONA FLORINDA", 10, 10, 20, BLACK);
        EndDrawing();

        // 4. VERIFICA A TRAVA PARA RODAR A PRÓXIMA FASE
        if (cutscene_iniciada) {
            Executar_fase_1();
            fase_acabou = true;
        }
    }

    UnloadTexture(cenario_casa_florinda);
    descarregarjogador(jogador);
    descarregar_dona_florinda(&dona_florinda);

}