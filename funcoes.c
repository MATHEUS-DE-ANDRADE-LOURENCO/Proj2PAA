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
    int menor;
    int tempoMenor = INT_MAX;
    for(int i = 0; i < qtdEsquinas; i++){
        if(T[i] < tempoMenor && E[i] != -1) {
            // Se o tempo da esquina atual for menor e ainda não foi removida
            menor = i; 
            tempoMenor = T[i];
        }
    }

    return menor;
}

void realizaAlgoritmoCerto(int **matriz, int qtdEsquinas, int localIncendio) {
    int *E = (int*) calloc(qtdEsquinas, sizeof(int));

    for(int i = 0; i < qtdEsquinas; i++) {
        E[i] = i;
    }

    int *T = (int*) calloc(qtdEsquinas, sizeof(int));
    for (int i = 0; i < qtdEsquinas; i++) {
        T[i] = INT_MAX;
    }

    int *R = (int*) calloc(qtdEsquinas, sizeof(int));
    for (int i = 0; i < qtdEsquinas; i++) {
        R[i] = -1;
    }

    T[0] = 0;

    while (!vetorEstaVazio(E, qtdEsquinas)) {
        int v = esquinaComMenorCusto(T, E, qtdEsquinas);
        E[v] = -1;
        for (int e = 0; e < qtdEsquinas; e++) {
            if ((matriz)[v][e] != INT_MAX && T[e] > T[v] + (matriz)[v][e]) {
                T[e] = T[v] + (matriz)[v][e];
                R[e] = v;
            }
        }
    }

    printf("\n\nEsquinas: ");
    imprimeVetor(E, qtdEsquinas);
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
    int caminho[100]; // Vetor auxiliar para armazenar a rota
    int indice = 0;

    // Percorre os predecessores até chegar ao início (-1)
    while (destino != -1) {
        caminho[indice++] = destino + 1; // Adiciona ao caminho ajustando o índice
        destino = R[destino];           // Vai para o predecessor
    }

    // Imprime a rota em ordem inversa
    for (int i = indice - 1; i >= 0; i--) {
        printf("%d ", caminho[i]);
    }
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
