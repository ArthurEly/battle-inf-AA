#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "carregar.h"
#include "highscores.h"
#include "pause_menu.h"
#include "stdio.h"

void SetActiveScreen(int screen_id);
void DrawScreen(int screen_id);

Texture2D escudo;
Texture2D texture;
Font fonte_legal;
Texture2D g_textura_jogador;
Texture2D g_textura_inimigo_patrulha;
Texture2D g_textura_inimigo_perseguicao;

const int tanque_altura_padrao = 50;
const int tanque_largura_padrao = 50;

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

    fonte_legal = LoadFontEx("assets/Ironmonger FB Extended.otf", 72, 0, 0);
    texture = LoadTexture("assets/Imagem padrao.png");
    escudo = LoadTexture("assets/shield.png");

    g_textura_jogador = LoadTexture("assets/tanque_player.png");
    g_textura_jogador.height = tanque_altura_padrao;
    g_textura_jogador.width = tanque_largura_padrao;

    g_textura_inimigo_patrulha = LoadTexture("assets/tanque_verde.png");
    g_textura_inimigo_patrulha.height = tanque_altura_padrao;
    g_textura_inimigo_patrulha.width = tanque_largura_padrao;

    g_textura_inimigo_perseguicao = LoadTexture("assets/tanque_inimigo.png");
    g_textura_inimigo_perseguicao.height = tanque_altura_padrao;
    g_textura_inimigo_perseguicao.width = tanque_largura_padrao;
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
            DrawCarregarScreen();
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
