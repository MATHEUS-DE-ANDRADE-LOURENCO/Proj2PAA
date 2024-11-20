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


/*
Iniciei a implementação desse algoritmo, mas não está funcionando. Estou tendo problemas na remoção do elemento do vetor.
Como cada vez que a função de encontrar a esquina com o maior custo vai pegar o menor valor do vetor de custos, toda a hora
ela irá pegar o mesmo valor.

Possível solução: Salvar o menor custo da esquina em uma variável (não apenas qual é essa esquina) e deixar outro valor no vetor de custos, 
acho que INT_MAX pode funcionar.
*/
void realizarAlgoritmoErrado(int ***matriz, int *esquinas, int qtdEsquinas, int localIncendio) {
    int vetoresTempo[TAM];
    
    // Preenche o vetor de tempos com infinito.  
    for(int i = 1; i <= qtdEsquinas; i++) vetoresTempo[i] = INT_MAX;

    printf("\n");

    // Atribui 0 ao primeiro elemento do vetor (custo da esquina 1 para a esquina 1)
    vetoresTempo[1] = 0;

    // Enquanto o vetor de esquinas não estiver vazio
    while(!vetorEstaVazio(esquinas, qtdEsquinas)) {
        imprimeVetor(esquinas, qtdEsquinas);
        printf("\n");
        // Pega a esquina com o menor custo
        int esquinaMenorCusto = esquinaComMenorCusto(vetoresTempo, esquinas, qtdEsquinas);

        // Remove essa esquina do vetor
        esquinas[esquinaMenorCusto] = INT_MAX;

        // Pra cada coluna que for possível se acessar através da esquina de menor custo
        for(int col = 1; col <= qtdEsquinas; col++) {
            // Se a coluna for diferente de 0 (for possível acessar a esquina pela esquina de menor custo)
            if ((*matriz)[esquinaMenorCusto][col] != 0) {
                if(vetoresTempo[col] > vetoresTempo[esquinaMenorCusto] + (*matriz)[esquinaMenorCusto][col]) {
                    vetoresTempo[col] = vetoresTempo[esquinaMenorCusto] + (*matriz)[esquinaMenorCusto][col];
                }
            }
        }
        

    }

    for(int j = 1; j <= qtdEsquinas; j++) {
        if(esquinas[j] != 0) printf("%d -> ", esquinas[j]);
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
    int esquinaMenorCusto;
    int custoEsquinaMenorCusto = INT_MAX;
    for(int i = 1; i <= qtdEsquinas; i++) {
       if(vetoresTempo[i] < custoEsquinaMenorCusto) {
            custoEsquinaMenorCusto = vetoresTempo[i];
            esquinaMenorCusto = esquinas[i];
       }
    }

    return esquinaMenorCusto;
}

void imprimeVetor(int *v, int n) {
    for(int i = 1; i <= n; i++) {
        printf("%d ", v[i]);
    }
}