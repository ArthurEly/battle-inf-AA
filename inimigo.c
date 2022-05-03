#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"
#include "construcao.h"
#include "mapa.h"
#include "math.h"
#include "string.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define FALSE 0
#define TRUE 1
int qtde_inimigos = 0;
void criarNovoInimigo(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], INIMIGO *inimigo, int altura_tanque, int largura_tanque){
    inimigo->inimigo_R.height = altura_tanque;
    inimigo->inimigo_R.width = largura_tanque;
    inimigo->vidas = 1;
    inimigo->multiplicador_vel = 1;
    inimigo->cor = WHITE;
    inimigo->emMovimento = 0;
    inimigo->colidiuComInimigo = false;
    inimigo->inimigo_posicionado = TRUE;

    int coord_y_rand;
    int coord_x_rand;
    int y_rand;
    int x_rand;

    //do{
        y_rand = GetRandomValue(1,15);
        x_rand = GetRandomValue(1,39);
    //}while(temUmAORedor(mapa,y_rand,x_rand,10,10));

    coord_x_rand = converterIndiceXParaCoordenada(x_rand);
    coord_y_rand = converterIndiceYParaCoordenada(y_rand);

    inimigo->inimigo_R.x = coord_x_rand;
    inimigo->inimigo_R.y = coord_y_rand;

    int novo_x = x_rand;
    int novo_y = y_rand;

    if (!temEmTodoORedor(mapa,y_rand,x_rand,0,1) || temUmAORedor(mapa,y_rand,x_rand,10,3)){
        if (!reposicionarObjeto(mapa,&novo_y,&novo_x)){
            inimigo->inimigo_posicionado = FALSE;
        }
    }

    if (inimigo->inimigo_posicionado){
        inimigo->inimigo_R.x = converterIndiceXParaCoordenada(novo_x);
        inimigo->inimigo_R.y = converterIndiceYParaCoordenada(novo_y);
        qtde_inimigos++;
    }else{
        INIMIGO z_inimigo = {0};
        *inimigo = z_inimigo;
    }
}

