#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"
#include "construcao.h"
#include "mapa.h"
#include "math.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42


#define FALSE 0
#define TRUE 1

void criarNovoInimigo(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], INIMIGO *inimigo, int altura_tanque, int largura_tanque){
    inimigo->inimigo_R.height = altura_tanque;
    inimigo->inimigo_R.width = largura_tanque;
    inimigo->vidas = 1;
    inimigo->multiplicador_vel = 1;
    inimigo->cor = WHITE;
    inimigo->emMovimento = 0;

    int coord_y_rand;
    int coord_x_rand;
    int y_rand;
    int x_rand;

    do{
        y_rand = GetRandomValue(1,15);
        x_rand = GetRandomValue(1,40);
    }while(proximoAoJogador(mapa,y_rand,x_rand,10));

    coord_x_rand = converterIndiceXParaCoordenada(x_rand);
    coord_y_rand = converterIndiceYParaCoordenada(y_rand);

    inimigo->inimigo_R.x = coord_x_rand;
    inimigo->inimigo_R.y = coord_y_rand;

    int novo_x = x_rand;
    int novo_y = y_rand;

    bool colidiu_com_o_bloco = checarColisaoInimigoEBloquinho(&inimigo->inimigo_R, &blocos[y_rand][x_rand].bloco_R);
    bool colidiu_com_o_bloco_a_direita = checarColisaoInimigoEBloquinho(&inimigo->inimigo_R, &blocos[y_rand][x_rand+1].bloco_R);
    bool colidiu_com_o_bloco_a_esquerda = checarColisaoInimigoEBloquinho(&inimigo->inimigo_R, &blocos[y_rand][x_rand-1].bloco_R);

    if (colidiu_com_o_bloco || colidiu_com_o_bloco_a_direita || colidiu_com_o_bloco_a_esquerda){
        printf("x : %d\n",novo_x);
        printf("y : %d\n",novo_y);
        reposicionarInimigo(mapa,&novo_y,&novo_x);
    }

    printf("novo x : %d\n",novo_x);
    printf("novo y : %d\n",novo_y);

    inimigo->inimigo_R.x = converterIndiceXParaCoordenada(novo_x);
    inimigo->inimigo_R.y = converterIndiceYParaCoordenada(novo_y);
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
        bool perto_do_x = jogador->jogador_R.x+5 >= inimigo->inimigo_R.x && jogador->jogador_R.x-5 <= inimigo->inimigo_R.x;
        bool perto_do_y = jogador->jogador_R.y+5 >= inimigo->inimigo_R.y && jogador->jogador_R.y-5 <= inimigo->inimigo_R.y;

        if(perto_do_x || perto_do_y){
            inimigo->emMovimento = 2;
        }

    } else if (inimigo->emMovimento == 2){
        //perseguição
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
            //baixo
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

void girarSentidoHorario(INIMIGO *inimigo){
    int velocidade = 1*inimigo->multiplicador_vel;
    switch(inimigo->angulo){
        case 0:
            inimigo->inimigo_R.y = inimigo->inimigo_R.y+1;
            inimigo->vel.vx = velocidade;
            inimigo->vel.vy = 0;
            inimigo->origem_textura.x = 0;
            inimigo->origem_textura.y = inimigo->inimigo_R.height;
            break;

        case 90:
            inimigo->inimigo_R.x = inimigo->inimigo_R.x-1;
            inimigo->vel.vx = 0;
            inimigo->vel.vy = velocidade;
            inimigo->origem_textura.x = inimigo->inimigo_R.width;
            inimigo->origem_textura.y = inimigo->inimigo_R.height;
            break;

        case 180:
            inimigo->inimigo_R.y = inimigo->inimigo_R.y-1;
            inimigo->vel.vx = -velocidade;
            inimigo->vel.vy = 0;
            inimigo->origem_textura.x = inimigo->inimigo_R.width;
            inimigo->origem_textura.y = 0;
            break;

        case 270:
            inimigo->inimigo_R.x = inimigo->inimigo_R.x+1;
            inimigo->vel.vx = 0;
            inimigo->vel.vy = -velocidade;
            inimigo->origem_textura.x = 0;
            inimigo->origem_textura.y = 0;
            break;
    }

    if (inimigo->angulo < 270)
        inimigo->angulo += 90;
    else
        inimigo->angulo = 0;
}

void removerInimigo(INIMIGO inimigos[], int indice){
    inimigos[indice].vidas = 0;
    inimigos[indice].vel.vx = 0;
    inimigos[indice].vel.vy = 0;
    inimigos[indice].inimigo_R.x = 900;
    inimigos[indice].inimigo_R.y = 1000;
}

bool checarColisaoInimigoEBloquinho(Rectangle *inimigo_R, Rectangle *bloco_R){
    bool colidiu = CheckCollisionRecs(*inimigo_R,*bloco_R);
    return colidiu;
}



