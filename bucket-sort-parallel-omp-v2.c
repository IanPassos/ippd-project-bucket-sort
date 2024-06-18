#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define threads 8

// Ordenação dos itens em cada bucket com Insertion Sort
void insertionSort(float bucket[], int pos)
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

// Ordenando o vetor A com Bucket Sort
void bucketSort(float A[], int n, int limit)
{
    int i, j, k; // Contadores
    int bi; // Índice primário dos buckets

    // 1 - Criando N Buckets
    float **b = (float **)malloc(n * sizeof(float *)); // Alocando memória para os N buckets
    int *pos = (int *)calloc(n, sizeof(int)); // índice secundário dos buckets

    for (i = 0; i < n; i++){
        b[i] = (float *)malloc(n * sizeof(float)); //Alocando memória para os N possíveis itens
    }

    #pragma omp parallel num_threads(threads) private(i, bi) shared(b, pos, A)
    {
        int my_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int index_local = 0;
        int n_per_thread = n / num_threads;
        int start = my_id * n_per_thread;
        int end = (my_id + 1) * n_per_thread;

        if (my_id == num_threads - 1) {
            end = n;
        }
        
        // 2 - Colocando os elementos em diferentes buckets

        #pragma omp for schedule(static)
        for (i = start; i < end; i++)
        {
            bi = (int)((float)(n - 1) * (A[i] / (float)limit));

            #pragma omp critical
            {
                b[bi][pos[bi]] = A[i];
                pos[bi] += 1;
            }        
        }

        #pragma omp barrier
        
        // 3 - Ordenando cada bucket com Insertion Sort
        #pragma omp for
        for (i = 0; i < n; i++)
        {
            if(pos[i] > 0){
                insertionSort(b[i], pos[i]);
            }
        }

        #pragma omp barrier
        
        // 4 - Juntar os buckets novamente em A[]

        for (i = 0; i < start; i++)
        {
            index_local += pos[i];
        }

        for (i = start; i < end; i++)
        {
            for (j = 0; j < pos[i]; j++)
            {
                #pragma omp critical
                {
                    A[index_local++] = b[i][j];
                }
            }
            free(b[i]);
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

    printf("\nArray ordenado em %f segundos\n", t2);

    for (i = 0; i < n; i++)
    {
        printf("%.0f ", A[i]);

        if((i + 1) % 10 == 0){
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}
