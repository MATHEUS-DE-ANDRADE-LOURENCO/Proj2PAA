#include "funcoes.h"

int len(char texto[], int tam) {
    int count = 0;
    while (texto[count] != '\0') count++;
    return count;
}

void inicializarVariaveis(int ***matriz, int *qtdEsquinas, int *localIncendio, char nomeArquivo[]) {
    FILE *arq = fopen(nomeArquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Aloca o espaço para a matriz (considerando índices de 1 a TAM)
    *matriz = (int**) malloc((TAM + 1) * sizeof(int*));
    for (int i = 0; i <= TAM; i++) {
        (*matriz)[i] = (int*) calloc((TAM + 1), sizeof(int)); // Usando calloc para inicializar com 0
    }

    char texto[TAM];

    // Lê o local do incêndio
    if (fgets(texto, TAM, arq) != NULL) {
        *localIncendio = texto[0] - '0';
    }

    // Lê a quantidade de esquinas
    if (fgets(texto, TAM, arq) != NULL) {
        *qtdEsquinas = texto[0] - '0';
    }

    // Lê as conexões e atualiza a matriz
    while (fgets(texto, TAM, arq) != NULL) {
        if (len(texto, TAM) < 5) continue; // Ignorar linhas inválidas ou vazias

        int linha = texto[0] - '0';
        int coluna = texto[2] - '0';
        int custo = texto[4] - '0';

        (*matriz)[linha][coluna] = custo;
    }

    fclose(arq);
}

void imprimirMatriz(int **matriz, int qtdEsquinas) {
    printf("\nMatriz de custos:\n");
    for (int i = 1; i <= qtdEsquinas; i++) {  // Índices de 1 a maior
        for (int j = 1; j <= qtdEsquinas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void realizarAlgoritmoErrado(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio) {
    int vetoresTempo[TAM];
    for(int i = 1; i <= qtdEsquinas; i++) {
        vetoresTempo[i] = INT_MAX;
    }

    vetoresTempo[1] = 0;

    while(!vetorEstaVazio(esquinas, qtdEsquinas)) {
        int esquinaMenorCusto = esquinaComMenorCusto(vetoresTempo, esquinas, qtdEsquinas);
        

    }   


}

void realizarAlgoritmoCerto(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio) {
    printf("\nTO DO");
}

int vetorEstaVazio(int *v, int tam) {
    for(int i = 1; i <= tam; i++) 
        if(v[i] != 0) return 0;
    
    return 1;
}

int esquinaComMenorCusto(int *vetoresTempo, int *esquinas, int qtdEsquinas) {
    int esquinaMenorCusto = 0;
    int custoEsquinaMenorCusto = 0;
    for(int i = 1; i <= qtdEsquinas; i++) {
       if(vetoresTempo[i] < custoEsquinaMenorCusto || esquinaMenorCusto == 0) {
            custoEsquinaMenorCusto = vetoresTempo[i];
            esquinaMenorCusto = esquinas[i];
       }
    }

    return esquinaMenorCusto;
}