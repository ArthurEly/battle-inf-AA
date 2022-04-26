#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
#include "game.h"

typedef struct jogador{
    Rectangle jogador_R;
    int vidas;
    int pontuacao;
    int angulo;
    VELOCIDADE vel;
    int multiplicador_vel;
    Color cor;
    Vector2 origem_textura;
    bool colidindo;
    bool energizado;

}JOGADOR;

void movimentacaoJogador(JOGADOR *jogador);
void pararJogador(JOGADOR *jogador);
void retomarJogador(JOGADOR *jogador);
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R);
bool checarColisaoJogadorEBloquinho(Rectangle *jogador_R, Rectangle *bloco_R);
bool checarColisaoJogadorECelEnergia(Rectangle *jogador_R, Rectangle *cel_energia_R);
#endif

