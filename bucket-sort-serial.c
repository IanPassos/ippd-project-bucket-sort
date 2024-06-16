#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int limit = 100000;

// Ordenação com Insertion Sort
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

// Ordenando array A com Bucket Sort
void bucketSort(int A[], int n)
{
    // 1 - Criando N Buckets
    int **b = (int **)malloc(n * sizeof(int *));
    int *size = (int *)malloc(n * sizeof(int)); // Armazenar o tamanho de cada bucket
    for (int i = 0; i < n; i++)
    {
        b[i] = (int *)malloc(n * sizeof(int));
        size[i] = 0;
    }

    // 2 - Colocando os elementos em diferentes buckets
    for (int i = 0; i < n; i++)
    {
        int bi = (int)((float)n * ((float)A[i] / (float)limit));
        b[bi][size[bi]] = A[i];
        size[bi]++;
    }

    // 3 - Ordenando cada bucket com Insertion Sort
    for (int i = 0; i < n; i++)
    {
        insertionSort(b[i], size[i]);
    }

    // 4 - Juntar os buckets novamente em A[]
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < size[i]; j++)
        {
            A[index++] = b[i][j];
        }
        free(b[i]); // Liberando a memória alocada para o bucket
    }
    free(b);    // Liberando a memória alocada para os ponteiros dos buckets
    free(size); // Liberando a memória alocada para os tamanhos dos buckets
}

// Programa principal para executar a ordenação
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
