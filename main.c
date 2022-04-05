#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "options.h"
#include "highscores.h"
#include "pause_menu.h"

void SetActiveScreen(int screen_id);
void DrawScreen(int screen_id);

int screens[5]={
        10, //Main Menu Screen
        11, //Gameplay Screen
        111, //menu de pausa dentro do jogo
        12, //Options Screen
        13  //Options Screen
    };
int active_screen = 10;
const int SCREENS_QTDY = sizeof(screens)/sizeof(screens[0]);

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Battle INF");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawScreen(active_screen);

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

        case 111:
            DrawPauseMenu();
            break;

        case 12:
            DrawOptionsScreen();
            break;

        case 13:
            DrawHighScoresScreen();
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
