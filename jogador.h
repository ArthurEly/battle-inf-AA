#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED
typedef struct jogador{
    Rectangle jogador_R;
    Rectangle ponto_de_colisao;
    int vidas;
    int pontuacao;
    int angulo;
    VELOCIDADE vel;
    int multiplicador_vel;
    Color cor;
    Vector2 origem_textura;

}JOGADOR;

void movimentacaoJogador(JOGADOR *jogador);
void pararJogador(JOGADOR *jogador);
void retomarJogador(JOGADOR *jogador);
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R);
bool checarColisaoJogadorEBloquinho(Rectangle *ponto_de_colisao, Rectangle *bloco_R);

#endif

