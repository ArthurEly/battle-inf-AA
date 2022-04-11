#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "options.h"
#include "highscores.h"
#include "pause_menu.h"
#include "stdio.h"

void SetActiveScreen(int screen_id);
void DrawScreen(int screen_id);

Texture2D g_tank_texture;

int g_screens[6]={
        10, //Main Menu Screen
        11, //Gameplay Screen
        111, //menu de pausa dentro do jogo
        12, //Continue Screen
        13, //Load Map Screen
        14,  //HighScore Screen
    };
int g_active_screen = 10;

const int SCREENS_QTDY = sizeof(g_screens)/sizeof(g_screens[0]);

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Battle INF");

    SetTargetFPS(60);
    /*
    carregamento dos recursos do jogo
    */
    g_tank_texture = LoadTexture("assets/tanque_player.png");
    g_tank_texture.height = 100;
    g_tank_texture.width = 100;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawScreen(g_active_screen);
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
            DrawGameplayScreen();
            break;

        case 13:
        DrawHighScoresScreen();
        break;

        case 14:
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
        if (g_screens[i] == screen_id){
            g_active_screen = screen_id;
        }
    }
}
