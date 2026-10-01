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

void ordenarBubbleSort(Placar *vetor, int n, long *comparacoes, long *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (vetor[j].pontuacao > vetor[j + 1].pontuacao) {
                Placar temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Exercicio 2 - Medindo Tempo Real");

    int n = 100;
    Placar *placares = criarPlacares(n);

    long comparacoes = 0;
    long trocas = 0;
    double tempo_decorrido_ms = 0.0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_B)) {
            double inicio = GetTime();

            ordenarBubbleSort(placares, n, &comparacoes, &trocas);

            double fim = GetTime();

            tempo_decorrido_ms = (fim - inicio) * 1000.0;
        }

        if (IsKeyPressed(KEY_R)) {
            free(placares);
            placares = criarPlacares(n);
            comparacoes = 0;
            trocas = 0;
            tempo_decorrido_ms = 0.0;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            int larguraBarra = larguraTela / n;
            for (int i = 0; i < n; i++) {
                int alturaBarra = (placares[i].pontuacao * (alturaTela - 150)) / PONTUACAO_MAX;
                DrawRectangle(i * larguraBarra, alturaTela - alturaBarra, larguraBarra - 1, alturaBarra, BLUE);
            }

            DrawRectangle(10, 10, 350, 100, Fade(LIGHTGRAY, 0.8f));
            DrawRectangleLines(10, 10, 350, 100, GRAY);
            
            DrawText(TextFormat("Comparacoes: %ld", comparacoes), 20, 20, 20, DARKGRAY);
            DrawText(TextFormat("Trocas: %ld", trocas), 20, 45, 20, DARKGRAY);
            DrawText(TextFormat("Tempo: %.4f ms", tempo_decorrido_ms), 20, 70, 20, MAROON);

            DrawText("Pressione [B] para executar Bubble Sort | [R] para reiniciar", 10, alturaTela - 25, 16, DARKGRAY);
        EndDrawing();
    }

    free(placares);
    CloseWindow();
    return 0;
}
