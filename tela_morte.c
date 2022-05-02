#include "raylib.h"
#include "stdio.h"
#include "pause_menu.h"
#include "game.h"
#include "highscores.h"

#define TEXTOS 3

void SetActiveScreen(int screen_id);

int death_menu_option=0;
void DrawDeathScreen(GAME *jogo){
    const int pause_menu_items[2]={11,10};
    const int PAUSE_MENU_ITEMS_QTDY = sizeof(pause_menu_items)/sizeof(pause_menu_items[0]);

    const char *escrito[3] = {"Novo jogo",
                              "Voltar ao menu",
                              " "};

    ClearBackground(RED);
    DrawTextureEx(jogo->texturas.morte, (Vector2){-75,0}, 0, 1, WHITE);
    Color optionColor = LIGHTGRAY;
    int tamanho_fonte = 36;

    if(IsKeyPressed(KEY_DOWN) && death_menu_option<PAUSE_MENU_ITEMS_QTDY-1 + 1){
       death_menu_option++;
    }

    if(IsKeyPressed(KEY_UP) && death_menu_option > 0){
       death_menu_option--;
    }
    int i;
    for (i = 0; i < 2; i++){
        if(death_menu_option == i){
            optionColor = YELLOW;
            tamanho_fonte = 38;
        }else{
            optionColor = LIGHTGRAY;
            tamanho_fonte = 36;
        }
        DrawTextEx(jogo->fontes.fonte_legal, escrito[i], (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, escrito[i], tamanho_fonte, 2).x)/2), 300 + 75*i}, tamanho_fonte, 2, optionColor);
    }

    if (death_menu_option == 2){
        DrawRectangle(212,438,725,225,YELLOW);
    }

    if(IsKeyPressed(KEY_ENTER)){
        if(pause_menu_items[death_menu_option] == 10){
            resetarJogo(jogo);
        };

        if(pause_menu_items[death_menu_option] == 11){
            reiniciarJogo(jogo);
        };

        SetActiveScreen(pause_menu_items[death_menu_option]);
    }


    HIGHSCORE ultimo_highscore;
    HIGHSCORE novo_highscore;

    lerUltimoColocado(&ultimo_highscore);

    strcpy(novo_highscore.nome,jogo->jogador.nome);
    novo_highscore.pontuacao = jogo->jogador.pontuacao;
    novo_highscore.segundos = jogo->segundos;

    //serve pra teste, nao apaga ainda
    /*printf("nome jogador -> %s\n",novo_highscore.nome);
    printf("pontuacao jogador -> %d\n",novo_highscore.pontuacao);
    printf("ultimo_highscore.pontuacao -> %d\n",ultimo_highscore.pontuacao);

    if(novo_highscore.pontuacao > ultimo_highscore.pontuacao){

    }else if (jogo->jogador.pontuacao == ultimo_highscore.pontuacao){
        if(jogo->segundos < ultimo_highscore.segundos){


        }else if (jogo->segundos > ultimo_highscore.pontuacao){
            printf("bah, n melhora esse tempo ai\n");
        }else{
            printf("deu empate. quem chego primeiro tem preferencia kkkkkkkkk\n");
        }
    }else{
        printf("horrivel\n");
    }*/

    if(novo_highscore.pontuacao >= ultimo_highscore.pontuacao){
        DrawRectangle(225,450,700,200,WHITE);
        DrawText(TextFormat("dai abre essa coisa aqui se o highscore for maior q algum q tem la"), -10, 500, 36, RED);
        if(IsKeyDown(KEY_H)){
            atualizarHighscore(&novo_highscore);
            printf("parabens!!!!!\n");
            resetarJogo(jogo);
            SetActiveScreen(14);
        }
    }
}



