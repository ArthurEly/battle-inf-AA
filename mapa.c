#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"
#include <math.h>

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define FALSE 0
#define TRUE 1

/*
    depois tem que mexer aqui
*/
void transcreverMapa(int *id, int y, int x, int y_max, int x_max, BLOCO blocos[][MAPA_COLUNAS]){
    /*
    printf("blocos[%d][%d]:\n",y,x);
    printf("x: %.2f\n",blocos[y][x].bloco_R.x);
    printf("y: %.2f\n",blocos[y][x].bloco_R.y);
    printf("width: %.2f\n",blocos[y][x].bloco_R.width);
    printf("height: %.2f\n",blocos[y][x].bloco_R.height);
    printf("cabei!\n");
    */
    if(*id == 1){
        blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x);
        blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y);
        blocos[y][x].bloco_R.width = LARGURA_BLOCO;
        blocos[y][x].bloco_R.height = ALTURA_BLOCO;
        blocos[y][x].cor = BROWN;
        blocos[y][x].tipo = 1;
        blocos[y][x].destrutivel = true;
    }
    /*da pra deixar mais enxuto isso aqui*/
    if(*id == 7){
        if(y == 0){
            blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y) - TAMANHO_BORDA_MAPA;
        }else{
            blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y);
        }

        if(x == 0){
            blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x) - TAMANHO_BORDA_MAPA;
        }else{
            blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x);
        }
        blocos[y][x].bloco_R.width = TAMANHO_BORDA_MAPA;
        blocos[y][x].bloco_R.height = TAMANHO_BORDA_MAPA;
        if(!blocos[y][x].mudou_de_cor){
            blocos[y][x].cor = GRAY;
        }
        blocos[y][x].tipo = 7;
        blocos[y][x].destrutivel = false;
    }

    if(*id == 8){
        //borda lateral
        if(!blocos[y][x].mudou_de_cor){
            blocos[y][x].cor = GRAY;
        }
        blocos[y][x].tipo = 8;
        blocos[y][x].destrutivel = false;
        blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y);
        if (x == 0){
            blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x) - TAMANHO_BORDA_MAPA;
        }else{
            blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x);
        }
        blocos[y][x].bloco_R.width = TAMANHO_BORDA_MAPA;
        blocos[y][x].bloco_R.height = ALTURA_BLOCO;
    }

    if(*id == 9){
        //borda superior e inferior
        blocos[y][x].bloco_R.x = converterIndiceXParaCoordenada(x);
        if(y == 0){
            blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y) - TAMANHO_BORDA_MAPA ;
        }else{
            blocos[y][x].bloco_R.y = converterIndiceYParaCoordenada(y);
        }
        blocos[y][x].bloco_R.width = LARGURA_BLOCO;
        blocos[y][x].bloco_R.height = TAMANHO_BORDA_MAPA;
        if(!blocos[y][x].mudou_de_cor){
            blocos[y][x].cor = GRAY;
        }
        blocos[y][x].tipo = 9;
        blocos[y][x].destrutivel = false;
    }
}

/*repartir isso em mais funções*/
void atualizarMapa(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], JOGADOR jogador, INIMIGO inimigos[], int contador_inimigos, CELULA cels_energia[], int contador_cels_energia){
    int i,j;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            mapa[i][j] = blocos[i][j].tipo;
        }
    }
    int jogador_x = converterCoordenadaXParaIndice((int)jogador.jogador_R.x);
    int jogador_y = converterCoordenadaYParaIndice((int)jogador.jogador_R.y);

    if (mapa[jogador_y][jogador_x] == 0){
        mapa[jogador_y][jogador_x] = 10;
    }

    int inimigo_x;
    int inimigo_y;

    for(i=0; i<contador_inimigos; i++){
        inimigo_x = converterCoordenadaXParaIndice((int)inimigos[i].inimigo_R.x);
        inimigo_y = converterCoordenadaYParaIndice((int)inimigos[i].inimigo_R.y);
        if (mapa[inimigo_y][inimigo_x] == 0){
            mapa[inimigo_y][inimigo_x] = 11;
        }
    }

    int cel_energia_x;
    int cel_energia_y;

    for(i=0; i<contador_cels_energia; i++){
        cel_energia_x = converterCoordenadaXParaIndice((int)cels_energia[i].cel_energia_R.x);
        cel_energia_y = converterCoordenadaYParaIndice((int)cels_energia[i].cel_energia_R.y);
        if (mapa[cel_energia_y][cel_energia_x] == 0){
            mapa[cel_energia_y][cel_energia_x] = 12;
        }
    }
}

void posicionarJogador(int id, JOGADOR *jogador, int y, int x){
    int coord_x;
    int coord_y;

    if(x != 40)
        coord_x = TAMANHO_BORDA_MAPA + (x-1)*LARGURA_BLOCO;
     else
        coord_x = (x-1)*LARGURA_BLOCO;


    if(y != 15)
        coord_y = CABECALHO + TAMANHO_BORDA_MAPA + (y-1)*ALTURA_BLOCO;
    else
        coord_y = CABECALHO + TAMANHO_BORDA_MAPA + (y-1)*ALTURA_BLOCO + 5;

    jogador->jogador_R.x = coord_x;
    jogador->jogador_R.y = coord_y;
}

