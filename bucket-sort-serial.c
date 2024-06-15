#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int limit = 100000;

// Fun��o para ordenar um bucket individual usando Insertion Sort
void insertionSort(int bucket[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Fun��o para ordenar um array arr[] de tamanho n usando Bucket Sort
void bucketSort(int arr[], int n)
{
    // 1) Criar n buckets vazios
    int **b = (int **)malloc(n * sizeof(int *));
    int *size = (int *)malloc(n * sizeof(int)); // Armazenar o tamanho de cada bucket
    for (int i = 0; i < n; i++)
    {
        b[i] = (int *)malloc(n * sizeof(int));
        size[i] = 0;
    }

    // 2) Colocar os elementos do array em buckets diferentes
    for (int i = 0; i < n; i++)
    {
        // int bi = n * arr[i]; // �ndice do bucket
        int bi = (int)((float)n * ((float)arr[i] / (float)limit));
        b[bi][size[bi]] = arr[i];
        size[bi]++;
    }

    // 3) Ordenar cada bucket individual usando Insertion Sort
    for (int i = 0; i < n; i++)
    {
        insertionSort(b[i], size[i]);
    }

    // 4) Concatenar todos os buckets de volta em arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < size[i]; j++)
        {
            arr[index++] = b[i][j];
        }
        free(b[i]); // Liberar a mem�ria alocada para o bucket
    }
    free(b);    // Liberar a mem�ria alocada para os ponteiros dos buckets
    free(size); // Liberar a mem�ria alocada para os tamanhos dos buckets
}

// Programa principal para testar a fun��o acima
int main()
{
    int A[10000];
    int n = 10000;
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        A[i] = rand() % limit;
    }

    bucketSort(A, n);

    printf("Array ordenado \n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);

        if (((i + 1) % 10) == 0)
        {
            printf("\n");
        }
    }

    return 0;
}
