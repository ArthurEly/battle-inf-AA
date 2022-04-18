#include "raylib.h"
#include "stdio.h"
#include "menu.h"

#define TEXTOS 5

void SetActiveScreen(int screen_id);
extern Font fonte_legal;
extern Texture2D texture;
const int menu_items[TEXTOS]={
    11,
    12,
    13,
    14,
    999
};
const int MENU_ITEMS_QTDY = sizeof(menu_items)/sizeof(menu_items[0]);
int menu_option=0;
//Font fonte = GetFontDefault();
const char *escrita[TEXTOS] = { "Novo Jogo",
                                "Continuar",
                                "Carregar Mapa",
                                "Highscores",
                                "Sair"};
int i;
/*void teste(){
    Vector2 posicao[TEXTOS] = { 0 };
    for (i = 0; i < TEXTOS; i++){
        posicao[i].x = 400.0f - MeasureText(escrita[i], 40.0f).x/2.0f;
        posicao[i].y = 400.0f + 50.0f*i;
    }
}
int spacing = 2;*/

void DrawMainMenuScreen(){
    ClearBackground(BLUE);
    Color optionColor = LIGHTGRAY;
   // DrawTexture(texture, 0, 0, GRAY);
    DrawTextureEx(texture, (Vector2){0,0}, 0, 1, WHITE);

    if(IsKeyPressed(KEY_DOWN) &&menu_option<MENU_ITEMS_QTDY-1){
       menu_option++;
    }

    if(IsKeyPressed(KEY_UP) &&menu_option>0){
       menu_option--;
    }

 /*   if(menu_option == 0){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
   // DrawText("Novo jogo", 400, 400, 40, optionColor);

    if(menu_option == 1){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    //DrawText("Continuar", 400, 450, 40, optionColor);

    if(menu_option == 2){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }    DrawTextEx(GetFontDefault(), "Carregar Mapa", (Vector2){400.0f, 500.0f}, 40.0, 5, optionColor);

    if(menu_option == 3){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Highscores", 400, 550, 40, optionColor);

    if(menu_option == 4){
        optionColor = YELLOW;
    }else{
        optionColor = LIGHTGRAY;
    }
    DrawText("Sair", 400, 600, 40, optionColor);*/

    for (int i = 0; i < TEXTOS; i++){
            if(menu_option == i){
            optionColor = YELLOW;
            }else{
            optionColor = LIGHTGRAY;
            }
                DrawTextEx(fonte_legal, escrita[i], (Vector2){(500 - (MeasureTextEx(fonte_legal, escrita[i], 36, 2).x)/2), 400 + 50*i}, 36, 2, optionColor);
                           //(MeasureText(escrita[i], 40)/2), 400 + 50*i}, 40, 2, optionColor);
                //DrawText(escrita[i], 500 - (MeasureText(escrita[i], 40)/2), 400 + 50*i, 40, optionColor);
            }

    if(IsKeyPressed(KEY_ENTER)){
        if(menu_items[menu_option] != 999)
            SetActiveScreen(menu_items[menu_option]);
        else
            CloseWindow();
    }
}


