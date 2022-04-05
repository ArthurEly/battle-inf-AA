#include "raylib.h"
#include "stdio.h"

void SetActiveScreen(int screen_id);

const int pause_menu_items[2]={
    10,
    11
};
const int PAUSE_MENU_ITEMS_QTDY = sizeof(menu_items)/sizeof(menu_items[0]);
int pause_menu_option=0;

void DrawPauseMenu(){

    ClearBackground(RED);
    Color optionColor = LIGHTGRAY;

    if(IsKeyPressed(KEY_DOWN) &&pause_menu_option<PAUSE_MENU_ITEMS_QTDY-1){
       pause_menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&pause_menu_option>0){
       pause_menu_option--;
    }

    if(pause_menu_option == 0){
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
    DrawText("Volta pro game", 20, 140, 40, optionColor);

    if(IsKeyPressed(KEY_ENTER)){
        SetActiveScreen(pause_menu_items[pause_menu_option]);
    }
}

