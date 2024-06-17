#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define max_threads 8

// Ordenação com Insertion Sort
void insertionSort(float  bucket[], int pos)
{
    for (int i = 1; i < pos; ++i)
    {
        float key = bucket[i];
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
void bucketSort(float A[], int n, int limit)
{
    int i, j; // Contadores
    int bi; // Índice primário dos buckets

    int my_id;
    int num_threads;

    // 1 - Criando N Buckets
    float **b = (float **)malloc(n * sizeof(float *)); // Número de buckets
    int *pos = (int *)calloc(n, sizeof(int)); // índice secundário dos buckets

#pragma omp parallel num_threads(8) private(my_id)
{
    my_id = omp_get_thread_num();
    num_threads = omp_get_num_threads();

    #pragma omp parallel for private(i)
    for (i = my_id*(n/num_threads); i < (my_id + 1)*(n/num_threads); i++)
    {
    // my_id = 0 -> i = 00 -> limite 0+1 * 10 = 10
    // my_id = 1 -> i = 10 -> limite 1+1 * 10 = 20
    // my_id = 2 -> i = 20 -> limite 2+1 * 10 = 30
    // my_id = 3 -> i = 30 -> limite 3+1 * 10 = 40
    // my_id = 4 -> i = 40 -> limite 4+1 * 10 = 50
    // my_id = 5 -> i = 50 -> limite 5+1 * 10 = 60
    // my_id = 6 -> i = 60 -> limite 6+1 * 10 = 70
    // my_id = 7 -> i = 70 -> limite 7+1 * 10 = 80

        b[i] = (float *)malloc(n * sizeof(float));
    }

    #pragma omp barrier

    // 2 - Colocando os elementos em diferentes buckets

    #pragma omp parallel for private(i, bi)
    for (i = my_id*(n/num_threads); i < (my_id + 1)*(n/num_threads); i++)
    {
        bi = (float)n * (A[i] / (float)limit); 

        //fprintf(stderr, "%.2f %.2f %.2f %d \n", (float)n, A[i], (float)limit, bi);
        
        b[bi][pos[bi]] = A[i];
        pos[bi]++;
    }

    #pragma omp barrier

/*
    #pragma omp for private(i)
    for (i = my_id*(n/num_threads); i < (my_id + 1)*(n/num_threads); i++)
    {
        for(j = 0; j < pos[i]; i++)
        {
            printf("%d", b[i][j]);
        }
    }
*/
    
    // 3 - Ordenando cada bucket com Insertion Sort
    #pragma omp parallel for private(i)
    for (i = my_id*(n/num_threads); i < (my_id + 1)*(n/num_threads); i++)
    {
        insertionSort(b[i], pos[i]);
    }

    #pragma omp barrier

    // 4 - Juntar os buckets novamente em A[]
    int index = 0;

    #pragma omp single
    for (i = 0; i < n; i++)
    {
        #pragma omp task private(j, index)
        for (j = 0; j < pos[i]; j++)
        {
            A[index++] = b[i][j];
        }

        free(b[i]); // Liberando a memória alocada para o bucket
    }

    #pragma omp barrier
}
    free(b);    // Liberando a memória alocada para os ponteiros dos buckets
    free(pos); // Liberando a memória alocada para os tamanhos dos buckets
}

// Programa principal para executar a ordenação
int main()
{
    float *A; // Ponteiro para o vetor de elementos
    int i; // Contador
    int n; // Tamanho do vetor
    int limit = 100000; // Limite superior para randomização e cálculo de índice
    float t1, t2; // Medidores de tempo gasto

    srand(time(NULL));

    printf("Tamanho do vetor desejado: \n");
    scanf("%d", &n);

    A = (float *) malloc(sizeof(float)*n);

    for (i = 0; i < n; i++)
    {
        A[i] = rand() % limit;
    }

    t1 = omp_get_wtime();

    bucketSort(A, n, limit);

    t2 = omp_get_wtime() - t1;

    printf("Array ordenado em %f segundos\n", t2);

    /*for (i = 0; i < n; i++)
    {
        printf("%f ", A[i]);

        if (((i + 1) % 10) == 0)
        {
            printf("\n");
        }
    }*/

    return 0;
}
