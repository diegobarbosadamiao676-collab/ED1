
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define MAX_ENTIDADES 20
#define RAIO_JOGADOR 20.0f

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

typedef union {
    int dano;
    int valor;
} ExtraEntidade;

typedef struct {
    TipoEntidade tipo;
    Vector2 pos;
    float raio;
    int vida;
    Color cor;
    ExtraEntidade extra;
} Entidade;

Entidade *vetorEntidades[MAX_ENTIDADES];
int totalEntidades = 0;

Entidade *criarEntidade(TipoEntidade tipo, Vector2 pos) {
    Entidade *e = (Entidade *)malloc(sizeof(Entidade));
    if (e == NULL) return NULL;

    e->tipo = tipo;
    e->pos = pos;
    e->raio = (tipo == ENTIDADE_JOGADOR) ? RAIO_JOGADOR : (tipo == ENTIDADE_INIMIGO) ? 15.0f : 8.0f;

    switch (tipo) {
        case ENTIDADE_JOGADOR:
            e->vida = 100;
            e->cor = BLUE;
            break;
        case ENTIDADE_INIMIGO:
            e->vida = 40;
            e->cor = MAROON;
            e->extra.dano = GetRandomValue(5, 15);
            break;
        case ENTIDADE_ITEM:
            e->vida = 1;
            e->cor = GOLD;
            e->extra.valor = GetRandomValue(5, 20);
            break;
    }
    return e;
}

void adicionarEntidade(TipoEntidade tipo, Vector2 pos) {
    if (totalEntidades < MAX_ENTIDADES) {
        Entidade *nova = criarEntidade(tipo, pos);
        if (nova != NULL) {
            vetorEntidades[totalEntidades] = nova;
            totalEntidades++;
        }
    }
}

void liberarTudo() {
    for (int i = 0; i < totalEntidades; i++) {
        free(vetorEntidades[i]);
        vetorEntidades[i] = NULL;
    }
    totalEntidades = 0;
}

int main() {
    InitWindow(800, 450, "Atividade 5 - Exercicio 2");
    SetTargetFPS(60);

    adicionarEntidade(ENTIDADE_JOGADOR, (Vector2){400, 225});

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_N)) {
            Vector2 posAleatoria = { (float)GetRandomValue(50, 750), (float)GetRandomValue(50, 400) };
            adicionarEntidade(ENTIDADE_ITEM, posAleatoria);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("[N] Criar novo item em posicao aleatoria", 20, 20, 18, DARKGRAY);
            DrawText(TextFormat("Total de Entidades: %d/%d", totalEntidades, MAX_ENTIDADES), 20, 45, 16, BLUE);

            for (int i = 0; i < totalEntidades; i++) {
                DrawCircleV(vetorEntidades[i]->pos, vetorEntidades[i]->raio, vetorEntidades[i]->cor);
            }
        EndDrawing();
    }

    liberarTudo();
    CloseWindow();
    return 0;
}
