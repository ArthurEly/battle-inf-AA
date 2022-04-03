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
    DrawText("opcaos kkkkk", 20, 140, 40, BLACK);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
