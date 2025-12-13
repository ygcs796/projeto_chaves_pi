#include <stdio.h>
#include "raylib.h"
#include "player.h"
#include "npc.h"
#include "gerar_bruxa_71.h"
#include "fase1/fase1.h"
#include "fase2/executar_batalha.h"

int gerar_casa_bruxa(Player* jogador, Camera2D* camera) {

    bool ganhou_fase_2 = false;
    bool fase_acabou = false;

    Item itens[] = { {"Pocao de Vida", 7, 15, Cura}, {"Pocao de pp", 5, 5, PP}};
    Bixomon chaves, barriga, girafales, kiko, nhonho;

    NPC bruxa_71;

    Image imagem_inimigos = LoadImage("./imagens/inimigos_rpg.png");
    Texture inimigos = LoadTextureFromImage(imagem_inimigos);
    UnloadImage(imagem_inimigos);
    Rectangle hitbox_inimigos = {1078, 486, 447, 182};
    
    Image imagem_casa_bruxa = LoadImage("./imagens/casaBruxa.png");
    Texture cenario_casa_bruxa = LoadTextureFromImage(imagem_casa_bruxa);
    UnloadImage(imagem_casa_bruxa);

    Rectangle barreiras_casa[] = {
        // PAREDE LATERAL INICIAL
        {250, 0, 64, 656},
        // PAREDE DE TRÁS INICIAL
        {60, 0, 190, 221},
        // PAREDE ESQUERDA
        {0, 0, 60, 1136},
        // PAREDE DE BAIXO
        {0, 836, 1835, 84},
        bruxa_71.hitbox,
    };

    const int quant_barreiras_casa = sizeof(barreiras_casa) / sizeof(barreiras_casa[0]);

    Vector2 pos_chaves = {160, 267}; // testando

    setarjogador(jogador, pos_chaves);
    setar_bruxa_71(&bruxa_71);

    jogador->direcao = BAIXO;
    bool cutscene_iniciada = false;
    bool falou_com_a_bruxa = false;

    while(!WindowShouldClose() && !fase_acabou) {

        bool colisao_chaves_inimigos = CheckCollisionRecs(jogador->hitbox, hitbox_inimigos);
        
        bool colisao_chaves_bruxa = CheckCollisionRecs(jogador->hitbox, bruxa_71.hitbox);

        // 2. ATUALIZE A TRAVA
        // Se colidiu E AINDA NÃO tinha iniciado a cutscene, trava agora.
        if (colisao_chaves_bruxa && !cutscene_iniciada && !falou_com_a_bruxa) {
            cutscene_iniciada = true;
            
            // Força a parada imediatamente UMA ÚNICA VEZ
            jogador->frameAtual = 0;
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
                DrawTexture(cenario_casa_bruxa, 0, 0, WHITE);
                desenhar_bruxa_71(&bruxa_71, *jogador);
                desenharjogador(jogador);
                DrawTexture(inimigos, 1078, 486, WHITE);
                // ... desenhar hitboxes ...
                DrawRectangleLinesEx(bruxa_71.hitbox, 3, RED);
            EndMode2D();
            DrawText("CASA DA BRUXA DO 71", 10, 10, 20, BLACK);
            
            // 4. VERIFICA A TRAVA PARA RODAR A PRÓXIMA FASE
            if (cutscene_iniciada) {
                const char *texto_dialogo1 = "CHAVES!!! EU PRECISO DA SUA AJUDA PARA ENFRENTAR ESSES 4 INIMIGOS!!!\n";
                const char *texto_dialogo2 = "TOME MEU CACHORRO SATANÁS! ELE IRÁ TE AJUDAR! (Aperte ENTER para continuar)";
                int largura_texto = MeasureText(texto_dialogo1, 30);
                int largura_texto_2 = MeasureText(texto_dialogo2, 30);
                
                // Coordenadas de centro da tela
                int centro_x = 1920 / 2;
                int centro_y = 1080 / 2;
                
                // Desenha o fundo da caixa de diálogo (um retângulo)
                DrawRectangle(centro_x - (largura_texto / 2) - 20, centro_y + 150, 750, 120, Fade(BLACK, 0.8f));
                
                // Desenha o texto (usando o MeasureText para centralizar o texto no retângulo)
                DrawText(texto_dialogo1, centro_x - largura_texto/2, centro_y + 175, 30, WHITE);
                DrawText(texto_dialogo2, centro_x - (largura_texto_2 / 2), centro_y + 220, 30, WHITE);
                
                if (IsKeyPressed(KEY_ENTER)) {
                    
                    falou_com_a_bruxa = true;
                    cutscene_iniciada = false;
                    
                }
                
            }
        EndDrawing();

        if (colisao_chaves_inimigos) {

            int ganhando = executarBatalha(&chaves, &nhonho, itens, 4);

            if (ganhando) {

                ganhando = executarBatalha(&chaves, &girafales, itens, 2);

                if (ganhando) {
                
                    ganhando = executarBatalha(&chaves, &barriga, itens, 1);

                    if (ganhando) {

                        ganhando = executarBatalha(&chaves, &kiko, itens, 3);
                        if (ganhando) {

                            ganhou_fase_2 = 1;

                        } else {

                            ganhou_fase_2 = 0;
                            fase_acabou = 1;

                        }
                    } else {

                        ganhou_fase_2 = 0;
                        fase_acabou = 1;

                    }
                } else {

                ganhou_fase_2 = 0;
                fase_acabou = 1;

            }

            } else {

                ganhou_fase_2 = 0;
                fase_acabou = 1;

            }

        }
    }

    UnloadTexture(cenario_casa_bruxa);

    jogador->interagindo = 0; // para destravar o movimento
    jogador->frameAtual = 0; // reseta visualmente para parado
    jogador->direcao = BAIXO; // para ele olhar para fora da casa quando sair dela

    descarregarjogador(jogador);
    descarregar_bruxa_71(&bruxa_71);

    return ganhou_fase_2;
}
