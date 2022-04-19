#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"

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
}

void atualizarMapa(int mapa[][MAPA_COLUNAS], BLOCO blocos[][MAPA_COLUNAS]){
    int i,j;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            mapa[i][j] = blocos[i][j].tipo;
        }
    }
}

void posicionarJogador(int id, JOGADOR *jogador, int y, int x){
    if(id==10){
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
}

void reposicionarInimigo(BLOCO blocos[][MAPA_COLUNAS],int y, int x, int *novo_y, int *novo_x){
    int indice_procura=1;
    bool colidiu = true;

    while (colidiu){
        /*pra ele nao sair do tamanho do mapa*/
        int x_dir= x+indice_procura;
        if (x_dir > MAPA_COLUNAS-1)
            x_dir = MAPA_COLUNAS-1;

        int x_esq = x-indice_procura;
        if (x_dir < 0)
            x_dir = 0;

        int y_acima = y-indice_procura;
        if (y_acima < 0)
            y_acima = 0;

        int y_abaixo = y+indice_procura;
        if (y_abaixo > MAPA_LINHAS-1)
            y_abaixo = MAPA_LINHAS-1;

        if(blocos[y][x_dir].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y,x_dir) == FALSE){
                *novo_x = x_dir;
                colidiu = false;
            }
        }

        if(blocos[y][x_esq].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y,x_esq) == FALSE){
                *novo_x = x_esq;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_abaixo,x) == FALSE){
                *novo_y = y_abaixo;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_acima,x) == FALSE){
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x_dir].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_abaixo,x_dir) == FALSE){
                *novo_x = x_dir;
                *novo_y = y_abaixo;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x_esq].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_abaixo,x_esq) == FALSE){
                *novo_x = x_esq;
                *novo_y = y_abaixo;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_dir].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_acima,x_dir) == FALSE){
                *novo_x = x_dir;
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_esq].tipo == 0 && colidiu){
            if (buscarVizinhos(blocos,y_acima,x_esq) == FALSE){
                *novo_x = x_esq;
                *novo_y = y_acima;
                colidiu = false;
            }
        }
        indice_procura++;
    };
}

void reposicionarCelEnergia(BLOCO blocos[][MAPA_COLUNAS],int y, int x, int *novo_y, int *novo_x){
    int indice_procura=1;
    bool colidiu = true;

    while (colidiu){
        /*pra ele nao sair do tamanho do mapa*/
        int x_dir= x+indice_procura;
        if (x_dir > MAPA_COLUNAS-1)
            x_dir = MAPA_COLUNAS-1;

        int x_esq = x-indice_procura;
        if (x_dir < 0)
            x_dir = 0;

        int y_acima = y-indice_procura;
        if (y_acima < 0)
            y_acima = 0;

        int y_abaixo = y+indice_procura;
        if (y_abaixo > MAPA_LINHAS-1)
            y_abaixo = MAPA_LINHAS-1;

        if(blocos[y][x_dir].tipo == 0){
            if (buscarLugarVazio(blocos,y,x_dir)){
                *novo_x = x_dir;
                colidiu = false;
            }
        }

        if(blocos[y][x_esq].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y,x_esq)){
                *novo_x = x_esq;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_abaixo,x)){
                *novo_y = y_abaixo;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_acima,x)){
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        if(blocos[y_abaixo][x_dir].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_abaixo,x_dir)){
                *novo_x = x_dir;
                *novo_y = y_abaixo;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_esq].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_acima,x_esq)){
                *novo_x = x_esq;
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_dir].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_acima,x_dir)){
                *novo_x = x_dir;
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        if(blocos[y_acima][x_esq].tipo == 0 && colidiu){
            if (buscarLugarVazio(blocos,y_acima,x_esq)){
                *novo_x = x_esq;
                *novo_y = y_acima;
                colidiu = false;
            }
        }

        indice_procura++;
    };
}

int buscarVizinhos(BLOCO blocos[][42],int y, int x){
    int tem_vizinhos = TRUE;
    if (blocos[y][x].tipo == 0 && blocos[y][x+1].tipo == 0 && blocos[y][x-1].tipo == 0){
        tem_vizinhos = FALSE;
    }
    return tem_vizinhos;
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

    return x;
}

int converterCoordenadaYParaIndice(int coord_y){
    int altura_padrao_construcao = 40;
    int largura_padrao_construcao = 25;
    int tamanho_padrao_borda = 10;
    int borda = 90;

    float indice_y = (coord_y - borda - tamanho_padrao_borda + altura_padrao_construcao)/altura_padrao_construcao;

    int y = ceil(indice_y);

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
