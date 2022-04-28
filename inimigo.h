#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED
#include "jogador.h"
#include "construcao.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

typedef struct inimigo{
    Rectangle inimigo_R;
    int vidas;
    int angulo;
    VELOCIDADE vel;
    float multiplicador_vel;
    Color cor;
    Vector2 origem_textura;
    int emMovimento;
    bool colidindo;
    bool colidiuComInimigo;
    bool abatidoPeloJogador;
}INIMIGO;

void criarNovoInimigo(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], INIMIGO *inimigo, int altura_tanque, int largura_tanque);
//void movimentarInimigos(JOGADOR *jogador, INIMIGO *inimigo);
void girarSentidoHorario(INIMIGO *inimigo);
void inverterSentidoDeMovimento(INIMIGO *inimigo);
void colidirInimigos(INIMIGO *inimigo_a,INIMIGO *inimigo_b);
void removerInimigo(INIMIGO inimigos[], int indice);
bool checarColisaoInimigoEBloquinho(Rectangle *inimigo_R, Rectangle *bloco_R);
bool checarColisaoEntreInimigos(Rectangle *inimigo_Ra, Rectangle *inimigo_Rb);

#endif
