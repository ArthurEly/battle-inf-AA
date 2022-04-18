#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED
#include "jogador.h"
typedef struct inimigo{
    Rectangle inimigo_R;
    int vidas;
    float angulo;
    VELOCIDADE vel;
    int multiplicador_vel;
    Color cor;
    Vector2 origem_textura;
    int emMovimento;
}INIMIGO;

void criarNovoInimigo(INIMIGO *inimigo, int altura_tanque, int largura_tanque);
void movimentarInimigos(JOGADOR *jogador, INIMIGO *inimigo);
void removerInimigo(INIMIGO inimigos[], int indice);

#endif
