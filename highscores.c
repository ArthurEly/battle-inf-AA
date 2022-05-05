#include "raylib.h"
#include "stdio.h"
#include "highscores.h"
#include "game.h"
#include "construcao.h"
#include "string.h"

void SetActiveScreen(int screen_id);

void DrawHighScoresScreen(GAME *jogo){
    ClearBackground(WHITE);
    DrawTextureEx(jogo->texturas.highscore, (Vector2){-75,0}, 0, 1, WHITE);

    HIGHSCORE highscores[QTDE_HIGHSCORES]={0};

    //resetarHighscores();
    lerHighscores(highscores);

    DrawTextEx(jogo->fontes.fonte_legal, TextFormat("Nome"),      (Vector2){(300 - (MeasureTextEx(jogo->fontes.fonte_legal, TextFormat("Nome"), 36, 2).x)/2), 275}, 36, 2, WHITE);
    DrawTextEx(jogo->fontes.fonte_legal, TextFormat("Pontos"),    (Vector2){(650 - (MeasureTextEx(jogo->fontes.fonte_legal, TextFormat("Pontos"), 36, 2).x)/2), 275}, 36, 2, WHITE);
    DrawTextEx(jogo->fontes.fonte_legal, TextFormat("Tempo"),     (Vector2){(950 - (MeasureTextEx(jogo->fontes.fonte_legal, TextFormat("Tempo"), 36, 2).x)/2), 275}, 36, 2, WHITE);
    Color cor;
    for (int i = 0; i < QTDE_HIGHSCORES; i++){
        if(i == 0)
            cor = YELLOW;
        else if (i == 1)
            cor = GRAY;
        else if (i == 2)
            cor = BROWN;
        else
            cor = WHITE;

        DrawTextEx(jogo->fontes.fonte_legal, TextFormat("%d",(i+1)),                    (Vector2){50, 325 + 50*(i+1)}, 24, 2, cor);
        DrawTextEx(jogo->fontes.fonte_legal, TextFormat("%s", highscores[i].nome),      (Vector2){100, 325 + 50*(i+1)}, 22, 2, cor);
        DrawTextEx(jogo->fontes.fonte_legal, TextFormat("%i", highscores[i].pontuacao), (Vector2){575, 325 + 50*(i+1)}, 22, 2, cor);
        DrawTextEx(jogo->fontes.fonte_legal, TextFormat("%ds",highscores[i].segundos),  (Vector2){900, 325 + 50*(i+1)}, 22, 2, cor);
    }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}

void resetarHighscores(){
    FILE *highscores_fp;
    highscores_fp = fopen("highscore.bin","wb+");
    int i;
    HIGHSCORE highscore;
    if (highscores_fp != NULL){
        rewind(highscores_fp);
        for (i=1; i<=QTDE_HIGHSCORES; i++){
            strcpy(highscore.nome,"-");
            highscore.pontuacao = 0;
            highscore.segundos = 0;
            if(fwrite(&highscore,sizeof(HIGHSCORE),1,highscores_fp) != (-1)){

            }
        }
    }else{
        perror("erro na leitura highscores: ");
    }

    fclose(highscores_fp);
}

void escreverHighscores(HIGHSCORE highscores[]){
    FILE *highscores_fp;
    highscores_fp = fopen("highscore.bin","wb+");
    int i;

    if (highscores_fp != NULL){
        rewind(highscores_fp);
        for(i=0; i<QTDE_HIGHSCORES; i++){
            if(fwrite(&highscores[i],sizeof(HIGHSCORE),1,highscores_fp) != (-1)){

            }else{
                perror("big problema: ");
            }
        }
    }else{
        perror("erro na leitura highscores: ");
    }

    fclose(highscores_fp);
}

void lerHighscores(HIGHSCORE highscores[]){
    FILE *highscores_fp;
    highscores_fp = fopen("highscore.bin","rb+");
    int i = 0;
    HIGHSCORE highscore;

    if (highscores_fp != NULL){
        rewind(highscores_fp);
        while(!feof(highscores_fp)){
           if(fread(&highscore,sizeof(HIGHSCORE),1,highscores_fp) != (-1)){
                strcpy(highscores[i].nome,highscore.nome);
                highscores[i].pontuacao = highscore.pontuacao;
                highscores[i].segundos = highscore.segundos;
            }
            i++;
        }
    }else{
        perror("erro na leitura highscores: ");
    }

    fclose(highscores_fp);
}

void lerUltimoColocado(HIGHSCORE *highscore){
    FILE *highscores_fp;
    highscores_fp = fopen("highscore.bin","rb+");
    HIGHSCORE ultimo_highscore;
    if (highscores_fp != NULL){
        //posicao varia de 0 a 4
        fseek(highscores_fp,(QTDE_HIGHSCORES-1)*sizeof(HIGHSCORE),SEEK_SET);
        if(fread(&ultimo_highscore,sizeof(HIGHSCORE),1,highscores_fp) != (-1)){

        }
        *highscore = ultimo_highscore;
    }else{
        perror("erro na leitura highscores: ");
    }

    fclose(highscores_fp);
}

void atualizarHighscore(HIGHSCORE *novo_highscore){
    int i = 0;

    HIGHSCORE highscores_antigos[QTDE_HIGHSCORES]={0};

    HIGHSCORE highscores_atualizados[QTDE_HIGHSCORES]={0};

    lerHighscores(highscores_antigos);

    FILE *highscores_fp;
    highscores_fp = fopen("highscore.bin","wb+");

    int posicionado = FALSE;

    for (i=0; i<QTDE_HIGHSCORES && !posicionado; i++){
        if(novo_highscore->pontuacao > highscores_antigos[i].pontuacao && !posicionado){
            highscores_atualizados[i] = *novo_highscore;
            posicionado = TRUE;
        }else if (novo_highscore->pontuacao == highscores_antigos[i].pontuacao && !posicionado){
            if(novo_highscore->segundos < highscores_antigos[i].segundos){
                highscores_atualizados[i] = *novo_highscore;
                posicionado = TRUE;
            }
        }
    }

    int j=0;
    for (i=0; i<QTDE_HIGHSCORES ; i++){
        if(highscores_atualizados[i].pontuacao == 0){
            highscores_atualizados[i] = highscores_antigos[j];
            j++;
        }
    }

    escreverHighscores(highscores_atualizados);

    fclose(highscores_fp);
}
