#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
    //int thread_count = strtol(argv[1], NULL, 10);
    omp_set_num_threads(8);
    
#pragma omp parallel 
    {
        int thread_count = omp_get_num_threads();
        int my_rank = omp_get_thread_num();
        printf("Hello from thread %d of %d\n", my_rank+1, thread_count);
    }

    return 0;
}