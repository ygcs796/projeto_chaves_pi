#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include <time.h>
#include "fase1.h"
#include "tela1funcoes.h"

Info_rodada executartela1(Info_rodada info_rodada) {

    Music musicaTema = LoadMusicStream("musicas/fase1musicatema.mp3");
    Sound botaoIngredientes = LoadSound("musicas/selecaoingredientes.ogg");
    Sound botaoconfirmacao = LoadSound("musicas/confirmacaobotaofase1.ogg");
    Sound botaerro = LoadSound("musicas/errosubmissao.ogg");

    float escala_x = (float)GetScreenWidth()  / LARGURA_BASE;
    float escala_y = (float)GetScreenHeight() / ALTURA_BASE;

    float escala_x_FULL = (float)GetScreenWidth()  / LARGURA_BASE_FULL;
    float escala_y_FULL = (float)GetScreenHeight() / ALTURA_BASE_FULL;

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
    Rectangle botao_de_selecao= { 500 * escala_x, 600 * escala_y, 200 * escala_x, 133 * escala_y };

    const int raio_botoes_ingredientes = 46;
    
    gerar_config_de_igredientes(ingredientes_temp); // primeira geracao dos ingredientes

    float tempo_base_cronometro = GetTime(); // seta o primeiro tempo no relogio
    float cronometro = 0.0f; // define o cronometro
    bool ganhou = false; // tenho que tirar isso depois
    int vidas = info_rodada.vidas; // seta as vidas em relacao a rodada
    bool primeiro_loop = true;
    int dinheiro = info_rodada.dinheiro;

    int tempo_minimo_cronometro = GetRandomValue(4, 10);
    int tempo_maximo_cronometro = tempo_minimo_cronometro + GetRandomValue(1, 3); // gera um intervalo aleatorio entre 1 e 3 segs 
    
    char texto_tempo_comanda[10];

    sprintf(texto_tempo_comanda, "%02d - %02d", tempo_minimo_cronometro, tempo_maximo_cronometro); // defino a string que contem os intervalos de tempo de cozimento da pizza
    
    bool encerou_rodada = false;

    Texture2D lista_imagens_pizza[6];
    lista_imagens_pizza[5] = LoadTexture("imagens/pizza_queijo_e_molho.png");
    lista_imagens_pizza[0] = LoadTexture("imagens/cogumelos.png");
    lista_imagens_pizza[1] = LoadTexture("imagens/presunto (2).png");
    lista_imagens_pizza[2] = LoadTexture("imagens/calabresa.png");
    lista_imagens_pizza[3] = LoadTexture("imagens/frango2.png");
    lista_imagens_pizza[4] = LoadTexture("imagens/cebola.png");

    Texture2D correto_comanda = LoadTexture("imagens/sinal_de_correto_comanda_fase1.png");
    Texture2D x_bebidas = LoadTexture("imagens/x_verde_fase1_ambiente1.png");

    Texture2D imagem_botao_selecao = LoadTexture("imagens/Botao colocar .png");
    PlayMusicStream(musicaTema);

    while (!WindowShouldClose() && !encerou_rodada) {
        UpdateMusicStream(musicaTema);

        Vector2 mouse = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

            // muda para os estados opostos
            if (CheckCollisionPointCircle(mouse, botao_champion, raio_botoes_ingredientes)){
                PlaySound(botaoIngredientes);
                ingredientes[Champion] = !ingredientes[Champion];
            }

            else if (CheckCollisionPointCircle(mouse, botao_presunto, raio_botoes_ingredientes)){
                PlaySound(botaoIngredientes);
                ingredientes[Presunto] = !ingredientes[Presunto];}

            else if (CheckCollisionPointCircle(mouse, botao_calabresa, raio_botoes_ingredientes)){
                PlaySound(botaoIngredientes);
                ingredientes[Calabresa] = !ingredientes[Calabresa];}

            else if (CheckCollisionPointCircle(mouse, botao_frango, raio_botoes_ingredientes)){
                PlaySound(botaoIngredientes);
                ingredientes[Frango] = !ingredientes[Frango];}

            else if (CheckCollisionPointCircle(mouse, botao_cebola, raio_botoes_ingredientes)){
                PlaySound(botaoIngredientes);
                ingredientes[Cebola] = !ingredientes[Cebola];}
            
            else if (CheckCollisionPointRec(mouse, botao_suco)){
                PlaySound(botaoIngredientes);
                ingredientes[suco] = !ingredientes[suco];}
            
            else if (CheckCollisionPointRec(mouse, botao_refri)){
                PlaySound(botaoIngredientes);
                ingredientes[refri] = !ingredientes[refri];}
        }

        if((cronometro < 0.1f && !primeiro_loop) || (CheckCollisionPointRec(mouse, botao_de_selecao) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))){ //&& CheckCollisionPointRec(mouse, botao_de_selecao))) && !primeiro_loop){ // condicoes de encerramento
            ganhou = verificar_vitoria(ingredientes, ingredientes_temp);
            if(ganhou) PlaySound(botaoconfirmacao);
            else PlaySound(botaerro);
            encerou_rodada = true;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DesenharImagemFit(fundo);

            /*DrawRectangleRec(botao_champion, YELLOW);
            DrawRectangleRec(botao_presunto, RED);
            DrawRectangleRec(botao_calabresa, ORANGE);
            DrawRectangleRec(botao_frango, BLACK);
            DrawRectangleRec(botao_cebola, LIGHTGRAY);*/
            //rawRectangleRec(botao_de_selecao, GREEN);
            DrawTexture(imagem_botao_selecao, 500 * escala_x, 600 * escala_y, WHITE);
            
            DrawTexture(lista_imagens_pizza[5], 354 * escala_x, 57 * escala_y, WHITE);
            printar_ingredientes(ingredientes, lista_imagens_pizza, x_bebidas);
            cronometro = desenhar_e_retornar_cronometro(tempo_base_cronometro, escala_x_FULL, escala_y_FULL);
            desenhar_dinheiro_e_vida(dinheiro, vidas, escala_x_FULL, escala_y_FULL);

            DrawText(texto_tempo_comanda, 1753 * escala_x_FULL, 822 * escala_y_FULL, 40 * escala_x_FULL, BLACK); // printa o intervalo de cozimnto da pizza

            desenhar_conf_ingredientes(ingredientes_temp, correto_comanda);

        EndDrawing();


        primeiro_loop = false; // encerra a imunidade de tirar vida
    }

    Pizza pizza_da_rodada;
    for (int i = 0; i < numero_de_ingredientes; i++)
        pizza_da_rodada.ingredientes[i] = ingredientes_temp[i];

    pizza_da_rodada.tempo_de_cozimento[0] = tempo_minimo_cronometro;
    pizza_da_rodada.tempo_de_cozimento[1] = tempo_maximo_cronometro;

    info_rodada.dinheiro = dinheiro;
    info_rodada.vidas = vidas;
    info_rodada.pizza_atual = pizza_da_rodada;
    info_rodada.vitoria_parte_1 = ganhou;

    // Fundo
    UnloadTexture(fundo);

    // Texturas das pizzas
    for (int i = 0; i < 6; i++)
        UnloadTexture(lista_imagens_pizza[i]);

    // Outras texturas
    UnloadTexture(correto_comanda);
    UnloadTexture(x_bebidas);
    UnloadTexture(imagem_botao_selecao);
    UnloadMusicStream(musicaTema);

    UnloadSound(botaoconfirmacao);
    UnloadSound(botaoIngredientes);

    return info_rodada;
}