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

#define NRO_INIMIGOS 2
#define TEMPO_DE_SPAWN_INIMIGOS 1
#define NRO_PROJETEIS 100
#define NRO_CELS_ENERGIA 5
#define TEMPO_DE_SPAWN_CELS_ENERGIA 1

#define NRO_EXPLOSOES 30
#define NUM_FRAMES_PER_LINE     4
#define NUM_LINES               4

#define TAMANHO_TANQUES 35
#define ALTURA_CELS_ENERGIA 35
#define LARGURA_CELS_ENERGIA 35

#define FALSE 0
#define TRUE 1

typedef struct explosao{
    Rectangle explosao_R;
    bool ativa;
    int frames;
    int currentFrame;
    int currentLine;
    Texture2D textura;
}EXPLOSAO;

typedef struct fontes{
    Font fonte_legal;
}FONTES;

typedef struct sons{
    Sound construcao;
    Sound explosao_inimigo;
    Sound hit_jogador;
    Sound power_up;
    Sound tiro;
}SONS;

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
    MAPA mapa;
    int fase;
    int segundos;
    float milisegundos;
    int jogo_carregado;
    TEXTURAS texturas;
    FONTES fontes;
    SONS sons;
    EXPLOSAO explosoes[NRO_EXPLOSOES];
    int contador_explosoes;
}GAME;

void DrawGameplayScreen(GAME *jogo);
void DrawNewGameplayScreen(GAME *jogo);
void DrawSavedGameGameplayScreen(GAME *jogo);
void salvarJogo(GAME *jogo);
void carregarJogoSalvo(GAME *jogo);
void passarDeFase(GAME *jogo);
void reiniciarJogo(GAME *jogo);
void resetarJogo(GAME *jogo);
void carregarMapa(int mapa[][MAPA_COLUNAS], FILE *nivel_fp);
#endif
