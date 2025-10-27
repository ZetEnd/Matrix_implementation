#include <stdio.h>
#include <stdlib.h>

int** malloc_first_method(int M, int N){
    int count = 0;

    int** parr = (int**)malloc(M*sizeof(int*));
    int *varr = (int*)malloc(M*N*sizeof(int));

    for(int i = 0 ; i < M; i++){
        parr[i] = varr + i*N;
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            parr[i][j] = ++count;
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", parr[i][j]);
        }
    }

    return parr;
}

void free_first_malloc(int** parr){

    /*for(int i = 0; i< M; i++){
        free(parr[i]);
    }*/
    free(parr[0]);
    free(parr);
}
int** malloc_second_method(int M, int N){

    int count = 0;
    int** parr = (int**)malloc(M*sizeof(int*));

    for(int i = 0; i < M; i++){
        parr[i] = (int*)malloc(N*sizeof(int));
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            parr[i][j] = ++count;
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", parr[i][j]);
        }
    }

    return parr;
}

void free_second_malloc(int** parr, int M){

    for(int i = 0; i < M; i++){
        free(parr[i]);
    }

    free(parr);

}

int** malloc_third_method(int M, int N){

    int count = 0;
    int** parr = (int**)malloc(M*sizeof(int*) + M*N*sizeof(int));

    int* ptr = (int*)(parr + M);

    for(int i = 0; i < M; i++){
        parr[i] = ptr + i*N;
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            parr[i][j] = ++count;
        }
    }

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", parr[i][j]);
        }
    }

    return parr;
}

void free_third_malloc(int** parr){
    free(parr);
}

int main(int argc, char** argv){

    int M = 4, N = 4;
    int ** parr = malloc_first_method(M, N);
    free_first_malloc(parr);

    parr = NULL;
    parr = malloc_second_method(M, N);
    free_second_malloc(parr, M);

    parr = NULL;
    parr = malloc_third_method(M, N);
    free_third_malloc(parr);


}