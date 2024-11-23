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

    for(int i = 0; i < *qtdEsquinas; i++) {
        for(int j = 0; j < *qtdEsquinas; j++) {
            (*matriz)[i][j] = INT_MAX;
        }
    }

    // Lê as conexões e atualiza a matriz
    while (fgets(texto, TAM, arq) != NULL) {
        if (len(texto, TAM) < 5) continue; // Ignorar linhas inválidas ou vazias

        int linha = texto[0] - '0';
        int coluna = texto[2] - '0';
        int custo = texto[4] - '0';

        (*matriz)[linha - 1][coluna - 1] = custo;
    }
    
    fclose(arq);
}

void imprimirMatriz(int **matriz, int qtdEsquinas) {
    printf("\nMatriz de custos:\n");
    for (int i = 0; i < qtdEsquinas; i++) { 
        for (int j = 0; j < qtdEsquinas; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

int esquinaComMenorCusto(int *T, int *E, int qtdEsquinas) {
    int menor;
    int tempoMenor = INT_MAX;
    for(int i = 0; i < qtdEsquinas; i++){
        if(T[i] < tempoMenor && E[i] != -1) {
            // Se o tempo da esquina atual for menor e ainda não foi removida
            menor = E[i]; 
            tempoMenor = T[i];
        }
    }

    return menor;
}

void realizaAlgoritmoErrado(int ***matriz, int qtdEsquinas, int localIncendio) {
    // Estrutura auxiliar E que tem as esquinas da matriz
    int *E = (int*) calloc(qtdEsquinas, sizeof(int));
    for(int i = 0; i < qtdEsquinas; i++) {
        E[i] = i;
    }

    // Estrutura para armazenar o tempo em cada esquina.
    int *T = (int*) calloc(qtdEsquinas, sizeof(int));
    // Para cada esquina e em E
    for(int e = 0; e < qtdEsquinas; e++) {
        T[E[e]] = INT_MAX;
    }

    int *P = (int*) calloc(qtdEsquinas, sizeof(int));

    T[0] = 0; // Tempo para ir da primeira esquina para a primeira esquina é zero

    while(!vetorEstaVazio(E, qtdEsquinas)) {
        int v = esquinaComMenorCusto(T, E, qtdEsquinas);
        printf("Esquina com menor custo: %d", v);
        // Removendo a solução
        E[v] = -1;
        // Para cada esquina no mapa que pode ser acessada pela esquina v
        for(int e = 0; e < qtdEsquinas; e++) {
            if(T[e] > T[v] + (*matriz)[v][e] && E[e] != -1) {
                T[e] = T[v] + (*matriz)[v][e];
            }
        }
    }

    printf("\n\nEsquinas: ");
    imprimeVetor(E, qtdEsquinas);
    printf("\nTempo: ");
    imprimeVetor(T, qtdEsquinas);

}

void realizarAlgoritmoCerto(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio) {
    printf("\nTO DO");
}

int vetorEstaVazio(int *v, int tam) {
    for(int i = 0; i < tam; i++) 
        if(v[i] != -1) return 0;
    
    return 1;
}

void imprimeVetor(int *v, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
}