#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>


void MultMatrix(int **matrixA, int **matrixB, int **resultado, int length) {
    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < length; k++) {
                resultado[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void PrintMatriz(int **matriz, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void FillMatrix(int **matrix, int length, int max)
{
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            matrix[i][j] = rand() % max;
        }
    }
}

int main(int argc, char *argv[]) {
    clock_t start, end;
    double elapsed_time;

    int length = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int max_number = 100;
    int verbose = 0;

    if (argc > 3 && strcmp(argv[3], "-v") == 0) {
        verbose = 1;
    }

    start = clock(); //Inicia Captura del tiempo

    int **matrixA = (int **)malloc(length * sizeof(int *));
    int **matrixB = (int **)malloc(length * sizeof(int *));
    int **result = (int **)malloc(length * sizeof(int *));

    for(int i = 0; i < length; i++){
        matrixA[i] = (int *)malloc(length * sizeof(int *));
        matrixB[i] = (int *)malloc(length * sizeof(int *));
        result[i] = (int *)malloc(length * sizeof(int *));
    }

    FillMatrix(matrixA, length, max_number);
    FillMatrix(matrixB, length, max_number);

    omp_set_num_threads(num_threads);

    MultMatrix(matrixA, matrixB, result, length);
    
    if(verbose){
        printf("Matriz A:\n");
        PrintMatriz(matrixA, length);

        printf("Matriz B:\n");
        PrintMatriz(matrixB, length);

        printf("Result:\n");
        PrintMatriz(result, length);
    }
    
    for(int i = 0; i < length; i++){
        free(matrixA[i]);
        free(matrixB[i]);
        free(result[i]);
    }

    free(matrixA);
    free(matrixB);
    free(result);

    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%f \n", elapsed_time);

    return 0;
}