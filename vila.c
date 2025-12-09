#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "vila.h"
#include "player.h"
#include "gerar_casa_florinda.h"
#include "fase1/fase1.h"

void rodar_vila(Player* chaves, Camera2D* camera, Texture2D* mapa_vila, Fase_selecionada* fase_selecionada, bool* selecionado) {

    // criando a hitbox da porta da dona florinda
    Rectangle porta_dona_florinda = { 1820, 515, 115, 230}; // seta a colisao da porta da dona florinda

    camera->target = chaves->pos;
        
        // verificar se o chaves colidiu com a porta da dona florinda
        int dialogo_porta_florinda = CheckCollisionRecs(porta_dona_florinda, chaves->hitbox);

        // condição para que o Chaves pare de andar quando chegar na porta da dona florinda
        if (!dialogo_porta_florinda) {

            atualizarjogador(chaves, NULL, 0);

        } else { // para deixar o chaves no estático inclusive na arte dele

            chaves->frameAtual = 0;

            if (IsKeyDown(KEY_ENTER)) { // avançando para a próxima fase
    
                *fase_selecionada = porta_florinda;
                *selecionado = true;
        
            } 

        }
        
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(*camera);

                // desenhando o mapa
                DrawTexture(*mapa_vila, 0, 0, WHITE);

                desenharjogador(chaves);
                DrawRectangleLinesEx(porta_dona_florinda, 1, RED);        // comando para verificar a hitbox

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


            }

            DrawText("VILA CENTRAL", 10, 10, 20, BLACK);

        EndDrawing();

}

Fase_selecionada executar_vila() {

    // CONFIGURAÇÕES INICIAIS
    Fase_selecionada fase_selecionada = erro; // coloca como erro para caso nada seja selecionado
    bool selecionado = false;

    // criando um bool temporário
    bool temp = false;

    Vector2 pos_chaves = {562, 1270};
    printf("\nEstá passando pela posição inicial!\n");

    Player chaves;
    setarjogador(&chaves, pos_chaves);

    // carregamento do mapa
    Image imagem_vila = LoadImage("imagens/mapa_vila.png");
    Texture2D mapa_vila = LoadTextureFromImage(imagem_vila);
    UnloadImage(imagem_vila); // liberando a imagem da RAM
    
    // inicialização da câmera 2D
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 1920 / 2.0f, 1080 / 2.0f }; //TODO mudar o 1920 e o 1080 para variáveis de largura e altura da tela
    camera.target = chaves.pos; // a câmera mira na posição do Chaves
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!selecionado && !WindowShouldClose()) { // flag e encerramento da janela
        
        rodar_vila(&chaves, &camera, &mapa_vila, &fase_selecionada, &selecionado);
        
        if ((fase_selecionada == porta_florinda) && !temp){ // caso o jogador tenha selecionado entrar na casa da dona florinda...
            
            carregar_casa_florinda(chaves, camera);

            temp = true;

            // quando acabar a casa da dona florinda, eu vou mudar o valor dessa variável
            fase_selecionada = erro;

            selecionado = false;
    
            chaves.pos = (Vector2){1820, 800};

            printf("\nEstá passando pelo final da fase da dona florinda\n");

        }
    }
    descarregarjogador(&chaves);

    UnloadTexture(mapa_vila);

    return fase_selecionada;
}
