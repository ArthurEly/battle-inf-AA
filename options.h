#include "raylib.h"
#include "stdio.h"
/*
Screens id
10 -> Main Menu Screen
11 -> Gameplay Screen
12 -> Options Menu Screen
*/
void DrawOptionsScreen(){
    ClearBackground(WHITE);
    DrawText("Tamanho da janela: 1000 por 800", 20, 140, 40, BLACK);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
