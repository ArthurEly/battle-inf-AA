#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED
#include "construcao.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

void transcreverMapa(int *id, int y, int x, int y_max, int x_max, BLOCO blocos[][MAPA_COLUNAS]);
//void atualizarMapa(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], JOGADOR jogador);
void posicionarJogador(int id, JOGADOR *jogador, int y, int x);
//void reposicionarInimigo(BLOCO blocos[][MAPA_COLUNAS],int y, int x, int *novo_y, int *novo_x);
//void reposicionarCelEnergia(BLOCO blocos[][MAPA_COLUNAS],int y, int x, int *novo_y, int *novo_x);
//int buscarVizinhos(BLOCO blocos[][42],int y, int x);
int buscarLugarVazio(BLOCO blocos[][42],int y, int x);
int converterCoordenadaXParaIndice(int coord_x);
int converterCoordenadaYParaIndice(int coord_y);
int converterIndiceXParaCoordenada(int indice_x);
int converterIndiceYParaCoordenada(int indice_y);
#endif

