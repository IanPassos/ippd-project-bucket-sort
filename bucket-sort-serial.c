#include <stdio.h>
#include <stdlib.h>

// Função para ordenar um bucket individual usando Insertion Sort
void insertionSort(float bucket[], int size) {
    for (int i = 1; i < size; ++i) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Função para ordenar um array arr[] de tamanho n usando Bucket Sort
void bucketSort(float arr[], int n) {
    // 1) Criar n buckets vazios
    float** b = (float**)malloc(n * sizeof(float*));
    int* size = (int*)malloc(n * sizeof(int)); // Armazenar o tamanho de cada bucket
    for (int i = 0; i < n; i++) {
        b[i] = (float*)malloc(n * sizeof(float));
        size[i] = 0;
    }

    // 2) Colocar os elementos do array em buckets diferentes
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Índice do bucket
        b[bi][size[bi]] = arr[i];
        size[bi]++;
    }

    // 3) Ordenar cada bucket individual usando Insertion Sort
    for (int i = 0; i < n; i++) {
        insertionSort(b[i], size[i]);
    }

    // 4) Concatenar todos os buckets de volta em arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < size[i]; j++) {
            arr[index++] = b[i][j];
        }
        free(b[i]); // Liberar a memória alocada para o bucket
    }
    free(b); // Liberar a memória alocada para os ponteiros dos buckets
    free(size); // Liberar a memória alocada para os tamanhos dos buckets
}

// Programa principal para testar a função acima
int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    printf("Array ordenado é \n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    return 0;
}


