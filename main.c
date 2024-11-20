# include "funcoes.h"

#include "funcoes.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\nEspecifique os arquivos da maneira correta.");
        return -1;
    }

    FILE *arq = fopen(argv[1], "r");
    if (arq == NULL) {
        printf("\nFalha ao abrir o arquivo.");
        return -1;
    }

    // Inicializando os ponteiros corretamente
    int **matriz;
    int tempo = 0;
    int qtdEsquinas = 0;
    int localIncendio = 0;

    // Passando os endereços das variáveis para inicializar corretamente
    inicializarVariaveis(&matriz, &qtdEsquinas, &localIncendio, argv[1]);

    printf("\nQuantidade de esquinas: %d", qtdEsquinas);
    printf("\nLocal do incêndio: %d", localIncendio);
    imprimirMatriz(matriz, qtdEsquinas);

    int *esquinas;
    esquinas = (int*) calloc(qtdEsquinas + 1, sizeof(int));

    for(int i = 1; i <= qtdEsquinas; i++) {
        esquinas[i] = i;
    }

    imprimeVetor(esquinas, qtdEsquinas);

    int vetorTempo[7] = {0, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    realizarAlgoritmoErrado(&matriz, esquinas, qtdEsquinas, localIncendio);


    return 0;
}
