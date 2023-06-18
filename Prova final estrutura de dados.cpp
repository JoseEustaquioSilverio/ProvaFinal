#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *vetor; // Ponteiro para o vetor de inteiros
int tamanho; // Variável para armazenar o tamanho do vetor

void gerarVetor() {
    int numero;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &numero);

    tamanho = numero;
    vetor = (int *)malloc(tamanho * sizeof(int)); // Aloca memória para o vetor com base no tamanho informado

    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 1000; // Gera números aleatórios entre 0 e 999
    }

    printf("Vetor gerado com sucesso!\n");
}

void exibirVetor() {
    printf("Vetor: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void insertionSort() {
    for (int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;
        
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        
        vetor[j + 1] = chave;
    }

    printf("Vetor ordenado por Insertion Sort.\n");
    exibirVetor();
}

void merge(int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *esquerda = (int *)malloc(n1 * sizeof(int));
    int *direita = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        esquerda[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++)
        direita[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (esquerda[i] <= direita[j]) {
            vetor[k] = esquerda[i];
            i++;
        } else {
            vetor[k] = direita[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = direita[j];
        j++;
        k++;
    }

    free(esquerda);
    free(direita);
}

void mergeSort(int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(inicio, meio);
        mergeSort(meio + 1, fim);
        merge(inicio, meio, fim);
    }
}

void ordenarVetor() {
    if (vetor == NULL) {
        printf("Erro: Vetor nao foi gerado.\n");
        return;
    }

    char opcao;
    printf("Digite a opcao de ordenacao (I - Insertion Sort, M - Merge Sort): ");
    scanf(" %c", &opcao);

    switch (opcao) {
        case 'I':
        case 'i':
            insertionSort();
            break;
        case 'M':
        case 'm':
            mergeSort(0, tamanho - 1);
            printf("Vetor ordenado por Merge Sort.\n");
            exibirVetor();
            break;
        default:
            printf("Opcao invalida.\n");
            break;
    }
}

void buscaSequencial() {
    if (vetor == NULL) {
        printf("Erro: Vetor nao foi gerado.\n");
        return;
    }

    int numero;
    printf("Digite o numero a ser buscado: ");
    scanf("%d", &numero);

    int posicao = -1;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == numero) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
        printf("O nnumero %d foi encontrado na posicao %d do vetor.\n", numero, posicao);
    } else {
        printf("O numero %d nao foi encontrado no vetor.\n", numero);
    }
}

void buscaBinaria() {
    if (vetor == NULL) {
        printf("Erro: vetor nao foi gerado.\n");
        return;
    }

    int numero;
    printf("Digite o numero a ser buscado: ");
    scanf("%d", &numero);

    int inicio = 0;
    int fim = tamanho - 1;
    int posicao = -1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (vetor[meio] == numero) {
            posicao = meio;
            break;
        }

        if (vetor[meio] < numero) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (posicao != -1) {
        printf("O numero %d foi encontrado na posicao %d do vetor.\n", numero, posicao);
    } else {
        printf("O numero %d nao foi encontrado no vetor.\n", numero);
    }
}

int main() {
    char opcao;

    do {
        printf("\n MENU DE OPCOES:  \n");
        printf("a. Gerar vetor\n");
        printf("b. Ordenar vetor\n");
        printf("c. Busca sequencial\n");
        printf("d. Busca binaria\n");
        printf("e. Sair\n");

        printf("Digite a opcao desejada: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case 'A':
            case 'a':
                gerarVetor();
                break;
            case 'B':
            case 'b':
                ordenarVetor();
                break;
            case 'C':
            case 'c':
                buscaSequencial();
                break;
            case 'D':
            case 'd':
                buscaBinaria();
                break;
            case 'E':
            case 'e':
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 'E' && opcao != 'e');

    free(vetor); // Libera a memória alocada para o vetor

    return 0;
}
