#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "stdio.h"
#include "raylib.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"
#include "cel_energia.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42
#define ALTURA_BLOCO 40
#define LARGURA_BLOCO 25
#define CABECALHO 90
#define TAMANHO_LAYOUT_LATERAL 150
#define TAMANHO_BORDA_MAPA 10

#define NRO_INIMIGOS 15
#define TEMPO_DE_SPAWN_INIMIGOS 1
#define NRO_PROJETEIS 100
#define NRO_CELS_ENERGIA 5
#define TEMPO_DE_SPAWN_CELS_ENERGIA 1

#define TAMANHO_TANQUES 35
#define ALTURA_CELS_ENERGIA 35
#define LARGURA_CELS_ENERGIA 35

#define FALSE 0
#define TRUE 1

typedef struct fontes{
    Font fonte_legal;
}FONTES;

/*typedef struct texturas{
    Texture2D energia;
    Texture2D tijolo;
    Texture2D escudo;
    Texture2D texture;
    Texture2D pause;
    Texture2D highscore;
    Texture2D carregar;
    Texture2D jogador;
    Texture2D inimigo_patrulha;
    Texture2D inimigo_perseguicao;
}TEXTURAS;*/

typedef struct game{
    JOGADOR jogador;
    INIMIGO inimigos[NRO_INIMIGOS];
    int contador_inimigos;
    PROJETIL projeteis[NRO_PROJETEIS];
    int contador_projeteis;
    CELULA cels_energia[NRO_CELS_ENERGIA];
    int contador_cels_energia;
    int contador_interno_cel_energia;
    BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS];
    int mapa[MAPA_LINHAS][MAPA_COLUNAS];
    int mapa_inicial[MAPA_LINHAS][MAPA_COLUNAS];
    int segundos;
    float milisegundos;
    int fase;
    int mapa_foi_pre_carregado;
    int jogo_carregado;
    int mapa_carregado;
    TEXTURAS texturas;
    FONTES fontes;
}GAME;

void DrawGameplayScreen(GAME *jogo, int cod_game);
void DrawNewGameplayScreen(GAME *jogo);
void DrawSavedGameGameplayScreen(GAME *jogo);
void salvarJogo(GAME *jogo);
void carregarJogoSalvo(GAME *jogo);
void passarDeFase(GAME *jogo);
void reiniciarJogo(GAME *jogo);
void resetarJogo(GAME *jogo);
void carregarMapa(int mapa[][MAPA_COLUNAS], FILE *nivel_fp);
#endif
