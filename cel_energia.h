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
    bool ativa;

}CELULA;

//void criarCelulaDeEnergia(BLOCO blocos[][MAPA_COLUNAS], CELULA *cel_energia, int altura_cel_energia, int largura_cel_energia);
void energizarJogador(JOGADOR *jogador, CELULA *cel_energia);
void removerCelEnergia(CELULA *cel_energia);
bool checarColisaoCelEnergiaEBloquinho(Rectangle *cel_energia_R, Rectangle *bloco_R);
#endif
