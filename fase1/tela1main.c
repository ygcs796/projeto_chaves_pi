#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>
#include "fase1.h"
#include "tela1funcoes.h"

void executartela1() {

    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE;

    Texture2D fundo = LoadTexture("imagens/fundo_fase1_ambiente1.png");
    printf("Fundo: id=%d, w=%d, h=%d\n", fundo.id, fundo.width, fundo.height);



    SetRandomSeed(time(NULL));

    bool ingredientes[numero_de_ingredientes] = {false}; // vetor original dos vetores
    bool ingredientes_temp[numero_de_ingredientes] = {false}; // vetor dos ingredientes de cada config aleatoria

    Vector2 botao_champion    = { 53 * escala_x, 48 * escala_y};
    Vector2 botao_presunto    = { 53 * escala_x, 152 * escala_y};
    Vector2 botao_calabresa   = { 53 * escala_x, 256 * escala_y};
    Vector2 botao_frango      = { 53 * escala_x, 358 * escala_y};
    Vector2 botao_cebola      = { 53 * escala_x, 458 * escala_y};
    Rectangle botao_suco      = { 56 * escala_x, 524 * escala_y, 97 * escala_x, 158 * escala_y};
    Rectangle botao_refri      = { 197 * escala_x, 524 * escala_y, 97 * escala_x, 158 * escala_y};
    //Rectangle botao_de_selecao= { 500, 600, 80, 80 };

    const int raio_botoes_ingredientes = 46;
    
    gerar_config_de_igredientes(ingredientes_temp); // primeira geracao dos ingredientes

    float tempo_base_cronometro = GetTime(); // seta o primeiro tempo no relogio
    float cronometro = 0.0f; // define o cronometro
    bool ganhou = false; // tenho que tirar isso depois
    int vidas = 3;
    bool primeiro_loop = true;
    int dinheiro = 0;
    bool venceu_jogo = false;

    Texture2D lista_imagens_pizza[6];
    lista_imagens_pizza[5] = LoadTexture("imagens/pizza_queijo_e_molho.png");
    lista_imagens_pizza[0] = LoadTexture("imagens/cogumelos.png");
    lista_imagens_pizza[1] = LoadTexture("imagens/presunto (2).png");
    lista_imagens_pizza[2] = LoadTexture("imagens/calabresa.png");
    lista_imagens_pizza[3] = LoadTexture("imagens/frango2.png");
    lista_imagens_pizza[4] = LoadTexture("imagens/cebola (2).png");

    Texture2D correto_comanda = LoadTexture("imagens/sinal_de_correto_comanda_fase1.png");
    Texture2D x_bebidas = LoadTexture("imagens/x_verde_fase1_ambiente1.png");

    while (!WindowShouldClose() && vidas > 0 && !venceu_jogo) {

        Vector2 mouse = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

            // muda para os estados opostos
            if (CheckCollisionPointCircle(mouse, botao_champion, raio_botoes_ingredientes))
                ingredientes[Champion] = !ingredientes[Champion];

            else if (CheckCollisionPointCircle(mouse, botao_presunto, raio_botoes_ingredientes))
                ingredientes[Presunto] = !ingredientes[Presunto];

            else if (CheckCollisionPointCircle(mouse, botao_calabresa, raio_botoes_ingredientes))
                ingredientes[Calabresa] = !ingredientes[Calabresa];

            else if (CheckCollisionPointCircle(mouse, botao_frango, raio_botoes_ingredientes))
                ingredientes[Frango] = !ingredientes[Frango];

            else if (CheckCollisionPointCircle(mouse, botao_cebola, raio_botoes_ingredientes))
                ingredientes[Cebola] = !ingredientes[Cebola];
            
            else if (CheckCollisionPointRec(mouse, botao_suco))
                ingredientes[suco] = !ingredientes[suco];
            
            else if (CheckCollisionPointRec(mouse, botao_refri))
                ingredientes[refri] = !ingredientes[refri];
        }

        if(cronometro < 0.1f && !primeiro_loop){ //&& CheckCollisionPointRec(mouse, botao_de_selecao))) && !primeiro_loop){ // condicoes de encerramento
            ganhou = verificar_vitoria(ingredientes, ingredientes_temp);

                if(ganhou){ // se ganhou a rodada
                    dinheiro += retornar_dinheiro_rodada(ingredientes);
                }else{ // se perdeu
                    printf("perdeu vida");
                    vidas--;
                }
            gerar_config_de_igredientes(ingredientes_temp); // muda a config caso o tempo acabe
            tempo_base_cronometro = GetTime(); // muda o tempo base do cronometro(zera)

        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DesenharImagemFit(fundo);

            /*DrawRectangleRec(botao_champion, YELLOW);
            DrawRectangleRec(botao_presunto, RED);
            DrawRectangleRec(botao_calabresa, ORANGE);
            DrawRectangleRec(botao_frango, BLACK);
            DrawRectangleRec(botao_cebola, LIGHTGRAY);
            DrawRectangleRec(botao_de_selecao, GREEN);*/

            DrawTexture(lista_imagens_pizza[5], 354 * escala_x, 57 * escala_y, WHITE);
            printar_ingredientes(ingredientes, lista_imagens_pizza, x_bebidas);
            cronometro = desenhar_e_retornar_cronometro(tempo_base_cronometro);
            desenhar_dinheiro_e_vida(dinheiro, vidas);

            desenhar_conf_ingredientes(ingredientes_temp, correto_comanda);

        EndDrawing();

        if (dinheiro >= 200)
            venceu_jogo = true;

        primeiro_loop = false; // encerra a imunidade de tirar vida 
    }
}