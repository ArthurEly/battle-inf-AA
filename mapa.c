#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include <math.h>

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define FALSE 0
#define TRUE 1

const int altura_padrao_construcao = 40;
const int largura_padrao_construcao = 25;
const int tamanho_padrao_borda = 10;
const int borda = 90;

int contador_x_borda = tamanho_padrao_borda;
int contador_y_borda = borda;
int contador_x_blocos = tamanho_padrao_borda;

void transcreverMapa(int *id, int y, int x, int y_max, int x_max, BLOCO blocos[][MAPA_COLUNAS]){
    if (x == 0)
        contador_x_blocos = tamanho_padrao_borda;

    if (*id == 0){
        blocos[y][x].tipo = 0;
        contador_x_blocos += largura_padrao_construcao;
    }

    if(*id == 1){
        blocos[y][x].bloco_R.x = contador_x_blocos;
        blocos[y][x].bloco_R.y = (borda+tamanho_padrao_borda)+((y-1)*altura_padrao_construcao);
        blocos[y][x].bloco_R.width = largura_padrao_construcao;
        blocos[y][x].bloco_R.height = altura_padrao_construcao;
        blocos[y][x].cor = BROWN;
        blocos[y][x].tipo = 1;
        blocos[y][x].destrutivel = true;
        contador_x_blocos += largura_padrao_construcao;
    }

    if(*id == 2){
        blocos[y][x].bloco_R.x = contador_x_blocos;
        blocos[y][x].bloco_R.y = (borda+tamanho_padrao_borda)+((y-1)*altura_padrao_construcao);
        blocos[y][x].bloco_R.width = largura_padrao_construcao;
        blocos[y][x].bloco_R.height = altura_padrao_construcao;
        blocos[y][x].cor = RED;
        blocos[y][x].tipo = 2;
        blocos[y][x].destrutivel = true;
        contador_x_blocos += largura_padrao_construcao;
    }

        if(*id == 8){
        //borda lateral
        blocos[y][x].bloco_R.y = contador_y_borda;
        blocos[y][x].cor = GRAY;
        blocos[y][x].tipo = 8;
        blocos[y][x].destrutivel = false;

        int coord_x;
        if(x == 0 && y == 0){
            coord_x = x*largura_padrao_construcao;
            blocos[y][x].bloco_R.x = coord_x;
            blocos[y][x].bloco_R.width = tamanho_padrao_borda;
            blocos[y][x].bloco_R.height = tamanho_padrao_borda;
        }
        else if(x == x_max && y == 0){
            coord_x = x*largura_padrao_construcao-largura_padrao_construcao+tamanho_padrao_borda;

            blocos[y][x].bloco_R.x = coord_x;
            blocos[y][x].bloco_R.width = tamanho_padrao_borda;
            blocos[y][x].bloco_R.height = tamanho_padrao_borda;

            contador_y_borda+=tamanho_padrao_borda;

        }
        else{
            if(x == 0 && y != 0 && x == 0 && y != y_max){
                coord_x = x*largura_padrao_construcao, //x

                blocos[y][x].bloco_R.x = coord_x;
                blocos[y][x].bloco_R.width = tamanho_padrao_borda;
                blocos[y][x].bloco_R.height = altura_padrao_construcao;
            }
            else if(x == x_max && y != y_max){
                coord_x = x*largura_padrao_construcao-largura_padrao_construcao+tamanho_padrao_borda, //x

                blocos[y][x].bloco_R.x = coord_x;
                blocos[y][x].bloco_R.width = tamanho_padrao_borda;
                blocos[y][x].bloco_R.height = altura_padrao_construcao;

                contador_y_borda += altura_padrao_construcao;
            }
        }

        if(x == 0 && y == y_max){
            coord_x = x*largura_padrao_construcao;
            blocos[y][x].bloco_R.x = coord_x;
            blocos[y][x].bloco_R.width = tamanho_padrao_borda;
            blocos[y][x].bloco_R.height = tamanho_padrao_borda;
        }

        if(x == x_max && y == y_max){
            coord_x = x*largura_padrao_construcao-largura_padrao_construcao+tamanho_padrao_borda;

            blocos[y][x].bloco_R.x = coord_x;
            blocos[y][x].bloco_R.y = borda+600+tamanho_padrao_borda; //fiquei com preguiça me perdoa
            blocos[y][x].bloco_R.width = tamanho_padrao_borda;
            blocos[y][x].bloco_R.height = tamanho_padrao_borda;
        }

        //resetar
        if (y == y_max)
            contador_y_borda = borda;
    }

    if(*id == 9){
        //borda superior
        float coord_y = 0;

        if (y == 0){
            coord_y = borda+(y*altura_padrao_construcao);
        }
        else{
            coord_y = borda+(y-1)*altura_padrao_construcao+tamanho_padrao_borda;
        }

        blocos[y][x].bloco_R.x = contador_x_borda;
        blocos[y][x].bloco_R.y = coord_y;
        blocos[y][x].bloco_R.width = largura_padrao_construcao;
        blocos[y][x].bloco_R.height = tamanho_padrao_borda;
        blocos[y][x].cor = GRAY;
        blocos[y][x].tipo = 9;
        blocos[y][x].destrutivel = false;
        contador_x_borda += largura_padrao_construcao;

        if (x == 40)
            contador_x_borda = tamanho_padrao_borda;
    }

    if (*id >= 10 && *id <= 12){
        contador_x_blocos += largura_padrao_construcao;
    }
}

void atualizarMapa(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS], JOGADOR jogador, INIMIGO inimigos[], int contador_inimigos){
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
}

