# ifndef funcoes
# define funcoes

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

# define TAM 100

int len(char texto[], int tam);

void inicializarVariaveis(int ***matriz, int *maior, int *esquinas, int *tempo, int *qtdEsquinas, int *localIncendio, char nomeArquivo[]);

void imprimirMatriz(int **matriz, int maior);

# endif