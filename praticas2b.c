#include <stdio.h>
#include <stdlib.h>
int main() {
FILE *in = fopen("entrada_q2.txt", "r");
FILE *out = fopen("saida_q2.txt", "w");
if (in == NULL || out == NULL) {
printf("Erro ao abrir os os arquivos!\n");
return 1;
}
int vetor[10];
int menor, maior;
float soma = 0;
for (int i = 0; i < 10; i++) {
fscanf(in, "%d", &vetor[i]);
soma += vetor[i];
if (i == 0) {
menor = vetor[i];
maior = vetor[i];
} else {
if (vetor[i] < menor) menor = vetor[i];
if (vetor[i] > maior) maior = vetor[i];
}
}
float media = soma / 10.0;
fprintf(out, "menor elemento: %d\n", menor);
fprintf(out, "maior elemento: %d\n", maior);
fprintf(out, "media dos elementos: %f\n", media);
fclose(in);
fclose(out);
printf("Ficheiro 'saida_q2.txt' gerado com sucesso.\n");
return 0;
}
