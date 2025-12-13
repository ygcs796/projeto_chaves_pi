#include <stdio.h>
#include "raylib.h"
#include "npc.h"
#include "player.h" 

void setar_bruxa_71(NPC* bruxa) {

    bruxa->position = (Vector2){834, 430};

    // medidas de 1 sprite da dona florinda
    bruxa->larguraFrame = 234;
    bruxa->alturaFrame = 200;
    
    // carregando os sprites
    bruxa->SpriteImage = LoadImage("imagens/DonaClotiude.png");
    bruxa->TexSprite = LoadTextureFromImage(bruxa->SpriteImage);
    UnloadImage(bruxa->SpriteImage);
    
    // alinhando a hitbox para ficar bem nos pés da dona florinda
    bruxa->hitbox.x = bruxa->position.x - (bruxa->larguraFrame / 2);
    bruxa->hitbox.y = bruxa->position.y - (bruxa->alturaFrame / 2);
    bruxa->hitbox.width = bruxa->larguraFrame;
    bruxa->hitbox.height = bruxa->alturaFrame;

}

void desenhar_bruxa_71(NPC* bruxa, Player chaves) {

    Rectangle sourceRec = {
        5,
        40,
        bruxa->larguraFrame,
        bruxa->alturaFrame
    };
    Rectangle destRec = {
        bruxa->position.x,
        bruxa->position.y,
        (float) bruxa->larguraFrame,
        (float) bruxa->alturaFrame
    };

    Vector2 origin = {destRec.width / 2, destRec.height / 2};

    DrawTexturePro(bruxa->TexSprite, sourceRec, destRec, origin, 0.0f, WHITE);

    DrawRectangleLinesEx(bruxa->hitbox, 2, RED);

}

void descarregar_bruxa_71(NPC* bruxa) {

    UnloadTexture(bruxa->TexSprite);

}