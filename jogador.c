#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"

void movimentacaoJogador(JOGADOR *jogador){
    int velocidade = 5;
    if (IsKeyDown(KEY_RIGHT) && jogador->jogador_R.x + jogador->jogador_R.width<1000){
        jogador->vel.vx += velocidade;
        jogador->angulo = 90;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = 100;
    }

    else if (IsKeyDown(KEY_LEFT) && jogador->jogador_R.x>0){
        jogador->vel.vx += (-velocidade);
        jogador->angulo = 270;
        jogador->origem_textura.x = 100;
        jogador->origem_textura.y = 0;
    }

    else if (IsKeyDown(KEY_DOWN) && jogador->jogador_R.y + jogador->jogador_R.height<800){
        jogador->vel.vy += velocidade;
        jogador->angulo = 180;
        jogador->origem_textura.x = 100;
        jogador->origem_textura.y = 100;
    }

    else if (IsKeyDown(KEY_UP) && jogador->jogador_R.y>0){
        jogador->vel.vy += (-velocidade);
        jogador->angulo = 0;
        jogador->origem_textura.x = 0;
        jogador->origem_textura.y = 0;
    }

    jogador->jogador_R.x += jogador->vel.vx;
    jogador->jogador_R.y += jogador->vel.vy;

    jogador->vel.vx = 0;
    jogador->vel.vy = 0;
}

//aqui tem que ir o array de construção, projetil inimigo, e inimigos
bool checarColisaoJogadorEInimigo(Rectangle *jogador_R, Rectangle *inimigo_R){
    bool colidiu = CheckCollisionRecs(*jogador_R,*inimigo_R);
    return colidiu;
}
