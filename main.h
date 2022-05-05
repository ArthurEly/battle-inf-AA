#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include "game.h"

void SetActiveScreen(int screen_id);
void DrawScreen(GAME *jogo, int screen_id);
void timerSegundos(int *segundos, float *milisegundos);

#endif

