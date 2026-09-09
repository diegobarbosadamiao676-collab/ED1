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

void ordenarPorDistancia() {
    if (totalEntidades <= 2) return;

    Entidade *jogador = vetorEntidades[0];
    int indiceMaisProximo = 1;
    float menorDistancia = Vector2Distance(jogador->pos, vetorEntidades[1]->pos);

    for (int i = 2; i < totalEntidades; i++) {
        float dist = Vector2Distance(jogador->pos, vetorEntidades[i]->pos);
        if (dist < menorDistancia) {
            menorDistancia = dist;
            indiceMaisProximo = i;
        }
    }

    if (indiceMaisProximo != 1) {
        Entidade *tmp = vetorEntidades[1];
        vetorEntidades[1] = vetorEntidades[indiceMaisProximo];
        vetorEntidades[indiceMaisProximo] = tmp;
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
    InitWindow(800, 450, "Atividade 5 - Exercicio 1");
    SetTargetFPS(60);

    vetorEntidades[totalEntidades++] = criarEntidade(ENTIDADE_JOGADOR, (Vector2){400, 225});
    vetorEntidades[totalEntidades++] = criarEntidade(ENTIDADE_INIMIGO, (Vector2){700, 100});
    vetorEntidades[totalEntidades++] = criarEntidade(ENTIDADE_INIMIGO, (Vector2){450, 230});
    vetorEntidades[totalEntidades++] = criarEntidade(ENTIDADE_ITEM, (Vector2){100, 300});

    while (!WindowShouldClose()) {
        ordenarPorDistancia();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Posição [1] e o elemento mais proximo do Jogador [0]", 20, 20, 18, DARKGRAY);

            for (int i = 0; i < totalEntidades; i++) {
                DrawCircleV(vetorEntidades[i]->pos, vetorEntidades[i]->raio, vetorEntidades[i]->cor);
                DrawText(TextFormat("[%d]", i), (int)vetorEntidades[i]->pos.x - 10, (int)vetorEntidades[i]->pos.y - 5, 14, WHITE);
            }
        EndDrawing();
    }

    liberarTudo();
    CloseWindow();
    return 0;
}
