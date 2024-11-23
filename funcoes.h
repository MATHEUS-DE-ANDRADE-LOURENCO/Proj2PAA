# ifndef funcoes
# define funcoes

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

# define TAM 100

int len(char texto[], int tam);

void inicializarVariaveis(int ***matriz, int *qtdEsquinas, int *localIncendio, char nomeArquivo[]);

void imprimirMatriz(int **matriz, int qtdEsquinas);

int esquinaComMenorCusto(int *T, int *E, int qtdEsquinas);

void realizaAlgoritmoErrado(int ***matriz, int qtdEsquinas, int localIncendio);

void realizarAlgoritmoCerto(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio);

int vetorEstaVazio(int *v, int tam);

void imprimeVetor(int *v, int n);

# endif