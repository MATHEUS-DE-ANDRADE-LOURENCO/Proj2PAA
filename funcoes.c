#include "funcoes.h"

int len(char texto[], int tam) {
    int count = 0;
    while (texto[count] != '\0') count++;
    return count;
}

void inicializarVariaveis(int ***matriz, int *maior, int *esquinas, int *tempo, int *qtdEsquinas, int *localIncendio, char nomeArquivo[]) {
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
    *maior = -1;  // Inicializa o maior

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

        if (*maior == -1 || linha > *maior) *maior = linha;
        if (coluna > *maior) *maior = coluna;

        (*matriz)[linha][coluna] = custo;
    }

    fclose(arq);
}

void imprimirMatriz(int **matriz, int maior) {
    printf("\nMatriz de custos:\n");
    for (int i = 1; i <= maior; i++) {  // Índices de 1 a maior
        for (int j = 1; j <= maior; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}
