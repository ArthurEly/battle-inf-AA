#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"

void criarNovoInimigo(INIMIGO *inimigo, Rectangle *inimigo_R){
    int x = GetRandomValue(50,950);
    int y = GetRandomValue(50,750);

    inimigo->x = x;
    inimigo->y = y;
    inimigo->vidas = 1;
    inimigo->vel.vx = 0;
    inimigo->vel.vy = 0;
    inimigo->altura = 50;
    inimigo->largura = 50;
    inimigo->cor = WHITE;
    inimigo->origem_textura.x=50;
    inimigo->origem_textura.y=50;
    inimigo->emMovimento = 0;

    inimigo_R->x = x;
    inimigo_R->y = y;
}

void movimentarInimigos(JOGADOR *jogador, INIMIGO *inimigo, Rectangle *inimigo_R){
    int movimentacoes[4][3]={
    //    vx , vy ,angulo
        {  1 ,  0 ,90},
        {(-1),  0 ,270},
        {  0 ,  1 ,180},
        {  0 ,(-1),0}
    };

    int movimentacaoAleatoria = GetRandomValue(0,3);

    if (inimigo->emMovimento == 0){
        //inicia o movimento
        inimigo->vel.vx = movimentacoes[movimentacaoAleatoria][0];
        inimigo->vel.vy = movimentacoes[movimentacaoAleatoria][1];
        inimigo->angulo = movimentacoes[movimentacaoAleatoria][2];
        inimigo->emMovimento = 1;
    } else if (inimigo->emMovimento == 1){
        //patrulha
        if(inimigo->x == jogador->x){
            inimigo->vel.vx = 0;
            if(inimigo->y > jogador->y){
                inimigo->vel.vy = (-1);
                inimigo->angulo = 0;
            }else{
                inimigo->vel.vy = 1;
                inimigo->angulo = 180;
            }
            inimigo->emMovimento = 2;
        }

        if(inimigo->y == jogador->y){
            inimigo->vel.vy = 0;
            if(inimigo->x > jogador->x){
                inimigo->vel.vx = (-1);
                inimigo->angulo = 270;
            }else{
                inimigo->vel.vx = 1;
                inimigo->angulo = 90;
            }
            inimigo->emMovimento = 2;
        }

    } else if (inimigo->emMovimento == 2){
        //perseguição
        if(inimigo->x < jogador->x){
            inimigo->vel.vy = 0;
            inimigo->vel.vx = 1;
            inimigo->angulo = 90;
        }

        if(inimigo->x > jogador->x){
            inimigo->vel.vy = 0;
            inimigo->vel.vx = (-1);
            inimigo->angulo = 270;
        }

        if(inimigo->y < jogador->y){
            inimigo->vel.vx = 0;
            inimigo->vel.vy = 1;
            inimigo->angulo = 180;
        }

        if(inimigo->y > jogador->y){
            inimigo->vel.vx = 0;
            inimigo->vel.vy = (-1);
            inimigo->angulo = 0;
        }
    }

    inimigo->x += inimigo->vel.vx;
    inimigo->y += inimigo->vel.vy;

    inimigo_R->x = inimigo->x;
    inimigo_R->y = inimigo->y;
}

void removerInimigo(INIMIGO inimigos[], int indice){
    inimigos[indice].vidas = 0;
    inimigos[indice].vel.vx = 0;
    inimigos[indice].vel.vy = 0;
    inimigos[indice].x = 900;
    inimigos[indice].y = 1000;
}
