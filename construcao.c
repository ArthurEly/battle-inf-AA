#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "construcao.h"

void renderizarBloquinho(BLOCO id){
    if(id.tipo != 0){
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