int reposicionarObjeto(int mapa[][MAPA_COLUNAS], int *novo_y, int *novo_x){
    int raio_procura=1;
    bool loop = true;
    int x = *novo_x;
    int y = *novo_y;
    printf("entrei com esse x: %d\n",x);
    printf("entrei com esse y: %d\n",y);
    int i,j;

    int indice_comeco_linha;
    int indice_fim_linha;
    int indice_comeco_coluna;
    int indice_fim_coluna;

    int objeto_posicionado = FALSE;
    while (loop){
        if(y-raio_procura > 1)
            indice_comeco_linha = y-raio_procura;
        else
            indice_comeco_linha = 1;

        //printf("indice_comeco_linha %d\n",indice_comeco_linha);
        if (y+raio_procura < MAPA_LINHAS-2)
            indice_fim_linha = y+raio_procura;
        else
            indice_fim_linha = MAPA_LINHAS-2;

        //printf("indice_fim_linha %d\n",indice_fim_linha);

        if(x-raio_procura > 1)
            indice_comeco_coluna = x-raio_procura;
        else
            indice_comeco_coluna = 1;

        //printf("indice_comeco_coluna %d\n",indice_comeco_coluna);
        if(x+raio_procura < MAPA_COLUNAS-2)
            indice_fim_coluna = x+raio_procura;
        else
            indice_fim_coluna = MAPA_COLUNAS-2;

        //printf("indice_fim_coluna %d\n",indice_fim_coluna);

        if(indice_comeco_linha  == 1              &&
           indice_comeco_coluna == 1              &&
           indice_fim_linha     == MAPA_LINHAS-2  &&
           indice_fim_coluna    == MAPA_COLUNAS-2 ){
                printf("MEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEUDEEEEEEEEEEEEEEEEEEEEEEEEEEEUS\n");
                objeto_posicionado = FALSE;
                loop = false;
           }

        for(i=indice_comeco_linha; i<=indice_fim_linha && loop; i++){
            for(j=indice_comeco_coluna; j<=indice_fim_coluna && loop; j++){
                if(temEmTodoORedor(mapa,i,j,0,1) && !temUmAORedor(mapa,i,j,10,5)){
                    loop = false;
                    *novo_x = j;
                    *novo_y = i;
                    objeto_posicionado = TRUE;
                    printf("[!!]\n");
                    printf("%d,%d\n",i,j);
                }
                else{
                    if(mapa[i][j]==11){
                        printf("[I]");
                    }else if(mapa[i][j]==10){
                        printf("[J]");
                    }else{
                        printf("[%d]",mapa[i][j]);
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
        raio_procura++;
    };
    printf("sai com esse x: %d\n",*novo_x);
    printf("sai com esse y: %d\n",*novo_y);
    return objeto_posicionado;
}

int temEmTodoORedor(int mapa[][MAPA_COLUNAS],int y, int x, int tipo, int raio_procura){
    int tem_ao_redor = FALSE;
    int distancia_inicial = 1;
    int contador_ao_redor = 0;
    int i;

    for (i=distancia_inicial; i<=raio_procura; i++){
       if ( mapa[y][x]     == tipo &&
            mapa[y][x+i]   == tipo &&
            mapa[y][x-i]   == tipo &&
            mapa[y+i][x]   == tipo &&
            mapa[y-i][x]   == tipo &&
            mapa[y-i][x-i] == tipo &&
            mapa[y+i][x+i] == tipo ){
            contador_ao_redor++;
        }
    }

    if (contador_ao_redor > 0){
        tem_ao_redor = TRUE;
    }

    return tem_ao_redor;
}

int temUmAORedor(int mapa[][MAPA_COLUNAS],int y, int x, int tipo, int raio_procura){
    int tem_ao_redor = FALSE;
    int distancia_inicial = 1;
    int contador_ao_redor = 0;
    int i;

    for (i=distancia_inicial; i<=raio_procura; i++){
       if ( mapa[y][x]     == tipo ||
            mapa[y][x+i]   == tipo ||
            mapa[y][x-i]   == tipo ||
            mapa[y+i][x]   == tipo ||
            mapa[y-i][x]   == tipo ||
            mapa[y-i][x-i] == tipo ||
            mapa[y+i][x+i] == tipo ){
            contador_ao_redor++;
        }
    }

    if (contador_ao_redor > 0){
        tem_ao_redor = TRUE;
    }

    return tem_ao_redor;
}

int calcularDistanciaEntrePontos(int x_inimigo, int y_inimigo, int x_jogador, int y_jogador){
    float distancia = 0;
    distancia = sqrt(pow(x_jogador - x_inimigo, 2)+ pow(y_jogador - y_inimigo , 2));
    return distancia;
}

int converterCoordenadaXParaIndice(int coord_x){
    float indice_x = (coord_x - TAMANHO_BORDA_MAPA + LARGURA_BLOCO)/LARGURA_BLOCO;

    int x = ceil(indice_x);
    if (x < 1)
        x = 1;

    if (x > 39)
        x = 39;
    return x;
}

int converterCoordenadaYParaIndice(int coord_y){
    float indice_y = (coord_y - CABECALHO - TAMANHO_BORDA_MAPA + ALTURA_BLOCO)/ALTURA_BLOCO;

    int y = ceil(indice_y);

    if (y < 1)
        y = 1;

    if (y > 15)
        y = 15;

    return y;
}

int converterIndiceXParaCoordenada(int indice_x){
    if(indice_x > 0){
        indice_x--;
    }
    int coord_x = TAMANHO_BORDA_MAPA + indice_x*LARGURA_BLOCO;
    return coord_x;
}

int converterIndiceYParaCoordenada(int indice_y){
    if(indice_y > 0){
        indice_y--;
    }
    int coord_y = CABECALHO + TAMANHO_BORDA_MAPA + indice_y*ALTURA_BLOCO;
    return coord_y;
}

void printarMapa(int mapa[][MAPA_COLUNAS]){
    int i,j;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            printf("[%d]",mapa[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}
