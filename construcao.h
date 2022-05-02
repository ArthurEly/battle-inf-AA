#ifndef CONSTRUCAO_H_INCLUDED
#define CONSTRUCAO_H_INCLUDED
#include "raylib.h"
#include "game.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

typedef struct texturas{
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
    Texture2D explosa;
    Texture2D morte;
    Texture2D bala;
}TEXTURAS;

typedef struct id{
    Rectangle bloco_R;
    int indice_y;
    int indice_x;
    Color cor;
    bool destrutivel;
    bool destruido;
    int tipo;
    bool mudou_de_cor;
}BLOCO;

void renderizarBloquinho(TEXTURAS *texturas, BLOCO bloco);
void mudarCorBorda(BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS], Color nova_cor);
void removerBloquinho(BLOCO *id);
#endif
