#include "game.h"
#include "raylib.h"
#include "stdio.h"
#include "jogador.h"
#include "inimigo.h"
#include "projetil.h"
#include "construcao.h"
#include "mapa.h"
#include "cel_energia.h"

#define NRO_INIMIGOS 2
#define NRO_PROJETEIS 100
#define NRO_CELS_ENERGIA 3

#define MAPA_LINHAS 17
#define MAPA_COLUNAS 42

#define TAMANHO_TANQUES 35

#define FALSE 0
#define TRUE 1

void SetActiveScreen(int screen_id);

extern Texture2D energia;
extern Texture2D tijolo;
extern Texture2D escudo;
extern Texture2D g_textura_jogador;
extern Texture2D g_textura_inimigo_patrulha;
extern Texture2D g_textura_inimigo_perseguicao;

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

INIMIGO inimigos[NRO_INIMIGOS]={0};

PROJETIL projeteis[NRO_PROJETEIS]={0};
int contador_projeteis= 0;

int mapa[MAPA_LINHAS][MAPA_COLUNAS] = {
    //8-> borda lateral
    //9-> borda superior/inferior
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8},
    {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,8},
    {8,1,0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,8},
    {8,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,8},
    {8,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,0,0,0,1,0,8},
    {8,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
    {8,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,8},
    {8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8}
};
BLOCO blocos[MAPA_LINHAS][MAPA_COLUNAS] = {0};

Rectangle tanque_textura_R = {0,0,TAMANHO_TANQUES/2,TAMANHO_TANQUES/2};
Rectangle energia_textura = {0,0, 25, 25};

JOGADOR jogador = {
        .jogador_R.x = 1100,
        .jogador_R.y = 600,
        .jogador_R.height = TAMANHO_TANQUES, //aqui também
        .jogador_R.width = TAMANHO_TANQUES, //aqui também
        .vidas = 3,
        .pontuacao = 0,
        .angulo = 0,
        .vel = {0,0},
        .multiplicador_vel = 1,
        .cor =  {255, 255, 255, 255},
        .origem_textura={0,0}
};
int tanques_posicionados=0;

CELULA cels_energia[NRO_CELS_ENERGIA]={0};
int contador_cels_energia = 0;
int altura_cel_energia = 35;
int largura_cel_energia = 35;
int contador_interno_cel_energia = 0;

