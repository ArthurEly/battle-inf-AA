#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
typedef struct jogador{
    Rectangle jogador_R;
    int vidas;
    int pontuacao;
    int angulo;
    VELOCIDADE vel;
    Color cor;
    Vector2 origem_textura;

}JOGADOR;

void movimentacaoJogador(JOGADOR *jogador);
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R);

#endif

