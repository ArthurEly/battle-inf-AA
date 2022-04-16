#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"

void movimentacaoJogador(JOGADOR *jogador, Rectangle *jogador_R){
    if (IsKeyDown(KEY_RIGHT)){
        jogador->vel.vx += 2;
        jogador->angulo = 90;
    }

    else if (IsKeyDown(KEY_LEFT)){
        jogador->vel.vx += (-2);
        jogador->angulo = 270;
    }

    else if (IsKeyDown(KEY_DOWN)){
        jogador->vel.vy += 2;
        jogador->angulo = 180;
    }

    else if (IsKeyDown(KEY_UP)){
        jogador->vel.vy += (-2);
        jogador->angulo = 0;
    }

    jogador->x += jogador->vel.vx;
    jogador->y += jogador->vel.vy;

    jogador_R->x = jogador->x;
    jogador_R->y = jogador->y;

    jogador->vel.vx = 0;
    jogador->vel.vy = 0;
}

//aqui tem que ir o array de construção, projetil inimigo, e inimigos
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*inimigo_R);
    return colidiu;
}
