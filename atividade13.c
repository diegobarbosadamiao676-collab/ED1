#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define PONTUACAO_MAX 1000

typedef struct {
    char nome[16];
    int pontuacao;
} Placar;

Placar *criarPlacares(int quantidade) {
    Placar *placares = (Placar *)malloc(quantidade * sizeof(Placar));
    for (int i = 0; i < quantidade; i++) {
        Placar *p = (placares + i);
        TextCopy(p->nome, TextFormat("P%02d", i + 1));
        p->pontuacao = GetRandomValue(10, PONTUACAO_MAX);
    }
    return placares;
}

void ordenarInsertionSort(Placar *vetor, int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 1; i < n; i++) {
        Placar chave = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            if (vetor[j].pontuacao > chave.pontuacao) {
                vetor[j + 1] = vetor[j];
                (*trocas)++;
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Exercicio 1 - Insertion Sort");

    int n = 50;
    Placar *placares = criarPlacares(n);

    long comparacoes = 0;
    long trocas = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_I)) {
            ordenarInsertionSort(placares, n, &comparacoes, &trocas);
        }

        if (IsKeyPressed(KEY_R)) {
            free(placares);
            placares = criarPlacares(n);
            comparacoes = 0;
            trocas = 0;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            int larguraBarra = larguraTela / n;
            for (int i = 0; i < n; i++) {
                int alturaBarra = (placares[i].pontuacao * (alturaTela - 150)) / PONTUACAO_MAX;
                DrawRectangle(i * larguraBarra, alturaTela - alturaBarra, larguraBarra - 1, alturaBarra, BLUE);
            }

            DrawRectangle(10, 10, 300, 80, Fade(LIGHTGRAY, 0.8f));
            DrawRectangleLines(10, 10, 300, 80, GRAY);
            DrawText(TextFormat("Comparacoes: %ld", comparacoes), 20, 25, 20, DARKGRAY);
            DrawText(TextFormat("Trocas/Deslocs: %ld", trocas), 20, 55, 20, DARKGRAY);

            DrawText("Pressione [I] para ordenar com Insertion Sort | [R] para reiniciar", 10, alturaTela - 25, 16, DARKGRAY);
        EndDrawing();
    }

    free(placares);
    CloseWindow();
    return 0;
}
