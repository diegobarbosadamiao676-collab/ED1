#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define TOTAL_INIMIGOS 5
#define DANO_TIRO 20

typedef enum {
    INIMIGO_VIVO,
    INIMIGO_MORTO
} EstadoInimigo;

typedef struct {
    Vector2 pos;
    float raio;
    int vida;
    EstadoInimigo estado;
} Inimigo;

void inicializarInimigos(Inimigo *vetor, int n) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        ini->pos = (Vector2){ 100.0f + (i * 120.0f), 200.0f };
        ini->raio = 25.0f;
        ini->vida = 10 + (i * 15);
        ini->estado = INIMIGO_VIVO;
    }
}

void atingirInimigo(Inimigo *inimigo, int dano) {
    if (inimigo == NULL || inimigo->estado == INIMIGO_MORTO) return;

    inimigo->vida -= dano;
    if (inimigo->vida <= 0) {
        inimigo->vida = 0;
        inimigo->estado = INIMIGO_MORTO;
    }
}

Inimigo *encontrarInimigoMaisFraco(Inimigo *vetor, int n) {
    if (vetor == NULL) return NULL;

    Inimigo *maisFraco = NULL;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);

        if (ini->estado == INIMIGO_MORTO) continue;

        if (maisFraco == NULL || ini->vida < maisFraco->vida) {
            maisFraco = ini;
        }
    }

    return maisFraco;
}

void desenharInimigos(Inimigo *vetor, int n) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);

        if (ini->estado == INIMIGO_VIVO) {
            DrawCircleV(ini->pos, ini->raio, RED);
            DrawText(TextFormat("HP: %d", ini->vida), (int)ini->pos.x - 20, (int)ini->pos.y - 5, 16, WHITE);
        } else {
            DrawCircleV(ini->pos, ini->raio, DARKGRAY);
            DrawText("MORTO", (int)ini->pos.x - 25, (int)ini->pos.y - 5, 14, LIGHTGRAY);
        }
    }
}

int main() {
    InitWindow(800, 450, "Atividade 4 - Exercicio 2");
    SetTargetFPS(60);

    Inimigo *inimigos = (Inimigo *)malloc(TOTAL_INIMIGOS * sizeof(Inimigo));
    if (inimigos == NULL) return 1;

    inicializarInimigos(inimigos, TOTAL_INIMIGOS);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            Inimigo *alvo = encontrarInimigoMaisFraco(inimigos, TOTAL_INIMIGOS);
            atingirInimigo(alvo, DANO_TIRO);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("[ESPACO] Atacar inimigo mais fraco", 20, 20, 20, DARKGRAY);
            desenharInimigos(inimigos, TOTAL_INIMIGOS);
        EndDrawing();
    }

    free(inimigos);
    inimigos = NULL;

    CloseWindow();
    return 0;
}
