#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>

using namespace std;

int main(int argc,char *argv[]) {
    srand((unsigned)(long long)argv);
    omp_set_num_threads(8);
    long long n = 1000000000;
    long long sum = 0;
    auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction (+: sum)
        for (long long i = 1; i <= n; i++) {
            int x1 = rand() % 20, x2 = rand() % 20;
            double x = -1 + 1.0 * x1 / 10;
            double y = -1 + 1.0 * x2 / 10;
            if (x * x + y * y <= 1)
                sum++;
        }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_time = end - start;
    std::cout << "OpenMP code time: " << duration_time.count() << " seconds" << std::endl;
    //printf("%.6lf\n", sum * 4.0 / n);
    return 0;
}