void posicionarJogador(int id, JOGADOR *jogador, int y, int x){
    int coord_x;
    int coord_y;

    if(x != 40)
        coord_x = tamanho_padrao_borda + (x-1)*largura_padrao_construcao;
     else
        coord_x = (x-1)*largura_padrao_construcao;


    if(y != 15)
        coord_y = borda + tamanho_padrao_borda + (y-1)*altura_padrao_construcao;
    else
        coord_y = borda + tamanho_padrao_borda + (y-1)*altura_padrao_construcao + 5;

    jogador->jogador_R.x = coord_x;
    jogador->jogador_R.y = coord_y;
}

void reposicionarInimigo(int mapa[][MAPA_COLUNAS], int *novo_y, int *novo_x){
    int raio_procura=1;
    bool colidiu = true;
    int x = *novo_x;
    int y = *novo_y;
    int i,j;
    printf("mpovp ingimgio\n");
    while (colidiu){
        int indice_comeco_linha = y-raio_procura;
        printf("indice_comeco_linha %d\n",indice_comeco_linha);
        int indice_fim_linha = y+raio_procura;
        printf("indice_fim_linha %d\n",indice_fim_linha);
        int indice_comeco_coluna = x-raio_procura;
        printf("indice_comeco_coluna %d\n",indice_comeco_coluna);
        int indice_fim_coluna = x+raio_procura;
        printf("indice_fim_coluna %d\n",indice_fim_coluna);

        for(i=indice_comeco_linha; i<=indice_fim_linha; i++){
            for(j=indice_comeco_coluna; j<=indice_fim_coluna; j++){
                if(mapa[i][j] == 0){
                    if(!buscarVizinhos(mapa,i,j)){
                        colidiu = false;
                        *novo_x = j;
                        *novo_y = i;
                    }
                }
            }
        }
        raio_procura++;
    };
}

void reposicionarCelEnergia(int mapa[][MAPA_COLUNAS], int *novo_y, int *novo_x){
    int raio_procura=1;
    bool colidiu = true;
    int x = *novo_x;
    int y = *novo_y;
    int i,j;
    printf("mpovp ingimgio\n");
    while (colidiu){
        int indice_comeco_linha = y-raio_procura;
        printf("indice_comeco_linha %d\n",indice_comeco_linha);
        int indice_fim_linha = y+raio_procura;
        printf("indice_fim_linha %d\n",indice_fim_linha);
        int indice_comeco_coluna = x-raio_procura;
        printf("indice_comeco_coluna %d\n",indice_comeco_coluna);
        int indice_fim_coluna = x+raio_procura;
        printf("indice_fim_coluna %d\n",indice_fim_coluna);

        for(i=indice_comeco_linha; i<=indice_fim_linha; i++){
            for(j=indice_comeco_coluna; j<=indice_fim_coluna; j++){
                if(mapa[i][j] == 0){
                    if(!buscarVizinhos(mapa,i,j)){
                        colidiu = false;
                        *novo_x = j;
                        *novo_y = i;
                    }
                }
            }
        }
        raio_procura++;
    };
}

int buscarVizinhos(int blocos[][42],int y, int x){
    int tem_vizinhos = TRUE;
    if (blocos[y][x] == 0 && blocos[y][x+1] == 0 && blocos[y][x-1] == 0){
        tem_vizinhos = FALSE;
    }
    return tem_vizinhos;
}

int proximoAoJogador(int mapa[][42],int y, int x, int distancia_minima){
    int i,j;
    int x_jogador;
    int y_jogador;
    int proximo = FALSE;

    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            if(mapa[i][j] == 10){
                y_jogador = i;
                x_jogador = j;
            }
        }
    }

    printf("y jogador: %d\n",y_jogador);
    printf("x jogador: %d\n",x_jogador);
    printf("y inimigo: %d\n",y);
    printf("x inimigo: %d\n",x);

    if (x_jogador+distancia_minima >= x && x_jogador-distancia_minima <= x && y_jogador+distancia_minima >= y && y_jogador-distancia_minima <= y){
        proximo = TRUE;
    }
    return proximo;
}

int buscarLugarVazio(BLOCO blocos[][42],int y, int x){
    int lugar_vazio = FALSE;
    if (blocos[y][x].tipo == 0){
        lugar_vazio = TRUE;
    }
    return lugar_vazio;
}

int converterCoordenadaXParaIndice(int coord_x){
    int altura_padrao_construcao = 40;
    int largura_padrao_construcao = 25;
    int tamanho_padrao_borda = 10;
    int borda = 90;

    float indice_x = (coord_x - tamanho_padrao_borda + largura_padrao_construcao)/largura_padrao_construcao;

    int x = ceil(indice_x);
    if (x < 1)
        x = 1;

    if (x > 39)
        x = 39;
    return x;
}

int converterCoordenadaYParaIndice(int coord_y){
    int altura_padrao_construcao = 40;
    int largura_padrao_construcao = 25;
    int tamanho_padrao_borda = 10;
    int borda = 90;

    float indice_y = (coord_y - borda - tamanho_padrao_borda + altura_padrao_construcao)/altura_padrao_construcao;

    int y = ceil(indice_y);

    if (y < 1)
        y = 1;

    if (y > 15)
        y = 15;

    return y;
}

int converterIndiceXParaCoordenada(int indice_x){
    int coord_x = tamanho_padrao_borda + (indice_x-1)*largura_padrao_construcao;
    return coord_x;
}

int converterIndiceYParaCoordenada(int indice_y){
    int coord_y = borda + tamanho_padrao_borda + (indice_y-1)*altura_padrao_construcao;
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
