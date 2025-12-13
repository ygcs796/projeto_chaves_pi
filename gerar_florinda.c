#include <stdio.h>
#include "raylib.h"
#include "npc.h"
#include "player.h" 

void setar_dona_florinda(NPC* florinda) {

    florinda->position = (Vector2){399, 959};
    
    // alinhando a hitbox para ficar bem nos pés da dona florinda
    florinda->hitbox.x = 365;
    florinda->hitbox.y = 980;
    florinda->hitbox.width = 90;
    florinda->hitbox.height = 50;

    // carregando os sprites
    florinda->SpriteImage = LoadImage("imagens/DonaFlorindaSprite.png");
    florinda->TexSprite = LoadTextureFromImage(florinda->SpriteImage);
    UnloadImage(florinda->SpriteImage);
    
    // medidas de 1 sprite da dona florinda
    florinda->larguraFrame = 160;
    florinda->alturaFrame = 190;

}

void desenhar_dona_florinda(NPC* florinda, Player chaves) {

    Rectangle sourceRec = { // alternância entre os sprites de acordo com qual direção o jogador vai colidir com a dona florinda
        44, 
        80,
        (float) florinda->larguraFrame,
        (float) florinda->alturaFrame
    };

    Rectangle destRec = {
        florinda->position.x,
        florinda->position.y,
        (float) florinda->larguraFrame,
        (float) florinda->alturaFrame
    };

    Vector2 origin = {destRec.width / 2, destRec.height / 2};

    DrawTexturePro(florinda->TexSprite, sourceRec, destRec, origin, 0.0f, WHITE);

    DrawRectangleLinesEx(florinda->hitbox, 2, RED);

}

void descarregar_dona_florinda(NPC* florinda) {

    UnloadTexture(florinda->TexSprite);

}