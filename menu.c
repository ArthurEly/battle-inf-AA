#include "raylib.h"
#include "stdio.h"
#include "menu.h"
void SetActiveScreen(int screen_id);
const int menu_items[4]={
    11,
    12,
    13,
    999
};
const int MENU_ITEMS_QTDY = sizeof(menu_items)/sizeof(menu_items[0]);
int menu_option=0;

void DrawMainMenuScreen(){
    ClearBackground(BLUE);
    Color optionColor = LIGHTGRAY;

    if(IsKeyPressed(KEY_DOWN) &&menu_option<MENU_ITEMS_QTDY-1){
       menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&menu_option>0){
       menu_option--;
    }

    if(menu_option == 0){
        optionColor = GREEN;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Novo jogo", 20, 20, 40, optionColor);

    if(menu_option == 1){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Opcoes", 20, 140, 40, optionColor);

    if(menu_option == 2){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Highscores", 20, 230, 40, optionColor);

    if(menu_option == 3){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Sair", 20, 260, 40, optionColor);

    if(IsKeyPressed(KEY_ENTER)){
        if(menu_items[menu_option] != 999)
            SetActiveScreen(menu_items[menu_option]);
        else
            CloseWindow();
    }
}


