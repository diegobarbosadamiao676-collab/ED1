#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>
#define MAX_ELEMENTOS 50
#define TAM_NOME 20
  typedef enum {
   PARADO,
  EXECUTANDO,
  PAUSADO,
   FINALIZADO
  } Estado;
   typedef struct {
   int valor;
   int estado;
  } Elemento;
typedef union {
int valor;
char nome[TAM_NOME];
} DadoExtra;
Elemento *vetor = NULL;
int quantidade = 0;
int indiceAtual = 1;
int indiceComparacao = 0;
int chave = 0;
long comparacoes = 0;
long movimentacoes = 0;
long passos = 0;
Estado estado = PARADO;
float tempoPasso = 0.0f;
float intervalo = 0.5f;
void criarArquivoExemplo() {
FILE *arquivo = fopen("dados.txt", "w");
if (arquivo == NULL) {
printf("Erro ao criar dados.txt!\n");
return;
}
int dados[] = {
45, 12, 78, 23, 9,
56, 34, 87, 15, 3,
62, 41, 29, 95, 7,
18, 73, 50, 31, 66,
22, 84, 11, 39, 5,
71, 27, 90, 14, 48
};
int total = sizeof(dados) / sizeof(dados[0]);
for (int i = 0; i < total; i++) {
fprintf(arquivo, "%d\n", dados[i]);
}
fclose(arquivo);
}
int carregarArquivo(const char *nomeArquivo) {
FILE *arquivo = fopen(nomeArquivo, "r");
if (arquivo == NULL) {
printf("Arquivo nao encontrado.\n");
return 0;
}
vetor = malloc(MAX_ELEMENTOS * sizeof(Elemento));
if (vetor == NULL) {
printf("Erro de memoria!\n");
fclose(arquivo);
return 0;
}
quantidade = 0;
while (
quantidade < MAX_ELEMENTOS &&
fscanf(arquivo, "%d", &vetor[quantidade].valor) == 1
) {
vetor[quantidade].estado = 0;
quantidade++;
}
fclose(arquivo);
return quantidade;
}
void reiniciar() {
for (int i = 0; i < quantidade; i++) {
vetor[i].estado = 0;
}
indiceAtual = 1;
indiceComparacao = 0;
chave = 0;
comparacoes = 0;
movimentacoes = 0;
passos = 0;
estado = PARADO;
}
void proximoPasso() {
if (indiceAtual >= quantidade) {
estado = FINALIZADO;
return;
}
if (indiceComparacao == 0) {
chave = vetor[indiceAtual].valor;
indiceComparacao = indiceAtual - 1;
vetor[indiceAtual].estado = 2;
passos++;
return;
}
comparacoes++;
passos++;
if (
indiceComparacao >= 0 &&
vetor[indiceComparacao].valor > chave
) {
vetor[indiceComparacao + 1].valor =
vetor[indiceComparacao].valor;
vetor[indiceComparacao + 1].estado = 1;
movimentacoes++;
indiceComparacao--;
} else {
vetor[indiceComparacao + 1].valor = chave;
vetor[indiceComparacao + 1].estado = 0;
indiceAtual++;
indiceComparacao = 0;
}
}
void desenharBarras() {
int larguraJanela = GetScreenWidth();
int alturaJanela = GetScreenHeight();
int areaTopo = 170;
int areaInferior = 60;
int alturaDisponivel =
alturaJanela - areaTopo - areaInferior;
int larguraBarra =
(larguraJanela - 40) / quantidade;
if (larguraBarra < 5)
larguraBarra = 5;
int maior = 1;
for (int i = 0; i < quantidade; i++) {
if (vetor[i].valor > maior) {
maior = vetor[i].valor;
}
}
for (int i = 0; i < quantidade; i++) {
float proporcao =
(float)vetor[i].valor / maior;
int altura =
proporcao * alturaDisponivel;
int x =
20 + i * larguraBarra;
int y =
alturaJanela - areaInferior - altura;
Color cor = BLUE;
if (vetor[i].estado == 1) {
cor = ORANGE;
}
if (vetor[i].estado == 2) {
cor = RED;
}
DrawRectangle(
x,
y,
larguraBarra - 2,
altura,
cor
);
if (larguraBarra >= 20) {
char texto[10];
sprintf(
texto,
"%d",
vetor[i].valor
);
DrawText(
texto,
x + 2,
y - 20,
14,
BLACK
);
}
}
}
void desenharInterface() {
DrawText(
"INSERTION SORT",
20,
15,
30,
DARKBLUE
);
char texto[100];
sprintf(
texto,
"Elementos: %d",
quantidade
);
DrawText(
texto,
20,
55,
20,
BLACK
);
sprintf(
texto,
"Comparacoes: %ld",
comparacoes
);
DrawText(
texto,
200,
55,
20,
BLACK
);
sprintf(
texto,
"Movimentacoes: %ld",
movimentacoes
);
DrawText(
texto,
430,
55,
20,
BLACK
);
sprintf(
texto,
"Passo: %ld",
passos
);
DrawText(
texto,
700,
55,
20,
BLACK
);
const char *nomeEstado;
switch (estado) {
case PARADO:
nomeEstado = "PARADO";
break;
case EXECUTANDO:
nomeEstado = "EXECUTANDO";
break;
case PAUSADO:
nomeEstado = "PAUSADO";
break;
case FINALIZADO:
nomeEstado = "FINALIZADO";
break;
default:
nomeEstado = "";
}
sprintf(
texto,
"Estado: %s",
nomeEstado
);
DrawText(
texto,
20,
90,
20,
DARKGRAY
);
if (
indiceAtual < quantidade &&
estado != FINALIZADO
) {
sprintf(
texto,
"Posicao atual: %d    Chave: %d",
indiceAtual,
chave
);
DrawText(
texto,
250,
90,
20,
DARKGRAY
);
}
DrawRectangle(
20,
GetScreenHeight() - 45,
20,
20,
BLUE
);
DrawText(
"Normal",
45,
GetScreenHeight() - 45,
18,
BLACK
);
DrawRectangle(
130,
GetScreenHeight() - 45,
20,
20,
RED
);
DrawText(
"Chave",
155,
GetScreenHeight() - 45,
18,
BLACK
);
DrawRectangle(
240,
GetScreenHeight() - 45,
20,
20,
ORANGE
);
DrawText(
"Movimentando",
265,
GetScreenHeight() - 45,
18,
BLACK
);
DrawText(
"SPACE: iniciar/continuar | P: pausar | N: proximo passo | R: reiniciar | E: experimentos",
20,
GetScreenHeight() - 22,
16,
DARKGRAY
);
}
void gerarArquivoExperimento(const char *nomeArquivo, int quantidadeDados, int tipo) {
FILE *arquivo = fopen(nomeArquivo, "w");
if (arquivo == NULL) {
printf("Erro ao criar %s!\n", nomeArquivo);
return;
}
for (int i = 0; i < quantidadeDados; i++) {
int valor;
if (tipo == 0) {
valor = 1 + rand() % quantidadeDados;
}
else if (tipo == 1) {
valor = i + 1;
}
else if (tipo == 2) {
valor = quantidadeDados - i;
}
else {
valor = (i % 20) + 1;
}
fprintf(arquivo, "%d\n", valor);
}
fclose(arquivo);
}
int carregarDadosExperimento(const char *nomeArquivo, int **vetorDados, int quantidadeDados) {
FILE *arquivo = fopen(nomeArquivo, "r");
if (arquivo == NULL) {
printf("Erro ao abrir %s!\n", nomeArquivo);
return 0;
}
*vetorDados = malloc(quantidadeDados * sizeof(int));
if (*vetorDados == NULL) {
printf("Erro de memoria!\n");
fclose(arquivo);
return 0;
}
for (int i = 0; i < quantidadeDados; i++) {
if (fscanf(arquivo, "%d", &(*vetorDados)[i]) != 1) {
free(*vetorDados);
*vetorDados = NULL;
fclose(arquivo);
return 0;
}
}
fclose(arquivo);
return 1;
}
void executarInsertionSortExperimento(
int *vetorDados,
int quantidadeDados,
long *comparacoesExperimento,
long *movimentacoesExperimento
) {
*comparacoesExperimento = 0;
*movimentacoesExperimento = 0;
for (int i = 1; i < quantidadeDados; i++) {
int chaveExperimento = vetorDados[i];
int j = i - 1;
while (j >= 0) {
(*comparacoesExperimento)++;
if (vetorDados[j] > chaveExperimento) {
vetorDados[j + 1] = vetorDados[j];
(*movimentacoesExperimento)++;
j--;
}
else {
break;
}
}
vetorDados[j + 1] = chaveExperimento;
(*movimentacoesExperimento)++;
}
}
void executarExperimentos() {
const int tamanhos[] = {10, 100, 500, 1000, 5000, 10000};
const int totalTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
const char *nomesTipos[] = {
"Aleatorio",
"Ordenado",
"Inversamente ordenado",
"Valores repetidos"
};
FILE *resultados = fopen("resultados_4_tipos.txt", "w");
if (resultados == NULL) {
printf("Erro ao criar resultados_4_tipos.txt!\n");
return;
}
fprintf(
resultados,
"Tipo;Elementos;Comparacoes;Movimentacoes;Tempo (ms)\n"
);
srand(2026);
for (int tipo = 0; tipo < 4; tipo++) {
for (int t = 0; t < totalTamanhos; t++) {
int quantidadeDados = tamanhos[t];
char nomeArquivo[100];
sprintf(
nomeArquivo,
"dados_%d_%d.txt",
tipo,
quantidadeDados
);
gerarArquivoExperimento(
nomeArquivo,
quantidadeDados,
tipo
);
int *vetorExperimento = NULL;
if (!carregarDadosExperimento(
nomeArquivo,
&vetorExperimento,
quantidadeDados
)) {
continue;
}
long comparacoesExperimento;
long movimentacoesExperimento;
clock_t inicio = clock();
executarInsertionSortExperimento(
vetorExperimento,
quantidadeDados,
&comparacoesExperimento,
&movimentacoesExperimento
);
clock_t fim = clock();
double tempoMs =
((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
fprintf(
resultados,
"%s;%d;%ld;%ld;%.3f\n",
nomesTipos[tipo],
quantidadeDados,
comparacoesExperimento,
movimentacoesExperimento,
tempoMs
);
printf(
"%-24s | %5d | Comparacoes: %10ld | Movimentacoes: %10ld | Tempo: %8.3f ms\n",
nomesTipos[tipo],
quantidadeDados,
comparacoesExperimento,
movimentacoesExperimento,
tempoMs
);
free(vetorExperimento);
}
}
fclose(resultados);
printf("\nExperimentos finalizados!\n");
printf("Resultados salvos em: resultados_4_tipos.txt\n");
printf("Os arquivos de entrada tambem foram criados.\n");
}
int main() {
FILE *teste = fopen("dados.txt", "r");
if (teste == NULL) {
criarArquivoExemplo();
} else {
fclose(teste);
}
if (carregarArquivo("dados.txt") == 0) {
printf("Nao foi possivel carregar os dados.\n");
return 1;
}
InitWindow(
1000,
650,
"Trabalho ED1 - Insertion Sort"
);
SetTargetFPS(60);
while (!WindowShouldClose()) {
if (IsKeyPressed(KEY_E)) {
executarExperimentos();
}
if (IsKeyPressed(KEY_SPACE)) {
if (estado == PARADO ||
estado == PAUSADO) {
estado = EXECUTANDO;
}
}
if (IsKeyPressed(KEY_P)) {
if (estado == EXECUTANDO) {
estado = PAUSADO;
}
}
if (IsKeyPressed(KEY_R)) {
reiniciar();
}
if (IsKeyPressed(KEY_N)) {
if (
estado == PARADO ||
estado == PAUSADO
) {
proximoPasso();
}
}
if (estado == EXECUTANDO) {
tempoPasso += GetFrameTime();
if (tempoPasso >= intervalo) {
proximoPasso();
tempoPasso = 0.0f;
}
}
BeginDrawing();
ClearBackground(RAYWHITE);
desenharInterface();
desenharBarras();
EndDrawing();
}
free(vetor);
CloseWindow();
return 0;
}
