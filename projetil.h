#ifndef PROJETIL_H_INCLUDED
#define PROJETIL_H_INCLUDED

typedef struct projetil{
    Rectangle projetil_R;
    VELOCIDADE vel;
    char tanque_de_origem;
    int em_movimento;
    Texture2D textura;
    Vector2 origem_textura;
    Rectangle projetil_textura_R;
    int angulo;
}PROJETIL;

void atirarProjetilJogador(PROJETIL *projetil, JOGADOR jogador);
void atirarProjetilInimigo(PROJETIL *projetil, INIMIGO inimigo);
void movimentarProjeteis(PROJETIL *projetil);
void removerProjetil(PROJETIL projeteis[], int indice);
void renderizarProjeteis(PROJETIL *projetil, Texture textura);
bool checarColisaoProjeteisEInimigo(PROJETIL *projetil, INIMIGO *inimigo);
bool checarColisaoProjeteisEJogador(PROJETIL *projetil, JOGADOR *jogador);
bool checarColisaoProjeteisEBlocos(PROJETIL *projetil, BLOCO *id);
bool checarColisaoDeProjeteis(PROJETIL *projetil_a, PROJETIL *projetil_b);
#endif

