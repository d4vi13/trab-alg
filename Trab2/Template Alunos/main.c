#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h"

int main() {
    char nome[MAX_CHAR];
    char nomeAlg[MAX_CHAR];
    int numComp;

    int tamVetor = 3;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    vetor[0] = 1;
    vetor[1] = 10;
    vetor[2] = 12;

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    numComp = mergeSort(vetor, 3);
    numComp = quickSort(vetor, 3);
    numComp = heapSort(vetor, 3);

    getNomeAlgoritmoExtra(nomeAlg);
    printf("Executando %s\n", nomeAlg);
    numComp = algoritmoExtra(vetor, 3);

    printf("NumComp: %d\n", numComp);

    unsigned int vetorUnsigned[3] = {5, 4, 3};
    countingSort(vetorUnsigned, 3, 12);

    for (int i = 0; i < 3; ++i) printf("%d ", vetor[i]);

    printf("\n");

    for (int i = 0; i < 3; ++i) printf("%d ", vetorUnsigned[i]);

    printf("\n");

    free(vetor);

    return 0;
}
