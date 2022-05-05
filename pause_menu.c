#include "raylib.h"
#include "stdio.h"
#include "pause_menu.h"
#include "game.h"
#define TEXTOS 2

void SetActiveScreen(int screen_id);

int pause_menu_option=0;

void DrawPauseMenu(GAME *jogo){
    const int pause_menu_items[3]={
        11,
        110,
        10
    };

    const char *escrito[3] = {
        "Continuar jogo",
        "Reiniciar jogo",
        "Voltar ao menu"
    };

    const int PAUSE_MENU_ITEMS_QTDY = sizeof(pause_menu_items)/sizeof(pause_menu_items[0]);

    ClearBackground(RED);
    DrawTextureEx(jogo->texturas.pause, (Vector2){-75,0}, 0, 1, WHITE);
    Color optionColor = LIGHTGRAY;
    int tamanho_fonte = 36;

    if(IsKeyPressed(KEY_DOWN) &&pause_menu_option<PAUSE_MENU_ITEMS_QTDY-1){
       pause_menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&pause_menu_option>0){
       pause_menu_option--;
    }

    for (int i = 0; i < 3; i++){
        if(pause_menu_option == i){
            optionColor = ORANGE;
            tamanho_fonte = 38;
        }else{
            optionColor = LIGHTGRAY;
            tamanho_fonte = 36;
        }
        DrawTextEx(jogo->fontes.fonte_legal, escrito[i], (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, escrito[i], tamanho_fonte, 2).x)/2), 300 + 75*i}, tamanho_fonte, 2, optionColor);
    }
    if(IsKeyPressed(KEY_ENTER)){
        if(pause_menu_items[pause_menu_option] == 10){
            resetarJogo(jogo);
        }

        if(pause_menu_items[pause_menu_option] == 110){
            reiniciarJogo(jogo);
            SetActiveScreen(11);
        }

        SetActiveScreen(pause_menu_items[pause_menu_option]);
    }
}


