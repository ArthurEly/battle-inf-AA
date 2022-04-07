#include "raylib.h"
#include "stdio.h"

void DrawOptionsScreen(){
    ClearBackground(WHITE);
    DrawText("Tamanho da janela: 1000 por 800", 20, 140, 40, BLACK);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
