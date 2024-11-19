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

void realizarAlgoritmoErrado(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio);

void realizarAlgoritmoCerto(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio);

int vetorEstaVazio(int *v, int tam);

int esquinaComMenorCusto(int *vetoresTempo, int *esquinas, int qtdEsquinas);

# endif