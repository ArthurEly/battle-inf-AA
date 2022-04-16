#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
typedef struct jogador{
    int x;
    int y;
    int vidas;
    int pontuacao;
    float angulo;
    VELOCIDADE vel;
    int altura;
    int largura;
    Color cor;
    Vector2 origem_textura;

}JOGADOR;

void movimentacaoJogador(JOGADOR *jogador, Rectangle *jogador_R);

#endif

