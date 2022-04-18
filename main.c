#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "options.h"
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

const int g_altura_tanques = 40/2;
const int g_largura_tanques = 40/2;

int g_screens[6]={
        10, //Main Menu Screen
        11, //Gameplay Screen
        111, //menu de pausa dentro do jogo
        12, //Continue Screen
        13, //Load Map Screen
        14,  //HighScore Screen
    };
int g_active_screen = 11;

const int SCREENS_QTDY = sizeof(g_screens)/sizeof(g_screens[0]);

int main(void)
{
    const int screenHeight = 710;
    const int screenWidth = 1130;

    InitWindow(screenWidth, screenHeight, "Battle INF");

    SetTargetFPS(60);

    fonte_legal = LoadFontEx("assets/Ironmonger FB Extended.otf", 72, 0, 0);
    texture = LoadTexture("assets/Imagem padrao.png");
    escudo = LoadTexture("assets/shield.png");

    g_textura_jogador = LoadTexture("assets/tanque_player.png");
    g_textura_jogador.height = g_altura_tanques;
    g_textura_jogador.width = g_largura_tanques;

    g_textura_inimigo_patrulha = LoadTexture("assets/tanque_verde.png");
    g_textura_inimigo_patrulha.height = g_altura_tanques;
    g_textura_inimigo_patrulha.width = g_largura_tanques;

    g_textura_inimigo_perseguicao = LoadTexture("assets/tanque_inimigo.png");
    g_textura_inimigo_perseguicao.height = g_altura_tanques;
    g_textura_inimigo_perseguicao.width = g_largura_tanques;


    Camera2D camera = { 0 };
    camera.target = (Vector2){ 500, 400};
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            BeginMode2D(camera);
            DrawScreen(g_active_screen);
            EndMode2D();
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