void movimentarInimigos(int mapa[][MAPA_COLUNAS], JOGADOR *jogador, INIMIGO *inimigo){
    if(inimigo->colidiuComInimigo){
        inimigo->emMovimento = 1;
        inimigo->colidiuComInimigo = false;
    }

    float velocidade = 1*inimigo->multiplicador_vel;
    float movimentacoes[4][5]={
        {      0      ,(-velocidade),  0  ,            0             ,            0              }, //cima
        {      0      ,  velocidade , 180 , inimigo->inimigo_R.width , inimigo->inimigo_R.height }, //baixo
        {  velocidade ,      0      ,  90 ,            0             , inimigo->inimigo_R.height }, //direita
        {(-velocidade),      0      , 270 , inimigo->inimigo_R.width ,            0              }  //esquerda
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
        //utilizando a fórmula de distancia entre dois pontos
        int indice_x_inimigo = converterCoordenadaXParaIndice(inimigo->inimigo_R.x);
        int indice_y_inimigo = converterCoordenadaYParaIndice(inimigo->inimigo_R.y);

        int indice_x_jogador = converterCoordenadaXParaIndice(jogador->jogador_R.x);
        int indice_y_jogador = converterCoordenadaYParaIndice(jogador->jogador_R.y);

        int menor_distancia = 100;
        int indice_movimento = 0;

        for(int i=0; i<4; i++){
            int indice_x_inimigo_comparacao = indice_x_inimigo;
            int indice_y_inimigo_comparacao = indice_y_inimigo;
            int distancia;

            if (i==0){
                indice_y_inimigo_comparacao--;
            }

            if (i==1){
                indice_y_inimigo_comparacao++;
            }

            if (i==2){
                indice_x_inimigo_comparacao++;
            }

            if (i==3){
                indice_x_inimigo_comparacao--;
            }

            distancia = calcularDistanciaEntrePontos(
                indice_x_inimigo_comparacao,
                indice_y_inimigo_comparacao,
                indice_x_jogador,
                indice_y_jogador
            );

            if (distancia < menor_distancia){
                menor_distancia = distancia;
                indice_movimento = i;
            }
        }
        inimigo->vel.vx = movimentacoes[indice_movimento][0];
        inimigo->vel.vy = movimentacoes[indice_movimento][1];
        inimigo->angulo = movimentacoes[indice_movimento][2];
        inimigo->origem_textura.x = movimentacoes[indice_movimento][3];
        inimigo->origem_textura.y = movimentacoes[indice_movimento][4];

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

void inverterSentidoDeMovimento(INIMIGO *inimigo){
    //acho que da pra deixar isso acima
    int velocidade = 1*inimigo->multiplicador_vel;
    int movimentacoes[4][5]={
        {      0      ,(-velocidade),  0  ,            0             ,            0              }, //cima
        {      0      ,  velocidade , 180 , inimigo->inimigo_R.width , inimigo->inimigo_R.height }, //baixo
        {  velocidade ,      0      ,  90 ,            0             , inimigo->inimigo_R.height }, //direita
        {(-velocidade),      0      , 270 , inimigo->inimigo_R.width ,            0              }  //esquerda
    };

    int indice_movimento;
    switch (inimigo->angulo){
        //inverter as coisas
        case 0:
            indice_movimento = 1;
            break;

        case 180:
            indice_movimento = 0;
            break;

        case 90:
            indice_movimento = 3;
            break;

        case 270:
            indice_movimento = 2;
            break;
    }

    inimigo->vel.vx = movimentacoes[indice_movimento][0];
    inimigo->vel.vy = movimentacoes[indice_movimento][1];
    inimigo->angulo = movimentacoes[indice_movimento][2];
    inimigo->origem_textura.x = movimentacoes[indice_movimento][3];
    inimigo->origem_textura.y = movimentacoes[indice_movimento][4];
}

void colidirInimigos(INIMIGO *inimigo_a,INIMIGO *inimigo_b){
    inimigo_a->colidiuComInimigo = true;
    inimigo_b->colidiuComInimigo = true;

    if((inimigo_a->angulo == 90 && inimigo_b->angulo == 270) || (inimigo_a->angulo == 270 && inimigo_b->angulo == 90) ||
       (inimigo_a->angulo == 0 && inimigo_b->angulo == 180) || (inimigo_a->angulo == 180 && inimigo_b->angulo == 0)){
        inverterSentidoDeMovimento(inimigo_a);
        inverterSentidoDeMovimento(inimigo_b);
    }

    else if((inimigo_a->angulo == 90 && inimigo_b->angulo == 0) || (inimigo_a->angulo == 90 && inimigo_b->angulo == 180)){
        if(inimigo_a->inimigo_R.x + (inimigo_a->inimigo_R.width - 2) <= inimigo_b->inimigo_R.x){
            inverterSentidoDeMovimento(inimigo_a);
        }else if(inimigo_a->inimigo_R.x + (inimigo_a->inimigo_R.width - 2)  > inimigo_b->inimigo_R.x){
            inverterSentidoDeMovimento(inimigo_b);
        }

    }else if((inimigo_a->angulo == 270 && inimigo_b->angulo == 0) || (inimigo_a->angulo == 270 && inimigo_b->angulo == 180)){
        if(inimigo_a->inimigo_R.x >= inimigo_b->inimigo_R.x + (inimigo_b->inimigo_R.width - 2)){
            inverterSentidoDeMovimento(inimigo_a);
        }else if(inimigo_a->inimigo_R.x < inimigo_b->inimigo_R.x + (inimigo_b->inimigo_R.width - 2)){
            inverterSentidoDeMovimento(inimigo_b);
        }
    }
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

bool checarColisaoEntreInimigos(Rectangle *inimigo_Ra, Rectangle *inimigo_Rb){
    bool colidiu = CheckCollisionRecs(*inimigo_Ra,*inimigo_Rb);
    return colidiu;
}




