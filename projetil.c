#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"

void atirarProjetilJogador(PROJETIL *projetil, JOGADOR jogador){
    projetil->em_movimento = 1;
    projetil->tanque_de_origem = 'j';

    int velocidade = 10*jogador.multiplicador_vel;
    int variacao = jogador.jogador_R.height*0.15;
    projetil->angulo = jogador.angulo;

    switch(projetil->angulo){
        case 0:
            projetil->projetil_R.height = jogador.jogador_R.height*0.6;
            projetil->projetil_R.width = jogador.jogador_R.width*0.3;
            projetil->projetil_R.x = jogador.jogador_R.x+((float)(jogador.jogador_R.width/2)-variacao);
            projetil->projetil_R.y = jogador.jogador_R.y;
            projetil->vel.vx = 0;
            projetil->vel.vy = -velocidade;
            projetil->origem_textura.x  = 0;
            projetil->origem_textura.y  = 0;
            break;

        case 90:
            projetil->projetil_R.height = jogador.jogador_R.height*0.3;
            projetil->projetil_R.width = jogador.jogador_R.width*0.6;
            projetil->projetil_R.x = jogador.jogador_R.x+((float)(jogador.jogador_R.width)-variacao);
            projetil->projetil_R.y = jogador.jogador_R.y+((float)(jogador.jogador_R.height/2)-variacao);
            projetil->vel.vx = velocidade;
            projetil->vel.vy = 0;
            projetil->origem_textura.x  = 0;
            projetil->origem_textura.y  = projetil->projetil_R.height;
            break;


        case 180:
            projetil->projetil_R.height = jogador.jogador_R.height*0.6;
            projetil->projetil_R.width = jogador.jogador_R.width*0.3;
            projetil->projetil_R.x = jogador.jogador_R.x+((float)(jogador.jogador_R.width/2)-variacao);
            projetil->projetil_R.y = jogador.jogador_R.y+((float)(jogador.jogador_R.height)-variacao);
            projetil->vel.vx = 0;
            projetil->vel.vy = velocidade;
            projetil->origem_textura.x  = projetil->projetil_R.width;
            projetil->origem_textura.y  = projetil->projetil_R.height;
            break;


        case 270:
            projetil->projetil_R.height = jogador.jogador_R.height*0.3;
            projetil->projetil_R.width = jogador.jogador_R.width*0.6;
            projetil->projetil_R.x = jogador.jogador_R.x;
            projetil->projetil_R.y = jogador.jogador_R.y+((float)(jogador.jogador_R.height/2)-variacao);
            projetil->vel.vx = -velocidade;
            projetil->vel.vy = 0;
            projetil->origem_textura.x  = projetil->projetil_R.width;
            projetil->origem_textura.y  = 0;
            break;
    }

    projetil->projetil_textura_R.x = 0;
    projetil->projetil_textura_R.y = 0;
    projetil->projetil_textura_R.height = 80;
    projetil->projetil_textura_R.width  = 80;
}

