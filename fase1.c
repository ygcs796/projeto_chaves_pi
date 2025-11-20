#include "fase1.h"
#include <raylib.h>
#include <stdbool.h>

void Executar_fase_1() {
    bool ingredientes[5] = {false};

    Rectangle botao_queijo    = { 200, 100, 80, 80 };
    Rectangle botao_molho     = { 200, 200, 80, 80 };
    Rectangle botao_calabresa = { 200, 300, 80, 80 };
    Rectangle botao_frango    = { 200, 400, 80, 80 };
    Rectangle botao_cebola    = { 200, 500, 80, 80 };

    while (!WindowShouldClose()) {

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

            if (CheckCollisionPointRec(mouse, botao_queijo))
                ingredientes[Queijo] = true;

            else if (CheckCollisionPointRec(mouse, botao_molho))
                ingredientes[Molho_de_tomate] = true;

            else if (CheckCollisionPointRec(mouse, botao_calabresa))
                ingredientes[Calabresa] = true;

            else if (CheckCollisionPointRec(mouse, botao_frango))
                ingredientes[Frango] = true;

            else if (CheckCollisionPointRec(mouse, botao_cebola))
                ingredientes[Cebola] = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(botao_queijo, YELLOW);
        DrawRectangleRec(botao_molho, RED);
        DrawRectangleRec(botao_calabresa, ORANGE);
        DrawRectangleRec(botao_frango, BLACK);
        DrawRectangleRec(botao_cebola, LIGHTGRAY);

        if (ingredientes[Queijo])
            DrawText("Queijo selecionado", 400, 100, 30, BLACK);

        if (ingredientes[Molho_de_tomate])
            DrawText("Molho selecionado", 400, 200, 30, BLACK);

        if (ingredientes[Calabresa])
            DrawText("Calabresa selecionada", 400, 300, 30, BLACK);

        if (ingredientes[Frango])
            DrawText("Frango selecionado", 400, 400, 30, BLACK);

        if (ingredientes[Cebola])
            DrawText("Cebola selecionada", 400, 500, 30, BLACK);

        EndDrawing();
    }
}
