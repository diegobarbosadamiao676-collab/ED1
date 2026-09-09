#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define TOTAL_INIMIGOS 5
#define VALOR_CURA 15
#define VIDA_MAXIMA 60

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
        ini->vida = 20 + (i * 5);
        ini->estado = INIMIGO_VIVO;
    }
}

void curarTodos(Inimigo *vetor, int n, int cura) {
    if (vetor == NULL) return;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);

        if (ini->estado == INIMIGO_MORTO) continue;

        ini->vida += cura;
        if (ini->vida > VIDA_MAXIMA) {
            ini->vida = VIDA_MAXIMA;
        }
    }
}

void desenharInimigos(Inimigo *vetor, int n) {
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);

        if (ini->estado == INIMIGO_VIVO) {
            DrawCircleV(ini->pos, ini->raio, GREEN);
            DrawText(TextFormat("HP: %d", ini->vida), (int)ini->pos.x - 20, (int)ini->pos.y - 5, 16, WHITE);
        } else {
            DrawCircleV(ini->pos, ini->raio, DARKGRAY);
            DrawText("MORTO", (int)ini->pos.x - 25, (int)ini->pos.y - 5, 14, LIGHTGRAY);
        }
    }
}

int main() {
    InitWindow(800, 450, "Atividade 4 - Exercicio 1");
    SetTargetFPS(60);

    Inimigo *inimigos = (Inimigo *)malloc(TOTAL_INIMIGOS * sizeof(Inimigo));
    if (inimigos == NULL) return 1;

    inicializarInimigos(inimigos, TOTAL_INIMIGOS);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_C)) {
            curarTodos(inimigos, TOTAL_INIMIGOS, VALOR_CURA);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("[C] Curar todos os inimigos vivos", 20, 20, 20, DARKGRAY);
            desenharInimigos(inimigos, TOTAL_INIMIGOS);
        EndDrawing();
    }

    free(inimigos);
    inimigos = NULL;

    CloseWindow();
    return 0;
}
