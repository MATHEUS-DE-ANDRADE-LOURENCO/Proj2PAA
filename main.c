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

    realizaAlgoritmoCerto(matriz, qtdEsquinas, localIncendio);

    return 0;
}
