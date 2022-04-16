#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED
typedef struct inimigo{
    int x;
    int y;
    int vidas;
    float angulo;
    VELOCIDADE vel;
    int altura;
    int largura;
    Color cor;
    Vector2 origem_textura;
    int emMovimento;
}INIMIGO;

void criarNovoInimigo(INIMIGO *inimigo, Rectangle *jogador_R);
void movimentarInimigos(JOGADOR *jogador, INIMIGO *inimigo, Rectangle *inimigo_R);
void removerInimigo(INIMIGO inimigos[], int indice);

#endif
