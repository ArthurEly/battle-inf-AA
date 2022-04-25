#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED
#include "construcao.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

void transcreverMapa(int *id, int y, int x, int y_max, int x_max, BLOCO blocos[][MAPA_COLUNAS]);
void atualizarMapa(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], JOGADOR jogador, INIMIGO inimigos[], int contador_inimigos);
void posicionarJogador(int id, JOGADOR *jogador, int y, int x);
void reposicionarObjeto(int mapa[][MAPA_COLUNAS], int *novo_y, int *novo_x);
int temEmTodoORedor(int mapa[][MAPA_COLUNAS],int y, int x, int tipo, int raio_procura);
int temUmAORedor(int mapa[][MAPA_COLUNAS],int y, int x, int tipo, int raio_procura);
int buscarLugarVazio(BLOCO blocos[][MAPA_COLUNAS],int y, int x);
int calcularDistanciaEntrePontos(int x_inimigo, int y_inimigo, int x_jogador, int y_jogador);
int proximoAoJogador(int mapa[][MAPA_COLUNAS],int y, int x, int distancia_minima);
int converterCoordenadaXParaIndice(int coord_x);
int converterCoordenadaYParaIndice(int coord_y);
int converterIndiceXParaCoordenada(int indice_x);
int converterIndiceYParaCoordenada(int indice_y);
void printarMapa(int mapa[][MAPA_COLUNAS]);
#endif

