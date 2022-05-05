#include "raylib.h"
#include "stdio.h"
#include "pause_menu.h"
#include "game.h"
#include "highscores.h"
#include "string.h"

#define TEXTOS 3

void SetActiveScreen(int screen_id);

int death_menu_option=0;
int letterCount = 0;
void DrawDeathScreen(GAME *jogo){
    const int pause_menu_items[2]={11,10};
    const int PAUSE_MENU_ITEMS_QTDY = sizeof(pause_menu_items)/sizeof(pause_menu_items[0]);

    const char *escrito[2] = {"Novo jogo",
                              "Voltar ao menu"};

    ClearBackground(RED);
    DrawTextureEx(jogo->texturas.morte, (Vector2){-50,0}, 0, 1, WHITE);
    Color optionColor = LIGHTGRAY;
    int tamanho_fonte = 36;

    int i;
    for (i = 0; i < 2; i++){
        if(death_menu_option == i){
            optionColor = ORANGE;
            tamanho_fonte = 38;
        }else{
            optionColor = LIGHTGRAY;
            tamanho_fonte = 36;
        }
        DrawTextEx(jogo->fontes.fonte_legal, escrito[i], (Vector2){(565 - (MeasureTextEx(jogo->fontes.fonte_legal, escrito[i], tamanho_fonte, 2).x)/2), 300 + 75*i}, tamanho_fonte, 2, optionColor);
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

    int nova_opcao = 0;
    if(novo_highscore.pontuacao >= ultimo_highscore.pontuacao  && (novo_highscore.segundos <= ultimo_highscore.segundos || ultimo_highscore.segundos == 0) && novo_highscore.pontuacao !=0 && !jogo->mapa.mapa_foi_pre_carregado){
        nova_opcao = 1;
        if (death_menu_option == 2){
                DrawRectangle(212,438,725,175,ORANGE);
                int key = GetCharPressed();

                while (key > 0)
                {
                    // só pega letras do alfabeto
                    if ((key >= 32) && (key <= 125) && (letterCount < TAMANHO_NOME))
                    {
                        jogo->jogador.nome[letterCount] = (char)key;
                        jogo->jogador.nome[letterCount+1] = '\0'; //adiciona o \0 pra indicar que é string.
                        letterCount++;
                    }

                    key = GetCharPressed();  // ve qual é a proxima letra pra por
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    jogo->jogador.nome[letterCount] = '\0';
                }
        }
        Rectangle input_nome = {225,450,700,150};
        DrawRectangleRec(input_nome,WHITE);
        DrawText(jogo->jogador.nome, (int)input_nome.x + 15, (int)input_nome.y + 30, 70, BLACK);
        if(IsKeyDown(KEY_ENTER) && death_menu_option == 2){
            death_menu_option = 0;
            nova_opcao = 0;
            strcpy(novo_highscore.nome,jogo->jogador.nome);
            atualizarHighscore(&novo_highscore);
            resetarJogo(jogo);
            SetActiveScreen(14);
            letterCount = 0;
        }
    }

    if(IsKeyPressed(KEY_DOWN) && death_menu_option < PAUSE_MENU_ITEMS_QTDY-1 + nova_opcao){
       death_menu_option++;
    }

    if(IsKeyPressed(KEY_UP) && death_menu_option > 0){
       death_menu_option--;
    }
}



