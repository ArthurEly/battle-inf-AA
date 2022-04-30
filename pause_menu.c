#include "raylib.h"
#include "stdio.h"
#include "pause_menu.h"
#include "game.h"
#define TEXTOS 2

void SetActiveScreen(int screen_id);

int pause_menu_option=0;

void DrawPauseMenu(GAME *jogo){
    const int pause_menu_items[2]={10,11};
    const int PAUSE_MENU_ITEMS_QTDY = sizeof(pause_menu_items)/sizeof(pause_menu_items[0]);

    const char *escrito[2] = {"Voltar para o menu",
                              "Voltar para o jogo"};

    ClearBackground(RED);
    DrawTextureEx(jogo->texturas.pause, (Vector2){-75,0}, 0, 1, WHITE);
    Color optionColor = LIGHTGRAY;

    if(IsKeyPressed(KEY_DOWN) &&pause_menu_option<PAUSE_MENU_ITEMS_QTDY-1){
       pause_menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&pause_menu_option>0){
       pause_menu_option--;
    }

   /* if(pause_menu_option == 0){
        optionColor = GREEN;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Volta pro menu", 20, 20, 40, optionColor);

    if(pause_menu_option == 1){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Volta pro game", 20, 140, 40, optionColor);*/

    for (int i = 0; i < 2; i++){
        if(pause_menu_option == i){
            optionColor = YELLOW;
        }else{
            optionColor = LIGHTGRAY;
        }
            DrawTextEx(jogo->fontes.fonte_legal, escrito[i], (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, escrito[i], 36, 2).x)/2), 300 + 75*i}, 36, 2, optionColor);
        }
    if(IsKeyPressed(KEY_ENTER)){
        if(pause_menu_items[pause_menu_option] == 10){
            resetarJogo(jogo);
        };
        SetActiveScreen(pause_menu_items[pause_menu_option]);
    }
}


