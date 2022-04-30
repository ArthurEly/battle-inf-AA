#include "raylib.h"
#include "stdio.h"
#include "carregar.h"
#include "game.h"

void SetActiveScreen(int screen_id);
//void DrawLoadMapGameplayScreen(GAME *jogo, FILE *mapa_fp);

int count = 0;
char **droppedFiles = { 0 };

void att(void){
    if (IsFileDropped())
        {
            droppedFiles = GetDroppedFiles(&count);
        }
}

void DrawCarregarScreen(GAME *jogo){
        att();
        ClearBackground(RAYWHITE);
        DrawTextureEx(jogo->texturas.carregar, (Vector2){-75,0}, 0, 1, WHITE);
        if (count == 0) {
        }
        else
        {
            FILE *mapa_fp;
            mapa_fp = fopen(droppedFiles[0],"r");
            if(mapa_fp != NULL){
                printf("%s\n",droppedFiles[0]);
                carregarMapa(jogo->mapa_inicial,mapa_fp);
            }else{
                perror("erro ao carregar um mapa ");
            }
            fclose(mapa_fp);
            jogo->mapa_foi_pre_carregado = TRUE;
            droppedFiles[0] = 0;
            count = 0;
            SetActiveScreen(11);
        }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
/*int count = 0;
    char **droppedFiles = { 0 };

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsFileDropped())
        {
            droppedFiles = GetDroppedFiles(&count);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (count == 0) DrawText("Drop your files to this window!", 100, 40, 20, DARKGRAY);
            else
            {
                DrawText("Dropped files:", 100, 40, 20, DARKGRAY);

                for (int i = 0; i < count; i++)
                {
                    if (i%2 == 0) DrawRectangle(0, 85 + 40*i, screenWidth, 40, Fade(LIGHTGRAY, 0.5f));
                    else DrawRectangle(0, 85 + 40*i, screenWidth, 40, Fade(LIGHTGRAY, 0.3f));

                    DrawText(droppedFiles[i], 120, 100 + 40*i, 10, GRAY);
                }

                DrawText("Drop new files...", 100, 110 + 40*count, 20, DARKGRAY);
            }
    }
*/
