#include "raylib.h"
#include "stdio.h"
/*
Screens id
10 -> Main Menu Screen
11 -> Gameplay Screen
12 -> Options Menu Screen
*/
//Main Menu variables
const int menu_items[2]={
    11,
    12
};
int op=0;

void DrawMainMenuScreen(){
    printf("\n%d\n",op);

    ClearBackground(BLUE);
    Color optionColor = LIGHTGRAY;

    if(IsKeyPressed(KEY_DOWN) && op<1){
        printf("baixo");
        op++;
    }

    if(IsKeyPressed(KEY_UP) && op>0){
        printf("CIAM");
        op--;
    }

    if(op == 0){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Novo jogo", 20, 20, 40, optionColor);

    if(op == 1){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Opcoes", 20, 140, 40, optionColor);

    if(IsKeyPressed(KEY_ENTER)){
        SetActiveScreen(menu_items[op]);
    }
}

