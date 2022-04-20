#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "construcao.h"

extern Texture2D tijolo;
Rectangle bloco_textura = {0,0,40,25};

void renderizarBloquinho(BLOCO id){
    if(id.tipo != 0){
        /*DrawRectangle(
            id.bloco_R.x,
            id.bloco_R.y,
            id.bloco_R.width,
            id.bloco_R.height,
            id.cor
        );*/
        DrawTexturePro(
            tijolo,
            bloco_textura,
            id.bloco_R,
            (Vector2){0,
            0},
            0,
            WHITE
        );


        //DrawTextureTiled(tijolo, sourceRec, (Rectangle){0, 2, 4, 9}, (Vector2){id.bloco_R.x,  id.bloco_R.y}, 0, 1, WHITE);
    }

    if(id.tipo == 8 || id.tipo == 9){
        DrawRectangle(
            id.bloco_R.x,
            id.bloco_R.y,
            id.bloco_R.width,
            id.bloco_R.height,
            id.cor
        );
    }
}

void removerBloquinho(BLOCO *id){
    id->tipo = 0;
}