void atirarProjetilInimigo(PROJETIL *projetil, INIMIGO inimigo){
    projetil->em_movimento = 1;
    projetil->tanque_de_origem = 'i';

    int velocidade = 10;
    int variacao = inimigo.inimigo_R.height*0.15;

    projetil->angulo = inimigo.angulo;

    switch(projetil->angulo){
        case 0:
            projetil->projetil_R.height = inimigo.inimigo_R.height*0.6;
            projetil->projetil_R.width = inimigo.inimigo_R.width*0.3;
            projetil->projetil_R.x = inimigo.inimigo_R.x+((float)(inimigo.inimigo_R.width/2)-variacao);
            projetil->projetil_R.y = inimigo.inimigo_R.y;
            projetil->vel.vx = 0;
            projetil->vel.vy = -velocidade;
            projetil->origem_textura.x  = 0;
            projetil->origem_textura.y  = 0;
            break;

        case 90:
            projetil->projetil_R.height = inimigo.inimigo_R.height*0.3;
            projetil->projetil_R.width = inimigo.inimigo_R.width*0.6;
            projetil->projetil_R.x = inimigo.inimigo_R.x+((float)(inimigo.inimigo_R.width)-variacao);
            projetil->projetil_R.y = inimigo.inimigo_R.y+((float)(inimigo.inimigo_R.height/2)-variacao);
            projetil->vel.vx = velocidade;
            projetil->vel.vy = 0;
            projetil->origem_textura.x  = 0;
            projetil->origem_textura.y  = projetil->projetil_R.height;
            break;


        case 180:
            projetil->projetil_R.height = inimigo.inimigo_R.height*0.6;
            projetil->projetil_R.width = inimigo.inimigo_R.width*0.3;
            projetil->projetil_R.x = inimigo.inimigo_R.x+((float)(inimigo.inimigo_R.width/2)-variacao);
            projetil->projetil_R.y = inimigo.inimigo_R.y+((float)(inimigo.inimigo_R.height)-variacao);
            projetil->vel.vx = 0;
            projetil->vel.vy = velocidade;
            projetil->origem_textura.x  = projetil->projetil_R.width;
            projetil->origem_textura.y  = projetil->projetil_R.height;
            break;


        case 270:
            projetil->projetil_R.height = inimigo.inimigo_R.height*0.3;
            projetil->projetil_R.width = inimigo.inimigo_R.width*0.6;
            projetil->projetil_R.x = inimigo.inimigo_R.x;
            projetil->projetil_R.y = inimigo.inimigo_R.y+((float)(inimigo.inimigo_R.height/2)-variacao);
            projetil->vel.vx = -velocidade;
            projetil->vel.vy = 0;
            projetil->origem_textura.x  = projetil->projetil_R.width;
            projetil->origem_textura.y  = 0;
            break;
    }

    projetil->projetil_textura_R.x = 0;
    projetil->projetil_textura_R.y = 0;
    projetil->projetil_textura_R.height = 80;
    projetil->projetil_textura_R.width  = 80;
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

void renderizarProjeteis(PROJETIL *projetil, Texture textura){
    Rectangle projetil_ajustado_R = {projetil->projetil_R.x,projetil->projetil_R.y,20,20};
    Vector2 origem_textura;

    switch(projetil->angulo){
        case 0:
            projetil_ajustado_R.x-=5;
            origem_textura.x  = 0;
            origem_textura.y  = 0;
            break;

        case 90:
            projetil_ajustado_R.y-=5;
            origem_textura.x  = 0;
            origem_textura.y  = 20;
            break;


        case 180:
            projetil_ajustado_R.x-=5;
            origem_textura.x  = 20;
            origem_textura.y  = 20;
            break;


        case 270:
            projetil_ajustado_R.y-=5;
            origem_textura.x  = 20;
            origem_textura.y  = 0;
            break;
    }

    DrawTexturePro(
        textura,
        projetil->projetil_textura_R,
        projetil_ajustado_R,
        origem_textura,
        projetil->angulo,
        WHITE
    );
}

bool checarColisaoProjeteisEInimigo(PROJETIL *projetil, INIMIGO *inimigo){
    bool colidiu = CheckCollisionRecs(projetil->projetil_R, inimigo->inimigo_R);
    return colidiu;
}

bool checarColisaoProjeteisEJogador(PROJETIL *projetil, JOGADOR *jogador){
    bool colidiu = CheckCollisionRecs(projetil->projetil_R, jogador->jogador_R);
    return colidiu;
}

bool checarColisaoProjeteisEBlocos(PROJETIL *projetil, BLOCO *id){
    bool colidiu = CheckCollisionRecs(projetil->projetil_R, id->bloco_R);
    return colidiu;
}

bool checarColisaoDeProjeteis(PROJETIL *projetil_a, PROJETIL *projetil_b){
    bool colidiu = CheckCollisionRecs(projetil_a->projetil_R, projetil_b->projetil_R);
    return colidiu;
}



