#include "raylib.h"
#include "stdio.h"
#include "highscores.h"
#include "game.h"

void SetActiveScreen(int screen_id);

void DrawHighScoresScreen(GAME *jogo){
    ClearBackground(GREEN);
    DrawTextureEx(jogo->texturas.highscore, (Vector2){-75,0}, 0, 1, WHITE);
    //DrawText("PONTNIHOS", 20, 140, 40, WHITE);
    DrawTextEx(jogo->fontes.fonte_legal, "Pontos: ", (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, "Pontos: ", 36, 2).x)/2), 300}, 36, 2, WHITE);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
