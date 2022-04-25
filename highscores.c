#include "raylib.h"
#include "stdio.h"
#include "highscores.h"

void SetActiveScreen(int screen_id);
extern Texture2D highscore;
extern Font fonte_legal;


void DrawHighScoresScreen(){
    ClearBackground(GREEN);
    DrawTextureEx(highscore, (Vector2){-75,0}, 0, 1, WHITE);
    //DrawText("PONTNIHOS", 20, 140, 40, WHITE);
    DrawTextEx(fonte_legal, "Pontos: ", (Vector2){(565 - (MeasureTextEx(fonte_legal, "Pontos: ", 36, 2).x)/2), 300}, 36, 2, WHITE);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
