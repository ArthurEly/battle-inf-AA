#ifndef CONSTRUCAO_H_INCLUDED
#define CONSTRUCAO_H_INCLUDED
#include "raylib.h"

typedef struct bloco{
    Rectangle bloco_R;
    int indice_y;
    int indice_x;
    Color cor;
    bool destrutivel;
    bool destruido;
    int tipo;

}BLOCO;

#endif
