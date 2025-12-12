#include "executar_batalha.h"

void executarBatalha(Bixomon *player, Bixomon *oponente){
    Music somBatalha = LoadMusicStream("musicas/musicabatalha.WAV");

    Texture2D fundoBatalha = LoadTexture("imagens/fundoBatalha.png");

    Rectangle botao_ataque = {1000, 300, 50, 50};
    Rectangle botao_mochila = {700, 300, 50, 50};

    Rectangle botoesDeAtaquePlayer[] = {{1000, 200, 50, 50}, {1000, 300, 50, 50}, {1000, 400, 50, 50}, {1000, 500, 50, 50}};

    Item itens[] = { {"Pocao de Vida", 3, 15, Cura}, {"Pocao de pp", 2, 5, PP}};
    int numItens = 2; // tamanho do vetor de intens

    Tela tela = Menu;

    int acao_telas = -1; // vou reutilizar essa variavel para receber as acoes das telas especificas
    bool acaoRealizadaPlayer = false;
    bool acaoRealizadaOponente = false;

    bool botaoEmPressao = false;
    PlayMusicStream(somBatalha);

    while(!WindowShouldClose() && (player->vida > 0 && oponente->vida > 0)){
        UpdateMusicStream(somBatalha);

            Vector2 posicao_mouse = GetMousePosition();
            //----------------------------------------------------------------
                    if(acaoRealizadaOponente || (!acaoRealizadaPlayer && (player->velocidade >= oponente->velocidade))){
                        
                        if(tela == Menu){
                            tela = menu_batalha(player, oponente, posicao_mouse, botao_ataque, &botaoEmPressao, botao_mochila, fundoBatalha);

                        }else { // se for realizada uma acao
                            if(tela == selecionarAtaques){
                                if((tela = receber_ataque(&player, &oponente, botoesDeAtaquePlayer, posicao_mouse, &botaoEmPressao, fundoBatalha)) == Menu)
                                    acaoRealizadaPlayer = true;
                                if(tela == NaoAcao) tela = Menu; // se o jogador nao agir volta ao menu sem concluir o turno
                            }else if(tela == Mochila){
                                tela = executar_mochila(&player, itens, numItens, posicao_mouse);
                                if(tela == NaoAcao) tela = Menu;
                                else if(tela == Menu) acaoRealizadaPlayer = true;
                            }
                            
                        }
                    }else{
                        BeginDrawing();
                            ClearBackground(WHITE);
                            printarFundoBatalha(player, oponente, fundoBatalha);
                            DrawText("oponente atacou", 500, 500, 30, BLACK);
                        EndDrawing();
                        PausarMs(1000);
                            acao_telas = GetRandomValue(0, 1); // 0 cura 10,  1 dá dano aleatorio
                            if(acao_telas){
                                player->vida -= oponente->ataques[GetRandomValue(0, 3)].dano; // da o dano de um ataque aleatorio do oponente
                                //printf("ATACOU!!!");
                            }else{
                                if(oponente->vida_MAX - oponente->vida <= 25) oponente->vida = oponente->vida_MAX;
                                else oponente->vida += 25;
                                //printf("CUROU!!!!!");
                        }
                        acaoRealizadaOponente = true;
                    }
                        if(acaoRealizadaOponente && acaoRealizadaPlayer){ // reseta  turno se ele foi concluido
                        acaoRealizadaPlayer = false; // reseta o turno
                        acaoRealizadaOponente = false;
                    }
    }
            


        BeginDrawing();
            ClearBackground(BLACK);
            if(player->vida > 0) DrawText("Vitoria!", 700, 350, 100, GREEN);
            else DrawText("Derrota", 700 ,350, 100, RED);
        EndDrawing();
        PausarMs(5000);
    
        UnloadTexture(fundoBatalha);
        UnloadMusicStream(somBatalha);
    }

void printarFundoBatalha(Bixomon *player, Bixomon *oponente, Texture2D fundoBatalha){ // funcao para printar o fundo

    char transferencia[50];

    DrawTexture(fundoBatalha, 0, 0, WHITE);
    sprintf(transferencia, "%d/%d", player->vida, player->vida_MAX);
    DrawText(transferencia, 1100, 460, 40, BLACK);
    DrawText(player->nome, 803, 360, 50, BLACK);

    sprintf(transferencia, "%d/%d", oponente->vida, oponente->vida_MAX); 
    DrawText(transferencia, 414, 95, 40, BLACK);
    DrawText(oponente->nome, 114, 90, 50, BLACK);
}

