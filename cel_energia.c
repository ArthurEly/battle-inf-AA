#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "inimigo.h"
#include "jogador.h"
#include "construcao.h"
#include "cel_energia.h"
#include "mapa.h"

void criarCelulaDeEnergia(int mapa[][MAPA_COLUNAS] ,BLOCO blocos[][MAPA_COLUNAS], CELULA *cel_energia){
    cel_energia->multiplicador_cel_energia = 2;
    cel_energia->cor = WHITE;
    cel_energia->cel_energia_R.height = ALTURA_CELS_ENERGIA;
    cel_energia->cel_energia_R.width = LARGURA_CELS_ENERGIA;
    cel_energia->origem_textura.x = 0;
    cel_energia->origem_textura.y = 0;
    cel_energia->cel_energia_posicionada = true;

    int coord_y_rand;
    int coord_x_rand;
    int y_rand;
    int x_rand;

    y_rand = GetRandomValue(1,15);
    x_rand = GetRandomValue(1,39);

    coord_x_rand = converterIndiceXParaCoordenada(x_rand);
    coord_y_rand = converterIndiceYParaCoordenada(y_rand);

    cel_energia->cel_energia_R.x = coord_x_rand;
    cel_energia->cel_energia_R.y = coord_y_rand;

    int novo_x = x_rand;
    int novo_y = y_rand;

    if (temUmAORedor(mapa,y_rand,x_rand,1,1)){
        printf("oooooooi\n");
        if (!reposicionarObjeto(mapa,&novo_y,&novo_x)){
            cel_energia->cel_energia_posicionada = false;
        }
    }

    if(cel_energia->cel_energia_posicionada){
        cel_energia->cel_energia_R.x = converterIndiceXParaCoordenada(novo_x);
        cel_energia->cel_energia_R.y = converterIndiceYParaCoordenada(novo_y);
    }else{
        removerCelEnergia(cel_energia);
    }
}

void energizarJogador(JOGADOR *jogador, CELULA *cel_energia){
    jogador->multiplicador_vel = cel_energia->multiplicador_cel_energia;
    jogador->energizado = true;
}

void removerCelEnergia(CELULA *cel_energia){
    CELULA z_cel_energia = {0};
    *cel_energia = z_cel_energia;
}



