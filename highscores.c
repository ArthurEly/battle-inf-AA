#include "raylib.h"
#include "stdio.h"
#include "highscores.h"
#include "game.h"
#include "construcao.h"

#define NUM_FRAMES_PER_LINE     4
#define NUM_LINES               4

void SetActiveScreen(int screen_id);

int frames=0;
int currentFrame = 0;
int currentLine = 0;
int som=0;

void DrawHighScoresScreen(GAME *jogo){
    if (som == 0){
            PlaySound(jogo->sons.boom);
    }
    som++;
    if (som == 47){
        som = 0;
    }

    float frameWidth = (float)(jogo->texturas.explosa.width/NUM_FRAMES_PER_LINE);
    float frameHeight = (float)(jogo->texturas.explosa.height/NUM_LINES);
    Rectangle frameRec = {0, 0, frameWidth, frameHeight};
    ClearBackground(GREEN);
    DrawTextureEx(jogo->texturas.highscore, (Vector2){-75,0}, 0, 1, WHITE);
    frames++;
            if (frames > 2)
            {
                currentFrame++;

                if (currentFrame >= NUM_FRAMES_PER_LINE)
                {
                    currentFrame = 0;
                    currentLine++;

                    if (currentLine >= NUM_LINES)
                    {
                        currentLine = 0;
                    }
                }

                frames = 0;
            }

    frameRec.x = frameWidth*currentFrame;
    frameRec.y = frameHeight*currentLine;
    DrawTextureRec(jogo->texturas.explosa, frameRec, (Vector2){0,0}, WHITE);
    //DrawText("PONTNIHOS", 20, 140, 40, WHITE);
    DrawTextEx(jogo->fontes.fonte_legal, "Pontos: ", (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, "Pontos: ", 36, 2).x)/2), 300}, 36, 2, WHITE);

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
