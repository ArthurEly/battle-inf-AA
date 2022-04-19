#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"
#include "construcao.h"
#include "math.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define FALSE 0
#define TRUE 1

void criarNovoInimigo(BLOCO blocos[][MAPA_COLUNAS], INIMIGO *inimigo, int altura_tanque, int largura_tanque){
    /*ARRUMAR ISSO AQUI ANTES DE ENTREGAR KKKKKKKKKKK*/
    inimigo->inimigo_R.height = altura_tanque;
    inimigo->inimigo_R.width = largura_tanque;
    inimigo->vidas = 1;
    inimigo->multiplicador_vel = 1;
    inimigo->cor = WHITE;
    inimigo->emMovimento = 0;

    int xa = GetRandomValue(10,955);
    int ya = GetRandomValue(100,655);

    inimigo->inimigo_R.x = xa;
    inimigo->inimigo_R.y = ya;

    int altura_padrao_construcao = 40;
    int largura_padrao_construcao = 25;
    int tamanho_padrao_borda = 10;
    int borda = 90;

    int i,j;

    float indice_x = (inimigo->inimigo_R.x - tamanho_padrao_borda + largura_padrao_construcao)/largura_padrao_construcao;
    float indice_y = (inimigo->inimigo_R.y - borda - tamanho_padrao_borda + altura_padrao_construcao)/altura_padrao_construcao;

    int x = ceil(indice_x);
    int y = ceil(indice_y);

    bool colidiu = false;
    bool ao_lado = blocos[y][x].tipo != 0 || blocos[y][x+1].tipo != 0 || blocos[y][x-1].tipo != 0;
    if (checarColisaoInimigoEBloquinho(&inimigo->inimigo_R, &blocos[y][x].bloco_R) || ao_lado){
        colidiu = true;
        printf("original: x->%d  y->%d\n",x,y);
    }

    int s=1;
    int novo_x = x;
    int novo_y = y;

    while (colidiu){
        int x_dir= x+s;
        if (x_dir > 41)
            x_dir = 41;

        int x_esq = x-s;
        if (x_dir < 0)
            x_dir = 0;

        int y_acima = y-s;
        if (y_acima < 0)
            y_acima = 0;

        int y_abaixo = y+s;
        if (y_abaixo > 16)
            y_abaixo = 16;

        if(blocos[y][x_dir].tipo == 0){
            printf("entrei 1\n");
            if (buscarVizinhos(blocos,y,x+s) == FALSE){
                printf("opa 1\n");
                novo_x = x+s;
                colidiu = false;
            }
        }

        if(blocos[y][x_esq].tipo == 0){
            printf("entrei 2\n");
            if (buscarVizinhos(blocos,y,x-s) == FALSE){
                printf("opa 2\n");
                novo_x = x-s;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x].tipo == 0){
            printf("entrei 3\n");
            if (buscarVizinhos(blocos,y+s,x) == FALSE){
                printf("opa 3\n");
                novo_y = y+s;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x].tipo == 0){
            printf("entrei 4\n");
            if (buscarVizinhos(blocos,y-s,x) == FALSE){
                printf("opa 4\n");
                novo_y = y-s;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x_dir].tipo == 0){
            printf("entrei 5\n");
            if (buscarVizinhos(blocos,y+s,x+s) == FALSE){
                printf("opa 5\n");
                novo_x = x+s;
                novo_y = y+s;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_esq].tipo == 0){
            printf("entrei 6\n");
            if (buscarVizinhos(blocos,y-s,x-s) == FALSE){
                printf("opa 6\n");
                novo_x = x-s;
                novo_y = y-s;
                colidiu = false;
            }
        }
        s++;
    };

    printf("novo: x->%d  y->%d\n\n\n\n\n",novo_x,novo_y);

    int coord_x = tamanho_padrao_borda + (novo_x-1)*largura_padrao_construcao;
    int coord_y = borda + tamanho_padrao_borda + (novo_y-1)*altura_padrao_construcao;

    inimigo->inimigo_R.x = coord_x;
    inimigo->inimigo_R.y = coord_y;
}

int buscarVizinhos(BLOCO blocos[][42],int y, int x){
    int tem_vizinhos = TRUE;
    if (blocos[y][x].tipo == 0 && blocos[y][x+1].tipo == 0 && blocos[y][x-1].tipo == 0){
        tem_vizinhos = FALSE;
    }
    return tem_vizinhos;
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



