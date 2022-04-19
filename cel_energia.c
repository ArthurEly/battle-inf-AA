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

void criarCelulaDeEnergia(BLOCO blocos[][MAPA_COLUNAS], CELULA *cel_energia, int altura_cel_energia, int largura_cel_energia){
    cel_energia->multiplicador_cel_energia = 2;
    cel_energia->cor = BLUE;
    cel_energia->ativa = true;
    cel_energia->cel_energia_R.height = altura_cel_energia;
    cel_energia->cel_energia_R.width = largura_cel_energia;

    cel_energia->origem_textura.x = 0;
    cel_energia->origem_textura.y = 0;

    int x_rand = GetRandomValue(10,1000);
    int y_rand = GetRandomValue(100,700);

    cel_energia->cel_energia_R.x = x_rand;
    cel_energia->cel_energia_R.y = y_rand;

    cel_energia->cel_energia_R.x = x_rand;
    cel_energia->cel_energia_R.y = y_rand;

    int x = converterCoordenadaXParaIndice(x_rand);
    int y = converterCoordenadaYParaIndice(y_rand);

    int novo_x = x;
    int novo_y = y;

    bool colidiu_com_o_bloco = checarColisaoCelEnergiaEBloquinho(&cel_energia->cel_energia_R, &blocos[y][x].bloco_R);

    if (colidiu_com_o_bloco){
       reposicionarCelEnergia(blocos,y,x,&novo_y,&novo_x);
    }

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



