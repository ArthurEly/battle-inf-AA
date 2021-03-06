#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "construcao.h"

void renderizarBloquinho(TEXTURAS *texturas, BLOCO bloco){
    Rectangle bloco_textura = {0,0,LARGURA_BLOCO,ALTURA_BLOCO};

    if(bloco.tipo == 1){
        DrawTexturePro(
            texturas->tijolo,
            bloco_textura,
            bloco.bloco_R,
            (Vector2){0,
            0},
            0,
            WHITE
        );
    }

    if(bloco.tipo >= 6 && bloco.tipo <= 9){
        DrawRectangle(
            bloco.bloco_R.x,
            bloco.bloco_R.y,
            bloco.bloco_R.width,
            bloco.bloco_R.height,
            bloco.cor
        );
    }
}

void mudarCorBorda(BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS], Color nova_cor){
    int i,j;
    for (i=0;i<MAPA_LINHAS; i++){
        for (j=0;j<MAPA_COLUNAS; j++){
            if(blocos[i][j].tipo >= 7 && blocos[i][j].tipo <= 9){
                blocos[i][j].cor = nova_cor;
                blocos[i][j].mudou_de_cor = true;
            }
        }
    }
}

void removerBloquinho(BLOCO *bloco){
    bloco->tipo = 0;
}
