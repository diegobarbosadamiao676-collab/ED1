#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
FILE *in = fopen("entrada_q3.txt", "r");
FILE *out = fopen("saida_q3.txt", "w");
if (in == NULL || out == NULL) {
printf("Erro ao abrir os arquivos!\n");
return 1;
}
char linha[256];
while (fgets(linha, sizeof(linha), in)) {
linha[strcspn(linha, "\r\n")] = 0;
if (strlen(linha) == 0) continue;
char nome[100];
float notas[10];
int num_notas = 0;
char *token = strtok(linha, "\t");
if (token != NULL) {
strcpy(nome, token);
while ((token = strtok(NULL, "\t")) != NULL) {
notas[num_notas++] = atof(token);
}
}
if (num_notas > 0) {
float soma = 0;
for (int i = 0; i < num_notas; i++) {
soma += notas[i];
}
float media = soma / num_notas;
char *situacao = (media >= 7.0) ? "aprovado" : "reprovado";
fprintf(out, "%s\t%.1f\t%s\n", nome, media, situacao);
}
}
fclose(in);
fclose(out);
printf("Ficheiro 'saida_q3.txt' gerado com sucesso.\n");
return 0;
}
