#ifndef PROJETIL_H_INCLUDED
#define PROJETIL_H_INCLUDED
typedef struct projetil{
    Rectangle projetil_R;
    VELOCIDADE vel;
    char tanque_de_origem;
    int em_movimento;

}PROJETIL;

void atirarProjetil(PROJETIL *projetil, JOGADOR jogador);
void movimentarProjeteis(PROJETIL *projetil);
void removerProjetil(PROJETIL projeteis[], int indice);
void renderizarProjeteis(PROJETIL *projetil);
bool checarColisaoProjeteis(PROJETIL *projetil, INIMIGO *inimigo);

#endif

