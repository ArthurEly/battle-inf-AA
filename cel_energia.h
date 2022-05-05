#ifndef CEL_ENERGIA_H_INCLUDED
#define CEL_ENERGIA_H_INCLUDED
#include "jogador.h"
#include "construcao.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

typedef struct celula{
    Rectangle cel_energia_R;
    int multiplicador_cel_energia;
    Color cor;
    Vector2 origem_textura;
    bool cel_energia_posicionada;
}CELULA;

void criarCelulaDeEnergia(int mapa[][MAPA_COLUNAS] ,BLOCO blocos[][MAPA_COLUNAS], CELULA *cel_energia);
void energizarJogador(JOGADOR *jogador, CELULA *cel_energia);
void removerCelEnergia(CELULA *cel_energia);
#endif
