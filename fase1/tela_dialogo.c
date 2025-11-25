#include <raylib.h>
#include <string.h>

int RodarDialogo(Texture2D imgA, Texture2D imgB, Texture2D imgCaixa, Font fonte, const char *falas[], int totalLinhas, const char *nomes[]) {
    
    // Variáveis estáticas para manter o estado da animação
    static int linhaAtual = 0;
    static int letrasAtuais = 0;
    static int frameCounter = 0;
    
    int velocidadeDigitar = 3; 

    frameCounter++;
    
    // Efeito de digitação
    if (frameCounter >= velocidadeDigitar) {
        letrasAtuais++;
        frameCounter = 0;
    }

    // Para o jogador conseguir adiantar o diálogo
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        int tamanhoFrase = strlen(falas[linhaAtual]);

        // Se ainda está digitando, completa a frase instantaneamente
        if (letrasAtuais < tamanhoFrase) {
            letrasAtuais = tamanhoFrase;
        }
        // Se já terminou, passa para a próxima linha
        else {
            linhaAtual++;
            letrasAtuais = 0;
            
            // Se acabaram as falas, retorna 1 (FIM)
            if (linhaAtual >= totalLinhas) {
                linhaAtual = 0; // Reseta para o futuro
                return 1; 
            }
        }
    }

    BeginDrawing();

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.8f));

        // Posicionando a caixa de diálogo
        int yCaixa = GetScreenHeight() - imgCaixa.height; 
        DrawTexture(imgCaixa, 0, yCaixa, WHITE);

        // Decidindo qual personagem fala 
        Texture2D avatarAtual;
        const char *nomeAtual;
        
        if (linhaAtual % 2 == 0) {
            avatarAtual = imgA;
            nomeAtual = nomes[0];
        } else {
            avatarAtual = imgB;
            nomeAtual = nomes[1];
        }
        int yAvatar = yCaixa + (imgCaixa.height - avatarAtual.height) / 2;
        
        DrawTexture(avatarAtual, 20, yAvatar, WHITE);

        Vector2 posicaoTexto = {250, yCaixa + 50};
    
        float tamanhoFonte = 20.0f; 
        float espacamento = 2.0f;   

        DrawTextEx(fonte, TextSubtext(falas[linhaAtual], 0, letrasAtuais), posicaoTexto, tamanhoFonte, espacamento, WHITE);

        // Instrução
        DrawText("Pressione ESPAÇO...", GetScreenWidth() - 150, GetScreenHeight() - 20, 10, GRAY);

    EndDrawing();

    return 0; // retornando 0 enquanto o diálogo não acaba 
}

int RodarCenaInicial(void) {
    
    static bool inicializado = false;

    // Recursos (Memória)
    static Texture2D texChaves;
    static Texture2D texFlorinda;
    static Texture2D texCaixaDialogo;
    static Font fontePixel;

    // Dados do Roteiro
    static const char *falas[] = {
        "Dona Florinda, Dona Florind... eu perdi a chave\nda minha casa. Você pode me ajudar?",           
        "Cha… chaves!?! Que susto, posso lhe ajudar,\nmas antes preciso de um favor seu.",                  
        "Favor?",     
        "Preciso sair agora e você vai cuidar do meu\nrestaurante. E trate de não perder nenhuma das\ntrês estrelas Michelin, entendido?",
        "Logo EU?! Mas eu já perdi até a minha chave,\nimagina três estrelas!",
        "Pois trate de não perder mais nada!",
        "Tá bom... mas, se eu achar a minha chave no\ncaminho, eu posso perder só um pouquinho\na atenção?",
        "CHAVES!!!!!",
        "Tá bom, tá bom! Cuido das estrelas primeiro…\ndepois da minha chave..."

    };
    static const char *nomes[] = { "CHAVES", "DONA FLORINDA" };
    static int totalFalas = 9;

    if (!inicializado) {
        // Carregando Chaves
        Image img1 = LoadImage("imagens/foto_chaves_dialogo.png");
        ImageResize(&img1, 200, 200); // Tamanho do avatar
        texChaves = LoadTextureFromImage(img1);
        UnloadImage(img1);

        // Carregando Dona Florinda
        Image img2 = LoadImage("imagens/dona_florinda_foto.png");
        ImageResize(&img2, 200, 200);
        texFlorinda = LoadTextureFromImage(img2);
        UnloadImage(img2);

        // Carregando a caixa de diálogo
        Image img3 = LoadImage("imagens/caixa_de_dialogo.png");
        
        ImageResize(&img3, GetScreenWidth(), 200);
        texCaixaDialogo = LoadTextureFromImage(img3);
        UnloadImage(img3);

        fontePixel = LoadFontEx("fase1/fontes/VCR_OSD_MONO_1.001.ttf", 32, 0, 250);
        
        // Usando filter point para ajudar na nitidez da imagem
        SetTextureFilter(fontePixel.texture, TEXTURE_FILTER_POINT);

        inicializado = true;
    }

    int status = RodarDialogo(texChaves, texFlorinda, texCaixaDialogo, fontePixel, falas, totalFalas, nomes);

    if (status == 1) {
        
        UnloadTexture(texChaves);
        UnloadTexture(texFlorinda);
        UnloadTexture(texCaixaDialogo);
        UnloadFont(fontePixel);
        
        inicializado = false; 

        return 1; // CÓDIGO DA PRÓXIMA TELA (Ex: 1 = Vila)
    }

    return 10; // CÓDIGO DESTA TELA (Ex: 10 = Cutscene)
}

// ==========================================================
// ÁREA DE TESTE TEMPORÁRIA
// (Apague ou comente tudo isso abaixo quando for juntar com o jogo oficial!)
// ==========================================================

int main(void) {
    InitWindow(1000, 600, "TESTE RAPIDO DIALOGO");
    SetTargetFPS(60);

    // Loop simples só para rodar sua cena
    while (!WindowShouldClose()) {
        
        int resultado = RodarCenaInicial();

        // Se acabou, fecha
        if (resultado == 1) { 
            break; 
        }
    }

    CloseWindow();
    return 0;
}