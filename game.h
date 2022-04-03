#include "raylib.h"
#include "stdio.h"
/*
Screens id
10 -> Main Menu Screen
11 -> Gameplay Screen
12 -> Options Menu Screen
*/
void DrawGameplayScreen(){
    ClearBackground(BLACK);
    DrawText("JOOOOOOOOJ", 20, 140, 40, WHITE);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
