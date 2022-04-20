#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"
#include "construcao.h"
#include "cel_energia.h"
#include "mapa.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42


#define FALSE 0
#define TRUE 1

void criarCelulaDeEnergia(int mapa[][MAPA_COLUNAS] ,BLOCO blocos[][MAPA_COLUNAS], CELULA *cel_energia, int altura_cel_energia, int largura_cel_energia){
    cel_energia->multiplicador_cel_energia = 2;
    cel_energia->cor = BLUE;
    cel_energia->ativa = true;
    cel_energia->cel_energia_R.height = altura_cel_energia;
    cel_energia->cel_energia_R.width = largura_cel_energia;

    cel_energia->origem_textura.x = 0;
    cel_energia->origem_textura.y = 0;

    int coord_y_rand;
    int coord_x_rand;
    int y_rand;
    int x_rand;

    do{
        y_rand = GetRandomValue(1,15);
        x_rand = GetRandomValue(1,40);
    }while(proximoAoJogador(mapa,y_rand,x_rand,3));

    coord_x_rand = converterIndiceXParaCoordenada(x_rand);
    coord_y_rand = converterIndiceYParaCoordenada(y_rand);

    cel_energia->cel_energia_R.x = coord_x_rand;
    cel_energia->cel_energia_R.y = coord_y_rand;

    int novo_x = x_rand;
    int novo_y = y_rand;

    bool colidiu_com_o_bloco = checarColisaoCelEnergiaEBloquinho(&cel_energia->cel_energia_R, &blocos[y_rand][x_rand].bloco_R);
    bool colidiu_com_o_bloco_a_direita = checarColisaoCelEnergiaEBloquinho(&cel_energia->cel_energia_R, &blocos[y_rand][x_rand+1].bloco_R);
    bool colidiu_com_o_bloco_a_esquerda = checarColisaoCelEnergiaEBloquinho(&cel_energia->cel_energia_R, &blocos[y_rand][x_rand-1].bloco_R);

    if (colidiu_com_o_bloco || colidiu_com_o_bloco_a_direita || colidiu_com_o_bloco_a_esquerda){
        printf("x : %d\n",novo_x);
        printf("y : %d\n",novo_y);
        reposicionarCelEnergia(mapa,&novo_y,&novo_x);
    }

    printf("novo x : %d\n",novo_x);
    printf("novo y : %d\n",novo_y);

    cel_energia->cel_energia_R.x = converterIndiceXParaCoordenada(novo_x);
    cel_energia->cel_energia_R.y = converterIndiceYParaCoordenada(novo_y);
}

void energizarJogador(JOGADOR *jogador, CELULA *cel_energia){
    jogador->multiplicador_vel = cel_energia->multiplicador_cel_energia;
    jogador->energizado = true;
}

bool checarColisaoCelEnergiaEBloquinho(Rectangle *cel_energia_R, Rectangle *bloco_R){
    bool colidiu = CheckCollisionRecs(*cel_energia_R,*bloco_R);
    return colidiu;
}

void removerCelEnergia(CELULA *cel_energia){
    cel_energia->ativa = false;
    cel_energia->cel_energia_R.x = 2000;
    cel_energia->cel_energia_R.y = 2000;
}



