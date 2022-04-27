#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "stdio.h"
#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

typedef struct velocidade{
    int vx;
    int vy;

}VELOCIDADE;

void DrawGameplayScreen(int cod_game);
void carregarMapa(int mapa[][MAPA_COLUNAS], FILE *nivel_fp);
void carregarMapaDeArquivo(FILE *nivel_fp);
#endif
