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
        exit(EXIT_FAILURE);
    }

    // Aloca espaço para a matriz (considerando índices de 0 a TAM-1)
    *matriz = (int**) malloc(TAM * sizeof(int*));
    for (int i = 0; i < TAM; i++) {
        (*matriz)[i] = (int*) calloc(TAM, sizeof(int));
        for (int j = 0; j < TAM; j++) {
            (*matriz)[i][j] = INT_MAX; // Inicializa com valor máximo
        }
    }

    char texto[TAM];

    // Lê o local do incêndio
    if (fgets(texto, TAM, arq) != NULL) {
        *localIncendio = atoi(texto);
    }

    // Lê a quantidade de esquinas
    if (fgets(texto, TAM, arq) != NULL) {
        *qtdEsquinas = atoi(texto);
    }

    // Lê as conexões e atualiza a matriz
    while (fgets(texto, TAM, arq) != NULL) {
        if (len(texto, TAM) < 5) continue;

        int linha = texto[0] - '0';
        int coluna = texto[2] - '0';
        int custo = texto[4] - '0';

        (*matriz)[linha - 1][coluna - 1] = custo;
    }

    fclose(arq);
}

void imprimirTabela(int **matriz, int qtdEsquinas) {
    printf("\n┌");
    for (int i = 0; i < qtdEsquinas; i++) {
        printf("───────┬");
    }
    printf("───────┐\n");

    printf("│      │");
    for (int i = 0; i < qtdEsquinas; i++) {
        printf("  %3d  │", i + 1);
    }
    printf("\n├");
    for (int i = 0; i < qtdEsquinas; i++) {
        printf("───────┼");
    }
    printf("───────┤\n");

    for (int i = 0; i < qtdEsquinas; i++) {
        printf("│  %3d │", i + 1);
        for (int j = 0; j < qtdEsquinas; j++) {
            if (matriz[i][j] == INT_MAX) {
                printf("   ∞   │");
            } else {
                printf("  %3d  │", matriz[i][j]);
            }
        }
        printf("\n├");
        for (int j = 0; j < qtdEsquinas; j++) {
            printf("───────┼");
        }
        printf("───────┤\n");
    }
    printf("\n");
}

int esquinaComMenorCusto(int *T, int *E, int qtdEsquinas) {
    int menor = -1;
    int tempoMenor = INT_MAX;

    for (int i = 0; i < qtdEsquinas; i++) {
        if (E[i] != -1 && T[i] < tempoMenor) {
            menor = i;
            tempoMenor = T[i];
        }
    }

    return menor;
}

void realizaAlgoritmoCerto(int **matriz, int qtdEsquinas, int localIncendio) {
    int *E = (int*) malloc(qtdEsquinas * sizeof(int));
    int *T = (int*) malloc(qtdEsquinas * sizeof(int));
    int *R = (int*) malloc(qtdEsquinas * sizeof(int));

    for (int i = 0; i < qtdEsquinas; i++) {
        E[i] = i;
        T[i] = INT_MAX;
        R[i] = -1;
    }

    T[localIncendio - 1] = 0;

    while (!vetorEstaVazio(E, qtdEsquinas)) {
        int v = esquinaComMenorCusto(T, E, qtdEsquinas);
        E[v] = -1;

        for (int e = 0; e < qtdEsquinas; e++) {
            if (matriz[v][e] != INT_MAX && T[e] > T[v] + matriz[v][e]) {
                T[e] = T[v] + matriz[v][e];
                R[e] = v;
            }
        }
    }

    printf("\nTempo: ");
    imprimeVetor(T, qtdEsquinas);

    printf("\nRota até a esquina %d: ", localIncendio);
    imprimirRota(R, localIncendio - 1);
    printf("\nTempo calculado para rota = %d min.\n", T[localIncendio - 1]);

    free(E);
    free(T);
    free(R);
}

void imprimirRota(int *R, int destino) {
    int caminho[100];
    int indice = 0;

    while (destino != -1) {
        caminho[indice++] = destino + 1;
        destino = R[destino];
    }

    for (int i = indice - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
}

int vetorEstaVazio(int *v, int tam) {
    for (int i = 0; i < tam; i++) {
        if (v[i] != -1) return 0;
    }
    return 1;
}

void imprimeVetor(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}
