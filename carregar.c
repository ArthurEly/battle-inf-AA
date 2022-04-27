#include "raylib.h"
#include "stdio.h"
#include "carregar.h"
#include "game.h"

void SetActiveScreen(int screen_id);

int count = 0;
char **droppedFiles = { 0 };

void att(void){
    if (IsFileDropped())
        {
            droppedFiles = GetDroppedFiles(&count);
        }
}

void DrawCarregarScreen(){
        att();
        ClearBackground(RAYWHITE);
        char objeto;
        if (count == 0) {
            DrawText("Drop your files to this window!", 100, 40, 20, DARKGRAY);
        }
        else
        {
            FILE *mapa_fp;
            mapa_fp = fopen(droppedFiles[0],"r");
            DrawLoadMapGameplayScreen(mapa_fp);
            printf("opafsdaaaaaafaafdsadsfafsdfsd\n");
            fclose(mapa_fp);
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
*/
