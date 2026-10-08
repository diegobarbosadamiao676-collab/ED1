# Insertion Sort

O projeto implementa o algoritmo **Insertion Sort** em linguagem C, utilizando a biblioteca **Raylib** para criar uma interface gráfica e demonstrar o funcionamento do algoritmo passo a passo.

## Integrantes

- Diego Barbosa Damião 
- gabriel pinheiro da silva

## Sobre o projeto

O programa permite visualizar o funcionamento do Insertion Sort através de barras que representam os elementos do vetor.

Durante a execução, é possível acompanhar:

- Comparações;
- Movimentações;
- Passos;
- Posição atual;
- Valor da chave;
- Estado da execução.

### Cores

- **Azul:** elemento normal;
- **Vermelho:** chave;
- **Laranja:** elemento sendo movimentado.

## Controles

| Tecla | Função |
|---|---|
| `SPACE` | Iniciar/continuar |
| `P` | Pausar |
| `N` | Próximo passo |
| `R` | Reiniciar |
| `E` | Executar experimentos |

## Insertion Sort

O Insertion Sort percorre o vetor da esquerda para a direita.

A cada posição, um elemento é escolhido como chave. Os elementos anteriores que são maiores que a chave são deslocados para a direita. Depois disso, a chave é colocada na posição correta.

Esse processo continua até que todos os elementos estejam ordenados.

## Complexidade

- **Melhor caso:** `O(n)`
- **Caso médio:** `O(n²)`
- **Pior caso:** `O(n²)`
- **Espaço:** `O(1)`

## Experimentos

O programa realiza experimentos utilizando diferentes tamanhos de vetores:

- 10 elementos;
- 100 elementos;
- 500 elementos;
- 1000 elementos;
- 5000 elementos;
- 10000 elementos.

São utilizados quatro tipos de entrada:

- Aleatório;
- Ordenado;
- Inversamente ordenado;
- Valores repetidos.

Durante os experimentos são registrados:

- Comparações;
- Movimentações;
- Tempo de execução.

Os resultados são armazenados no arquivo:

    resultados_4_tipos.txt

## Compilação e execução

### Compilação

Para compilar o programa, utilize:

    gcc trabalhosegundaunidade.c -o trabalhosegundaunidade.exe $(pkg-config --cflags --libs raylib)

### Execução

Depois de compilar, execute o programa com:

    ./trabalhosegundaunidade.exe

## Arquivos principais

    trabalhosegundaunidade.c
    dados.txt
    resultados_4_tipos.txt
    README.md

## Objetivo

O objetivo do projeto é implementar o algoritmo **Insertion Sort**, apresentar seu funcionamento de forma visual e analisar seu desempenho através de experimentos com diferentes tamanhos e tipos de entrada.
