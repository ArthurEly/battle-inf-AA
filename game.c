#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"

void SetActiveScreen(int screen_id);
extern Texture2D g_textura_jogador;
extern Texture2D g_textura_inimigo_patrulha;
extern Texture2D g_textura_inimigo_perseguicao;

JOGADOR jogador = {
        .x = 500,
        .y = 400,
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .altura = 50,
        .largura = 50,
        .cor = WHITE,
        .origem_textura={50,50}
};

float timer_segundos = 0;
int segundos = 0;

void timerSegundos(){
    timer_segundos += 0.0166666666666667;
    if(timer_segundos > 1){
        segundos++;
        timer_segundos = 0;
    }
}

Rectangle tanque_textura_R = {0,0,50,50};
Rectangle tanque_origem_textura = {50,50};

int contador_inimigos = 0;
INIMIGO inimigos[3]={{0}};

Rectangle jogador_R = {0,0,50*2,50*2};
Rectangle inimigos_R[3]={
    {0,0,50*2,50*2},
    {0,0,50*2,50*2},
    {0,0,50*2,50*2},
};

void DrawGameplayScreen(){
    ClearBackground(RAYWHITE);
    timerSegundos();
    int i;

    DrawTexturePro(
        g_textura_jogador,
        tanque_textura_R,
        jogador_R,
        jogador.origem_textura,
        jogador.angulo,
        jogador.cor
    );

    movimentacaoJogador(&jogador, &jogador_R);
    for(i=0; i<contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogador_R, &inimigos_R[i])){
            removerInimigo(&inimigos,i);
        }
    }

    //if(segundos % 2 == 0 && timer_segundos == 0){
        if(contador_inimigos < 3){
            criarNovoInimigo(&inimigos[contador_inimigos],&inimigos_R[contador_inimigos]);
            contador_inimigos++;
        }else{
            for(i=0; i<3; i++){
                if (inimigos[i].vidas == 0){
                    criarNovoInimigo(&inimigos[i],&inimigos_R[i]);
                }
            }
        }
    //}

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas !=0){
            movimentarInimigos(&jogador, &inimigos[i], &inimigos_R[i]);
        }

        Texture2D tanque_inimigo_textura;
        if(inimigos[i].emMovimento == 2)
            tanque_inimigo_textura = g_textura_inimigo_perseguicao;
        else
            tanque_inimigo_textura = g_textura_inimigo_patrulha;


        DrawTexturePro(
            tanque_inimigo_textura,
            tanque_textura_R,
            inimigos_R[i],
            inimigos[i].origem_textura,
            inimigos[i].angulo,
            inimigos[i].cor
        );
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