int menu_batalha(Bixomon *player, Bixomon *oponente, Vector2 posicao_mouse, Rectangle botao_ataque, bool *botaoEmPressao, Rectangle botao_mochila, Texture2D fundoBatalha){
    int acao = Menu; // acao padrao, continua no menu

    BeginDrawing();

        ClearBackground(WHITE);

        printarFundoBatalha(player, oponente, fundoBatalha);

        if(*botaoEmPressao == false){
            if(CheckCollisionPointRec(posicao_mouse, botao_ataque) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) acao = selecionarAtaques; // se o botao de ataque for pressionado 
            if(CheckCollisionPointRec(posicao_mouse, botao_mochila) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) acao = Mochila; // se o botao de mochila for pressionado 

        }else{
            if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) *botaoEmPressao = false; // chega se o botao foi solto
        }

        DrawRectangleRec(botao_ataque, GREEN);
        DrawRectangleRec(botao_mochila, GREEN);

    EndDrawing();
    return acao;
}

int receber_ataque(Bixomon **player, Bixomon **oponente, Rectangle botoesAtaques[], Vector2 posicaoMouse, bool *botaoEmPressao, Texture2D fundoBatalha){
    int acao = selecionarAtaques; // seta o default como nao acao
    char transferencia[50];

    Rectangle botaoMenu = {1000, 600, 50, 50};

    BeginDrawing();

        ClearBackground(WHITE);

        printarFundoBatalha(*player, *oponente, fundoBatalha);

        DrawRectangleRec(botaoMenu, BLUE);

        DrawRectangleRec(botoesAtaques[0], RED);
        DrawRectangleRec(botoesAtaques[1], BLUE);
        DrawRectangleRec(botoesAtaques[2], PURPLE);
        DrawRectangleRec(botoesAtaques[3], ORANGE);

        for(int i = 0; i < 4; i++){
            sprintf(transferencia, "%s(%d)->%d", (*player)->ataques[i].nome, (*player)->ataques[i].pp, (*player)->ataques[i].dano);
            DrawText(transferencia, botoesAtaques[i].x, botoesAtaques[i].y, 30, BLACK);
        }
    
    EndDrawing();

    for(int i = 0; i < 4; i++) // verifica qual botao foi pressionado, aplica o dano, segura o mouse e lanca a var de acao para o menu
        if(CheckCollisionPointRec(posicaoMouse, botoesAtaques[i]) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            if((*player)->ataques[i].pp > 0){ // caso ainda haja pp(caso o ataque aind apossa ser usado)
                (*oponente)->vida -= (*player)->ataques[i].dano;
                acao = Menu; // muda a variavel para retornar o menu com acao
                *botaoEmPressao = true;
                (*player)->ataques[i].pp--; // retira 1 de pp do ataque usado
            }
        }

    if(CheckCollisionPointRec(posicaoMouse, botaoMenu) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) acao = NaoAcao;

    return acao;
}

int executar_mochila(Bixomon **player, Item itens[], int numItens, Vector2 posicaoMouse){

    int acao = Mochila;

    char tranferencia[50]; //somente para passar o valores de cada

    Rectangle botaoMenu = {1000, 600, 50, 50};
    Rectangle botaoItens;

    

    BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangleRec(botaoMenu, BLUE);
        for(int i = 0; i < numItens; i++){
            botaoItens = (Rectangle){200, 100 + (i*50), 400, 30};
            DrawRectangleRec(botaoItens, RED);
            sprintf(tranferencia, "%s(%d)", itens[i].nome, itens[i].qtd);
            DrawText(tranferencia, 200, 100 + (i*50), 30, BLACK);
            if(CheckCollisionPointRec(posicaoMouse, botaoItens) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                acao = Menu;
                if(itens[i].tipoItem == Cura){
                    if((*player)->vida_MAX - (*player)->vida <= itens[i].module) (*player)->vida = (*player)->vida_MAX;
                    else (*player)->vida += itens[i].module;
                } // cura se o item for de cura

                else if(itens[i].tipoItem == PP){ 
                    int indice_atq = GetRandomValue(0, 3);
                    int recuperacao_pp;
                    if((*player)->ataques[indice_atq].pp_MAX - (*player)->ataques[indice_atq].pp < itens[i].module){ // se o pp a ser recuperado for menor que a quantiadade quea pocao recupera
                        recuperacao_pp = (*player)->ataques[indice_atq].pp_MAX - (*player)->ataques[indice_atq].pp;
                    }else recuperacao_pp = itens[i].module;
                    (*player)->ataques[indice_atq].pp+= recuperacao_pp;
                }
                 itens[i].qtd--;
            }
        }
    EndDrawing();

    if(CheckCollisionPointRec(posicaoMouse, botaoMenu) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) acao = NaoAcao;

    return acao;

}

void PausarMs(int ms) {
    double inicio = GetTime();         
    double duracao = ms / 1000.0; // mili para segundos

    while (GetTime() - inicio < duracao) {  // enrola
    
    }
}
