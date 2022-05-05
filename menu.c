#include "raylib.h"
#include "stdio.h"
#include "menu.h"
#include "game.h"
#include "main.h"

#define TEXTOS 5

int menu_option=0;

void DrawMainMenuScreen(GAME *jogo){
    const int menu_items[TEXTOS]={
        11,
        12,
        13,
        14,
        999
    };

    const char *escrita[TEXTOS] = {
        "Novo Jogo",
        "Carregar jogo",
        "Carregar Mapa",
        "Highscores",
        "Sair"
    };

    const int MENU_ITEMS_QTDY = sizeof(menu_items)/sizeof(menu_items[0]);

    ClearBackground(BLUE);
    int tamanho_fonte = 36;
    int i;

    Color optionColor = LIGHTGRAY;
    DrawTextureEx(jogo->texturas.menu_principal, (Vector2){-75,0}, 0, 1, WHITE);

    if(IsKeyPressed(KEY_DOWN) &&menu_option<MENU_ITEMS_QTDY-1){
       menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&menu_option>0){
       menu_option--;
    }

    for (i = 0; i < TEXTOS; i++){
        if(menu_option == i){
            optionColor = ORANGE;
            tamanho_fonte = 38;
        }else{
            optionColor = LIGHTGRAY;
            tamanho_fonte = 36;
        }
        DrawTextEx(jogo->fontes.fonte_legal, escrita[i], (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, escrita[i], tamanho_fonte, 2).x)/2), 400 + 50*i}, tamanho_fonte, 2, optionColor);
    }

    if(IsKeyPressed(KEY_ENTER)){
        if(menu_items[menu_option] != 999){
            SetActiveScreen(menu_items[menu_option]);
        }
        else{
            CloseWindow();
        }
    }
}


