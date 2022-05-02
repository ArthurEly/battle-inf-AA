#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED
#include "game.h"

typedef struct highscore{
    char nome[15];
    int pontuacao;
    int segundos;
}HIGHSCORE;

void DrawHighScoresScreen(GAME *jogo);

#endif

