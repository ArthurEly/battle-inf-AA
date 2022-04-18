#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

const int altura_padrao_construcao = 40;
const int largura_padrao_construcao = 25;

const int tamanho_padrao_borda = 10;

const int borda = 90;

int contador_x_borda = tamanho_padrao_borda;
int contador_y_borda = borda;

int contador_x_blocos = tamanho_padrao_borda;

void transcreverMapa(int *bloco, int y, int x, int y_max, int x_max, BLOCO blocos[][42]){
    if (x == 0)
        contador_x_blocos = tamanho_padrao_borda;

    if (*bloco == 0){
        contador_x_blocos += largura_padrao_construcao;
    }

    if(*bloco == 1){
        blocos[y][x].bloco_R.x = contador_x_blocos;
        blocos[y][x].bloco_R.y = (borda+tamanho_padrao_borda)+((y-1)*altura_padrao_construcao);
        blocos[y][x].bloco_R.width = largura_padrao_construcao;
        blocos[y][x].bloco_R.height = altura_padrao_construcao;
        blocos[y][x].cor = BROWN;
        blocos[y][x].tipo = 1;
        contador_x_blocos += largura_padrao_construcao;
    }

    if(*bloco == 2){
        blocos[y][x].bloco_R.x = contador_x_blocos;
        blocos[y][x].bloco_R.y = (borda+tamanho_padrao_borda)+((y-1)*altura_padrao_construcao);
        blocos[y][x].bloco_R.width = largura_padrao_construcao;
        blocos[y][x].bloco_R.height = altura_padrao_construcao;
        blocos[y][x].cor = RED;
        blocos[y][x].tipo = 2;
        contador_x_blocos += largura_padrao_construcao;
    }

    if(*bloco == 9){
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
        contador_x_borda += largura_padrao_construcao;

        if (x == 40)
            contador_x_borda = tamanho_padrao_borda;
    }

    if(*bloco == 8){
        //borda lateral
        blocos[y][x].bloco_R.y = contador_y_borda;
        blocos[y][x].cor = GRAY;
        blocos[y][x].tipo = 8;

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
}
