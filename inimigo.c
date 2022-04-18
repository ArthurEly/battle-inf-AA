#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"

void criarNovoInimigo(INIMIGO *inimigo, int altura_tanque, int largura_tanque){
    int x = GetRandomValue(10,970);
    int y = GetRandomValue(100,660);

    inimigo->inimigo_R.x = x;
    inimigo->inimigo_R.y = y;
    inimigo->inimigo_R.height = altura_tanque;
    inimigo->inimigo_R.width = largura_tanque;
    inimigo->vidas = 1;
    inimigo->multiplicador_vel = 1;
    inimigo->cor = WHITE;
    inimigo->emMovimento = 2;
}

void movimentarInimigos(JOGADOR *jogador, INIMIGO *inimigo){
    int velocidade = 1*inimigo->multiplicador_vel;
    int movimentacoes[4][5]={
        {  velocidade ,      0      ,  90 ,            0             , inimigo->inimigo_R.height },
        {(-velocidade),      0      , 270 , inimigo->inimigo_R.width ,            0              },
        {      0      ,  velocidade , 180 , inimigo->inimigo_R.width , inimigo->inimigo_R.height },
        {      0      ,(-velocidade),  0  ,            0             ,            0              }
    };

    int movimentacaoAleatoria = GetRandomValue(0,3);
    if (inimigo->emMovimento == 0){
        //inicia o movimento
        inimigo->vel.vx = movimentacoes[movimentacaoAleatoria][0];
        inimigo->vel.vy = movimentacoes[movimentacaoAleatoria][1];
        inimigo->angulo = movimentacoes[movimentacaoAleatoria][2];
        inimigo->origem_textura.x = movimentacoes[movimentacaoAleatoria][3];
        inimigo->origem_textura.y = movimentacoes[movimentacaoAleatoria][4];
        inimigo->emMovimento = 1;

    } else if (inimigo->emMovimento == 1){
        //patrulha
        if(inimigo->inimigo_R.x == jogador->jogador_R.x || inimigo->inimigo_R.y == jogador->jogador_R.y){
            inimigo->emMovimento = 2;
        }

    } else if (inimigo->emMovimento == 2){
        //perseguição
        inimigo->multiplicador_vel = 1;
        if(inimigo->inimigo_R.x < jogador->jogador_R.x){
            //direita
            inimigo->vel.vy = 0;
            inimigo->vel.vx = velocidade;
            inimigo->angulo = 90;
            inimigo->origem_textura.x = 0;
            inimigo->origem_textura.y = inimigo->inimigo_R.height;
        }

        else if(inimigo->inimigo_R.x > jogador->jogador_R.x){
            //esquerda
            inimigo->vel.vy = 0;
            inimigo->vel.vx = (-velocidade);
            inimigo->angulo = 270;
            inimigo->origem_textura.x = inimigo->inimigo_R.width;
            inimigo->origem_textura.y = 0;
        }

        else if(inimigo->inimigo_R.y < jogador->jogador_R.y){
            inimigo->vel.vx = 0;
            inimigo->vel.vy = velocidade;
            inimigo->angulo = 180;
            inimigo->origem_textura.x = inimigo->inimigo_R.width;
            inimigo->origem_textura.y = inimigo->inimigo_R.height;
        }

        else if(inimigo->inimigo_R.x == jogador->jogador_R.x){
            inimigo->vel.vx = 0;
            if(inimigo->inimigo_R.y > jogador->jogador_R.y){
                inimigo->vel.vy = (-velocidade);
                inimigo->angulo = 0;
                inimigo->origem_textura.x = 0;
                inimigo->origem_textura.y = 0;
            }else{
                printf("oiooio\n");
                inimigo->vel.vy = velocidade;
                inimigo->angulo = 180;
                inimigo->origem_textura.x = inimigo->inimigo_R.width;
                inimigo->origem_textura.y = inimigo->inimigo_R.height;
            }
        }

        else if(inimigo->inimigo_R.y == jogador->jogador_R.y){
            inimigo->vel.vy = 0;
            if(inimigo->inimigo_R.x > jogador->jogador_R.x){
                inimigo->vel.vx = (-velocidade);
                inimigo->angulo = 270;
                inimigo->origem_textura.x = inimigo->inimigo_R.width;
                inimigo->origem_textura.y = 0;
            }else{
                inimigo->vel.vx = velocidade;
                inimigo->angulo = 90;
                inimigo->origem_textura.x = 0;
                inimigo->origem_textura.y = inimigo->inimigo_R.height;
            }
        }
    }

    inimigo->inimigo_R.x += inimigo->vel.vx;
    inimigo->inimigo_R.y += inimigo->vel.vy;
}

void removerInimigo(INIMIGO inimigos[], int indice){
    inimigos[indice].vidas = 0;
    inimigos[indice].vel.vx = 0;
    inimigos[indice].vel.vy = 0;
    inimigos[indice].inimigo_R.x = 900;
    inimigos[indice].inimigo_R.y = 1000;
}
