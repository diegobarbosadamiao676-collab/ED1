#include <stdio.h>
#include <stdlib.h>
int main() {
FILE *arquivo = fopen("funcionarios.txt", "w");
if (arquivo == NULL) {
printf("Erro ao abrir o arquivo!\n");
return 1;
}
int id;
char nome[100];
float salario;
char continuar;
do {
printf("ID do funcionario: ");
scanf("%d", &id);
printf("Nome do funcionario: ");
scanf(" %[^\n]", nome);
printf("Salario do funcionario: ");
scanf("%f", &salario);
fprintf(arquivo, "%d %s %.2f\n", id, nome, salario);
 printf("Deseja cadastrar outro funcionario? (s/n): ");
scanf(" %c", &continuar);
 } while (continuar == 's' || continuar == 'S');
fclose(arquivo);
 printf("Dados guardados em 'funcionarios.txt' com sucesso.\n");
  return 0;
}