void DrawGameplayScreen(){
    ClearBackground(RAYWHITE);
    int i,j,k;
    timerSegundos();
    int fase=1;
    /**
        MAPA
    */
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            transcreverMapa(&mapa[i][j],i,j,(MAPA_LINHAS-1),(MAPA_COLUNAS-1),blocos);
            renderizarBloquinho(blocos[i][j]);
        }
    }

    DrawText(TextFormat("Fase: %i", fase), 600, 20, 48, ORANGE);
    DrawText(TextFormat("Pontuacao: %i", jogador.pontuacao), 250, 30, 36, DARKGRAY);
    for(i=0; i<jogador.vidas; i++){
        DrawTextureEx(escudo, (Vector2){i*65, 0}, 0, 0.11, WHITE);
    }

    if(!tanques_posicionados){
        for(i=0; i<MAPA_LINHAS; i++){
            for(j=0; j<MAPA_COLUNAS; j++){
                if (mapa[i][j] == 10){
                    posicionarJogador(mapa[i][j],&jogador,i,j);
                }
            }
        }
        tanques_posicionados = 1;
    }

    /**
        INIMIGOS
    */
    if(contador_inimigos < NRO_INIMIGOS){
        if(segundos % 1 == 0 && timer_segundos == 0){
            criarNovoInimigo(mapa, blocos, &inimigos[contador_inimigos],TAMANHO_TANQUES,TAMANHO_TANQUES);
            contador_inimigos++;
        }
    }else{
        if(segundos % 1 == 0 && timer_segundos == 0){
            bool nao_reviveu_inimigo = true;
            for(i=0;i<contador_inimigos;i++){
                if(inimigos[i].vidas == 0 && nao_reviveu_inimigo){
                    criarNovoInimigo(mapa, blocos, &inimigos[i],TAMANHO_TANQUES,TAMANHO_TANQUES);
                    nao_reviveu_inimigo = false;
                }
            }
        }
    }

    for(i=0;i<contador_inimigos;i++){
        if(inimigos[i].vidas == 1){
            int contador_colisao_inimigo = 0;

            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if (blocos[j][k].tipo != 0){
                        if(checarColisaoInimigoEBloquinho(&inimigos[i].inimigo_R, &blocos[j][k].bloco_R)){
                            contador_colisao_inimigo++;
                        }
                    }
                }
            }

            //COLISAO INIMIGOS
            /*for(j=i+1; j<contador_inimigos; j++){
                if(checarColisaoEntreInimigos(&inimigos[i].inimigo_R, &inimigos[j].inimigo_R)){
                    printf("inimgios colindond\n\n");
                    colidirInimigos(&inimigos[i].inimigo_R, &inimigos[j].inimigo_R);
                }
            }*/

            if (contador_colisao_inimigo > 0){
                girarSentidoHorario(&inimigos[i]);
                inimigos[i].colidindo = true;
            } else {
                inimigos[i].colidindo = false;
            }

            movimentarInimigos(&jogador, &inimigos[i]);

            Texture2D tanque_inimigo_textura;

            if(inimigos[i].emMovimento == 2){
                tanque_inimigo_textura = g_textura_inimigo_perseguicao;

                if(contador_projeteis < NRO_PROJETEIS)
                    contador_projeteis++;
                else
                    contador_projeteis = 0;

                atirarProjetilInimigo(&projeteis[contador_projeteis],inimigos[i]);
            }
            else{
                tanque_inimigo_textura = g_textura_inimigo_patrulha;
            }

            DrawRectangle(
                inimigos[i].inimigo_R.x,
                inimigos[i].inimigo_R.y,
                inimigos[i].inimigo_R.height,
                inimigos[i].inimigo_R.width,
                DARKGREEN
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
    }
    /**
        JOGADOR
    */
    DrawRectangle(
        jogador.jogador_R.x,
        jogador.jogador_R.y,
        jogador.jogador_R.height,
        jogador.jogador_R.width,
        SKYBLUE
    );

    DrawTexturePro(
        g_textura_jogador,
        tanque_textura_R,
        jogador.jogador_R,
        jogador.origem_textura,
        jogador.angulo,
        jogador.cor
    );

    if (IsKeyDown(KEY_LEFT) ||
        IsKeyDown(KEY_RIGHT)||
        IsKeyDown(KEY_DOWN) ||
        IsKeyDown(KEY_UP)   ){
            if(jogador.colidindo == false){
                movimentacaoJogador(&jogador);
            }
    }

    for(i=0; i<contador_inimigos; i++){
        if (checarColisaoJogadorEInimigo(&jogador.jogador_R, &inimigos[i].inimigo_R)){
            removerInimigo(inimigos,i);
            if (jogador.vidas > 0){
                jogador.vidas--;
            }
        }
    }

    int contador_colisoes = 0;
    for(i=0; i<MAPA_LINHAS; i++){
        for(j=0; j<MAPA_COLUNAS; j++){
            if (blocos[i][j].tipo != 0){
                if(checarColisaoJogadorEBloquinho(&jogador.jogador_R, &blocos[i][j].bloco_R)){
                    contador_colisoes++;
                }
            }
        }
    }

    if(contador_colisoes > 0)
        pararJogador(&jogador);
    else
        retomarJogador(&jogador);

    if(IsKeyPressed(KEY_SPACE)){
        if(contador_projeteis < NRO_PROJETEIS){
            contador_projeteis++;
        }
        else{
            contador_projeteis = 0;
        }
        atirarProjetilJogador(&projeteis[contador_projeteis],jogador);
    }
    /**
        PROJETEIS
    */
    for(i=0; i<NRO_PROJETEIS; i++){
        if (projeteis[i].em_movimento == 1){
            movimentarProjeteis(&projeteis[i]);
            renderizarProjeteis(&projeteis[i]);

            for(j=0; j<contador_inimigos; j++){
                if(projeteis[i].tanque_de_origem == 'j'){
                    if (checarColisaoProjeteisEInimigo(&projeteis[i], &inimigos[j])){
                        printf("oia eu aqui de novo");
                        removerInimigo(inimigos,j);
                        removerProjetil(projeteis,i);
                        jogador.pontuacao += 800;
                    }
                } else{
                    if (checarColisaoProjeteisEJogador(&projeteis[i], &jogador)){
                        removerProjetil(projeteis,i);
                        jogador.vidas--;
                        printf("vose moreu\n");
                    }
                }
            }
            for(j=0; j<MAPA_LINHAS; j++){
                for(k=0; k<MAPA_COLUNAS; k++){
                    if(blocos[j][k].tipo == 1 || blocos[j][k].tipo == 8 || blocos[j][k].tipo == 9){
                        if (checarColisaoProjeteisEBlocos(&projeteis[i], &blocos[j][k])){
                            if(blocos[j][k].destrutivel){
                                removerBloquinho(&blocos[j][k]);
                            }
                            removerProjetil(projeteis,i);
                        }
                    }
                }
            }

            for(j=i+1; j<NRO_PROJETEIS; j++){
                if (projeteis[j].em_movimento == 1){
                    if(checarColisaoDeProjeteis(&projeteis[i],&projeteis[j])){
                        removerProjetil(projeteis,i);
                        removerProjetil(projeteis,j);
                    }
                }
            }
        }
    }
    /**
        CELULAS DE ENERGIA
    */
    if(contador_cels_energia < NRO_CELS_ENERGIA){
        if(segundos % 1 == 0 && timer_segundos == 0){
            criarCelulaDeEnergia(mapa, blocos, &cels_energia[contador_cels_energia],altura_cel_energia,largura_cel_energia);
            contador_cels_energia++;
        }
    }else{
        if(segundos % 1 == 0 && timer_segundos == 0){
            for(i=0; i<NRO_CELS_ENERGIA; i++){
                if (cels_energia[i].ativa == false){
                    criarCelulaDeEnergia(mapa, blocos, &cels_energia[i],altura_cel_energia,largura_cel_energia);
                }
            }
        }
    }

    for(i=0; i<NRO_CELS_ENERGIA; i++){
        if(cels_energia[i].ativa == true){
            DrawRectangle(
                cels_energia[i].cel_energia_R.x,
                cels_energia[i].cel_energia_R.y,
                cels_energia[i].cel_energia_R.width,
                cels_energia[i].cel_energia_R.height,
                YELLOW
            );
            DrawTexturePro(
            energia,
            energia_textura,
            cels_energia[i].cel_energia_R,
            cels_energia[i].origem_textura,
            0,
            cels_energia[i].cor
         );

            if (checarColisaoJogadorECelEnergia(&jogador.jogador_R, &cels_energia[i].cel_energia_R)){
                if (contador_interno_cel_energia < 20){
                    contador_interno_cel_energia += 10;
                }
                energizarJogador(&jogador,&cels_energia[i]);
                removerCelEnergia(&cels_energia[i]);
            }
        }
    }

    if (jogador.energizado == true){
        if(segundos % 1 == 0 && timer_segundos == 0){
            contador_interno_cel_energia--;
            if(contador_interno_cel_energia == 0){
                jogador.energizado = false;
                jogador.multiplicador_vel = 1;
                jogador.cor = WHITE;

            }
        }
        if (timer_segundos>0 && timer_segundos < 0.5){
                jogador.cor = YELLOW;
            }else if(timer_segundos>0.5){
                jogador.cor = WHITE;
            }
    }
    /**
        MAPA DNV
    */
    atualizarMapa(mapa,blocos,jogador,inimigos,contador_inimigos);

    if(IsKeyPressed(KEY_S)){
        printarMapa(mapa);
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(111);
    }
}
