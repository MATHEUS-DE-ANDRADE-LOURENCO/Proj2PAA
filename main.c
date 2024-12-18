//Felipe Ujvari Gasparino de Sousa - 10418415
//Matheus Lourenço - 10419691
//Pedro Souza Zequi - 10419805

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

    imprimirTabela(matriz, qtdEsquinas);

    realizaAlgoritmoCerto(matriz, qtdEsquinas, localIncendio);

    return 0;
}


//ChatGPT nos auxiliou na criação da tabela (em asciiz) na hora do PRINT e na formatação do README.md
