#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "options.h"

#define SCREENS_QTDY 3
/*
Screens id
10 -> Main Menu Screen
11 -> Gameplay Screen
12 -> Options Menu Screen
*/
int screens[SCREENS_QTDY]={
        10, //Main Menu Screen
        11, //Gameplay Screen
        12, //Options Screen
    };
int active_screen = 10;

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    int i = 0;

    InitWindow(screenWidth, screenHeight, "Battle INF");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            switch(active_screen){
                case 10:
                    DrawScreen(10);
                    break;

                case 11:
                    DrawScreen(11);
                    break;

                case 12:
                    DrawScreen(12);
                    break;
            }
        EndDrawing();
    }

    CloseWindow();


    return 0;
}

void DrawScreen(int screen_id){
    switch(screen_id){
        case 10:
            DrawMainMenuScreen();
            break;

        case 11:
            DrawGameplayScreen();
            break;

        case 12:
            DrawOptionsScreen();
            break;

        default:
            printf("Não existe tela com esse id");
            break;
    }
}

void SetActiveScreen(int screen_id){
    int i;
    for(i=0;i<SCREENS_QTDY; i++){
        if (screens[i] == screen_id){
            active_screen = screen_id;
        }
    }
}
