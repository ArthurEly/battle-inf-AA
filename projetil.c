#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"

void atirarProjetil(PROJETIL *projetil, JOGADOR jogador){
    projetil->em_movimento = 1;
    projetil->projetil_R.height = 10;
    projetil->projetil_R.width = 10;
    int velocidade = 10;

    switch(jogador.angulo){
        case 0:
            projetil->projetil_R.x = jogador.jogador_R.x+45;
            projetil->projetil_R.y = jogador.jogador_R.y;
            projetil->vel.vx = 0;
            projetil->vel.vy = -velocidade;
            break;

        case 90:
            projetil->projetil_R.x = jogador.jogador_R.x+95;
            projetil->projetil_R.y = jogador.jogador_R.y+45;
            projetil->vel.vx = velocidade;
            projetil->vel.vy = 0;
            break;


        case 180:
            projetil->projetil_R.x = jogador.jogador_R.x+45;
            projetil->projetil_R.y = jogador.jogador_R.y+95;
            projetil->vel.vx = 0;
            projetil->vel.vy = velocidade;
            break;


        case 270:
            projetil->projetil_R.x = jogador.jogador_R.x;
            projetil->projetil_R.y = jogador.jogador_R.y+45;
            projetil->vel.vx = -velocidade;
            projetil->vel.vy = 0;
            break;
    }
}

void movimentarProjeteis(PROJETIL *projetil){
    projetil->projetil_R.x += projetil->vel.vx;
    projetil->projetil_R.y += projetil->vel.vy;
}

void removerProjetil(PROJETIL projeteis[], int indice){
    projeteis[indice].em_movimento = 0;
    projeteis[indice].vel.vx = 0;
    projeteis[indice].vel.vy = 0;
    projeteis[indice].projetil_R.x = 9000;
    projeteis[indice].projetil_R.y = 9000;
}

void renderizarProjeteis(PROJETIL *projetil){
    DrawRectangle(
      projetil->projetil_R.x,
      projetil->projetil_R.y,
      projetil->projetil_R.height,
      projetil->projetil_R.width,
      GREEN
    );
}

bool checarColisaoProjeteis(PROJETIL *projetil, INIMIGO *inimigo){
    bool colidiu = CheckCollisionRecs(projetil->projetil_R, inimigo->inimigo_R);
    return colidiu;
}

