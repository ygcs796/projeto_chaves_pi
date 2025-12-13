#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "vila.h"
#include "player.h"
#include "gerar_casa_florinda.h"
#include "fase1/fase1.h"
#include "gerar_casa_bruxa.h"

static void desenhar_debug_mouse(Camera2D camera) { 
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("X: %.0f Y: %.0f", mouseWorld.x, mouseWorld.y), 
             GetScreenToWorld2D((Vector2){10, 10}, camera).x, 
             GetScreenToWorld2D((Vector2){10, 50}, camera).y, 
             20, RED);
}

Fase_selecionada executar_vila() {

    bool ganhou_fase_1 = false;
    bool ganhou_fase_2 = false;

    int dialogo_porta_florinda = 0;
    int dialogo_porta_bruxa = 0;

    Music musica_vila = LoadMusicStream("./musicas/Copper_on_the_beat.ogg");

    // CONFIGURAÇÕES INICIAIS
    Fase_selecionada fase_selecionada = erro; // coloca como erro para caso nada seja selecionado
    bool selecionado = false;

    Vector2 pos_chaves = {562, 1270};

    Player chaves;
    setarjogador(&chaves, pos_chaves);

    // carregamento do mapa
    Image imagem_vila = LoadImage("imagens/mapa_vila.png");
    Texture2D mapa_vila = LoadTextureFromImage(imagem_vila);
    UnloadImage(imagem_vila); // liberando a imagem da RAM

    // carregamento da porta da bruxa do 71
    Image imagem_porta_bruxa = LoadImage("imagens/portaBruxa.png");
    Texture2D porta_bruxa_tex = LoadTextureFromImage(imagem_porta_bruxa);
    UnloadImage(imagem_porta_bruxa);

    // carregando a seta pra direita
    Image seta_direita = LoadImage("imagens/seta_direita.png");
    ImageResize(&seta_direita, 77, 60);
    Texture2D seta_direita_tex = LoadTextureFromImage(seta_direita);
    UnloadImage(seta_direita);

    // carregando a seta pra cima
    Image seta_cima = LoadImage("imagens/seta_cima.png");
    ImageResize(&seta_cima, 60, 77);
    Texture2D seta_cima_tex = LoadTextureFromImage(seta_cima);
    UnloadImage(seta_cima);

    // inicialização da câmera 2D
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 1920 / 2.0f, 1080 / 2.0f }; //TODO mudar o 1920 e o 1080 para variáveis de largura e altura da tela
    camera.target = chaves.pos; // a câmera mira na posição do Chaves
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    PlayMusicStream(musica_vila);
    SetMusicVolume(musica_vila, 0.5);

    Rectangle porta_dona_florinda = { 1820, 515, 115, 230}; // seta a colisao da porta da dona florinda
    Rectangle porta_bruxa_71 = {2045, 680, 95, 215};

    Rectangle barreiras_vila[] = {  
        // CORRIMÃO DA ESCADA DA VILA
        {1370, 515, 5, 640},
        // BARREIRA DA PORTA DA ESCADA
        {1265, 475, 225, 25},
        // VASO MAIS ALTO DA ESCADA
        {1165, 500, 100, 75},
        // VASO DO MEIO DA ESCADA
        {1165, 825, 90, 90},
        // PAREDE DA ESCADA
        {1115, 500, 45, 645},
        // BEIRA DA PIA DE ROUPA
        {1505, 800, 5, 260},
        // BARRIL DO CHAVES
        {1385, 1045, 141, 195},
        // PRIMEIRO VASO DA FRENTE DA CASA DA FLORINDA
        {1585, 705, 90, 90},
        // SEGUNDO VASO DA FRENTE DA CASA DA FLORINDA
        {1680, 725, 90, 90},
        // PAREDE DA FRENTE DA CASA DA FLORINDA
        {1935, 740, 205, 5}, 
        // PAREDE LATERAL DA CASA AMARELA
        {2140, 745, 10, 150},
        // PAREDE DA FRENTE DA CASA AMARELA
        {2140, 890, 410, 5},
        // CASA DE BAIXO 
        {2039, 1176, 630, 450},
        {2112, 1142, 482, 35},
        {2176, 1106, 350, 40},
        {2232, 1045, 233, 35},
        {2328, 1017, 46, 15},
        // VASO 1 DA CASA AZUL
        {2595, 790, 115, 105},
        // VASO 2 DA CASA AZUL
        {3010, 795, 115, 105},
        // RETÂNGULO QUE INCLUI A PAREDE E A PORTA DA CASA AZUL
        {2710, 812, 300, 8},
        // PISCINA
        {2850, 1220, 280, 205},
        // VASO DO LADO DA CAIXA DE BAIXO
        {1905, 1215, 115, 105},
        // PRIMEIRA METADE DA PAREDE DE BAIXO DA VILA
        {409, 1460, 1641, 34},
        // RETÂNGULO QUE INCLUI 3 VASOS E A PAREDE DE CIMA DO LADO DA ESCADA
        {610, 1095, 550, 105},
        {371, 792, 748, 357}, // PAREDE AMARELA (DOS VASOS)
        // PAREDE LATERAL AMARELA
        {370, 792, 40, 945},
        // CASA 28
        {3171, 76, 446, 747},
        // ESCADA DA CASA 28
        {3263, 832, 274, 92},
        // PAREDE AMARELA INFERIOR (METADE QUE FALTAVA)
        {2661, 1462, 1217, 275},
        // MURO DA DIREITA
        {3780, 92, 96, 1372},
        // TRECHO DE LIMTIE SUPERIOR (ENTRE A CASA E O MURO DA DIREITA)
        {3617, 55, 263, 40},
        // CASA AZUL DO CANTO DIREITO
        {3450, 1114, 331, 348},
        {3509, 1060, 271, 50},
        {3591, 1023, 189, 32},
        {3696, 957, 85, 35}
    };

    while (/*!selecionado && */!WindowShouldClose()) { // flag e encerramento da janela
        
        UpdateMusicStream(musica_vila);

        // criando a hitbox da porta da dona florinda

        const int quant_barreiras = sizeof(barreiras_vila) / sizeof(barreiras_vila[0]);

        camera.target = chaves.pos;
        
        // verificar se o chaves colidiu com a porta da dona florinda

        if (!ganhou_fase_1) {

            dialogo_porta_florinda = CheckCollisionRecs(porta_dona_florinda, chaves.hitbox);

        } else {

            dialogo_porta_bruxa = CheckCollisionRecs(chaves.hitbox, porta_bruxa_71);

        }

        // condição para que o Chaves pare de andar quando chegar na porta da dona florinda
        if (!dialogo_porta_florinda && !dialogo_porta_bruxa) {

            atualizarjogador(&chaves, barreiras_vila, quant_barreiras);

        } else { // para deixar o chaves no estático inclusive na arte dele

            chaves.frameAtual = 0;

            if (dialogo_porta_florinda) {

                if (IsKeyDown(KEY_ENTER)) { // avançando para a próxima fase
        
                    fase_selecionada = porta_florinda;
                    selecionado = true;
            
                } 
            } else if (dialogo_porta_bruxa) {

                if (IsKeyDown(KEY_ENTER)) { // avançando para a próxima fase
        
                    fase_selecionada = porta_bruxa;
                    selecionado = true;
            
                } 

            }

        }
        
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                // desenhando o mapa
                DrawTexture(mapa_vila, 0, 0, WHITE);

                if (!ganhou_fase_1) {

                    DrawTexture(seta_cima_tex, 1850, 774, WHITE);

                } else if (!ganhou_fase_2) {

                    DrawTexture(seta_direita_tex, 1941, 774, WHITE);
                    DrawTexture(porta_bruxa_tex, 2030, 670, WHITE);
                    
                } 
                desenharjogador(&chaves);
                desenhar_debug_mouse(camera);


            EndMode2D();
            
            // DESENHO DO DIALOGO (PERGUNTA SE O JOGADOR QUER ENTRAR NA CASA DA DONA FLORINDA)
            if (dialogo_porta_florinda) {

                const char *texto_dialogo1 = "QUER ENTRAR NA CASA DA DONA FLORINDA?\n";
                const char *texto_dialogo2 = "ENTER para SIM";
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


            } else if (dialogo_porta_bruxa) {

                const char *texto_dialogo1 = "QUER ENTRAR NA CASA DA DONA CLOTILDE?\n";
                const char *texto_dialogo2 = "ENTER para SIM";
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
                
            }



            DrawText("VILA CENTRAL", 10, 10, 20, BLACK);

        EndDrawing();
        
        // 
        if ((fase_selecionada == porta_florinda)){ // caso o jogador tenha selecionado entrar na casa da dona florinda...
            
            ganhou_fase_1 = carregar_casa_florinda(&chaves, &camera);

            // quando acabar a casa da dona florinda, eu vou mudar o valor dessa variável
            fase_selecionada = erro;

            // selecionado = false;
    
            chaves.pos = (Vector2){1820, 800};

            dialogo_porta_florinda = 0;

        } else if (ganhou_fase_1 && fase_selecionada == porta_bruxa) {

            StopMusicStream(musica_vila);

            ganhou_fase_2 = gerar_casa_bruxa(&chaves, &camera);

            fase_selecionada = erro;

        } else if (ganhou_fase_2) break;
    }
    UnloadMusicStream(musica_vila);

    descarregarjogador(&chaves);

    UnloadTexture(mapa_vila);
    UnloadTexture(porta_bruxa_tex);
    UnloadTexture(seta_direita_tex);
    UnloadTexture(seta_cima_tex);

    return fase_selecionada;
}