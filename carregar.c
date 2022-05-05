#include "raylib.h"
#include "stdio.h"
#include "carregar.h"
#include "game.h"
#include "main.h"

int count = 0;
char **droppedFiles = { 0 };

void verificarArquivosDropados(void){
    if (IsFileDropped()){
        droppedFiles = GetDroppedFiles(&count);
    }
}

void DrawCarregarScreen(GAME *jogo){
        verificarArquivosDropados();
        ClearBackground(RAYWHITE);
        DrawTextureEx(jogo->texturas.carregar, (Vector2){-75,0}, 0, 1, WHITE);
        if(count !=0){
            FILE *mapa_fp;
            mapa_fp = fopen(droppedFiles[0],"r");
            if(mapa_fp != NULL){
                carregarMapa(jogo->mapa.mapa_inicial,mapa_fp);
                printarMapa(jogo->mapa.mapa_inicial);
                jogo->mapa.mapa_foi_pre_carregado = TRUE;
            }else{
                perror("erro ao carregar um mapa ");
            }
            fclose(mapa_fp);
            SetActiveScreen(11);
        }

    if(IsKeyPressed(KEY_P)){
        SetActiveScreen(10);
    }
}
