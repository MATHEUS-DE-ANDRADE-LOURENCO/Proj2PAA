//Felipe Ujvari Gasparino de Sousa - 10418415
//Matheus Lourenço - 10419691
//Pedro Souza Zequi - 10419805

# ifndef funcoes
# define funcoes

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

# define TAM 100

int len(char texto[], int tam);

void inicializarVariaveis(int ***matriz, int *qtdEsquinas, int *localIncendio, char nomeArquivo[]);

int esquinaComMenorCusto(int *T, int *E, int qtdEsquinas);

void realizaAlgoritmoCerto(int **matriz, int qtdEsquinas, int localIncendio);

int vetorEstaVazio(int *v, int tam);

void imprimeVetor(int *v, int n);

void imprimirRota(int *R, int destino);

void imprimirTabela(int **matriz, int qtdEsquinas);

# endif
