#include "raylib.h"
#include "stdio.h"
#include "highscores.h"

void DrawHighScoresScreen(){
    ClearBackground(GREEN);
    DrawText("PONTNIHOS", 20, 140, 40, WHITE);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
