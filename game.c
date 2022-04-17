#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"

void SetActiveScreen(int screen_id);

extern Texture2D escudo;
extern Texture2D g_textura_jogador;
extern Texture2D g_textura_inimigo_patrulha;
extern Texture2D g_textura_inimigo_perseguicao;

Rectangle tanque_textura_R = {0,0,50,50};

float timer_segundos = 0;
int segundos = 0;
void timerSegundos(){
    timer_segundos += 0.0166666666666667;
    if(timer_segundos > 1){
        segundos++;
        timer_segundos = 0;
    }
}

int contador_inimigos = 0;
INIMIGO inimigos[3]={0};

JOGADOR jogador = {
        .jogador_R.x = 500,
        .jogador_R.y = 400,
        .jogador_R.height = 100,
        .jogador_R.width = 100,
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
//     .cor =  WHITE,
        .origem_textura={0,0}
};

PROJETIL projeteis[10]={0};
int contador_projeteis= 0;

void DrawGameplayScreen(){
    ClearBackground(RAYWHITE);
    timerSegundos();
    int i,j, vidas=3;

    for(int k; k<vidas; k++){
        DrawTextureEx(escudo, (Vector2){k*60, 0}, 0, 0.1, WHITE);
    }


    //if(segundos % 2 == 0 && timer_segundos == 0){
    if(contador_inimigos < 3){
        criarNovoInimigo(&inimigos[contador_inimigos]);
        contador_inimigos++;
    }else{
        for(i=0; i<3; i++){
            if (inimigos[i].vidas == 0){
                criarNovoInimigo(&inimigos[i]);
            }
        }
    }
    //}

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas !=0){
            movimentarInimigos(&jogador, &inimigos[i]);
        }

        Texture2D tanque_inimigo_textura;

        if(inimigos[i].emMovimento == 2)
            tanque_inimigo_textura = g_textura_inimigo_perseguicao;
        else
            tanque_inimigo_textura = g_textura_inimigo_patrulha;


        DrawRectangle(
            inimigos[i].inimigo_R.x,
            inimigos[i].inimigo_R.y,
            inimigos[i].inimigo_R.height,
            inimigos[i].inimigo_R.width,
            RED
        );

        DrawTexturePro(
            tanque_inimigo_textura,
            tanque_textura_R,
            inimigos[i].inimigo_R,
            inimigos[i].origem_textura,
            inimigos[i].angulo,
            inimigos[i].cor
        );
    }

    DrawRectangle(
        jogador.jogador_R.x,
        jogador.jogador_R.y,
        jogador.jogador_R.height,
        jogador.jogador_R.width,
        BLUE
    );

    DrawTexturePro(
        g_textura_jogador,
        tanque_textura_R,
        jogador.jogador_R,
        jogador.origem_textura,
        jogador.angulo,
        WHITE
        //jogador.cor
    );

    movimentacaoJogador(&jogador);
    for(i=0; i<contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogador.jogador_R, &inimigos[i].inimigo_R)){
            removerInimigo(inimigos,i);
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        if(contador_projeteis < 10){
            contador_projeteis++;
        } else{
            contador_projeteis = 0;
        }
        atirarProjetil(&projeteis[contador_projeteis],jogador);
    }

    for(i=0; i<10; i++){
        if (projeteis[i].em_movimento == 1){
            movimentarProjeteis(&projeteis[i]);
            renderizarProjeteis(&projeteis[i]);

            for(j=0; j<contador_inimigos; j++){
                if (checarColisaoProjeteis(&projeteis[i], &inimigos[j])){
                    printf("aooooooooba\n");
                    removerInimigo(inimigos,j);
                    removerProjetil(projeteis,i);
                }
            }
        }
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
