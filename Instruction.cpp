#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>

using namespace std;

int counter;
#pragma omp threadprivate(counter)//将counter声明为每个线程都有的变量
/*
 omp master:指定代码均由主线程执行,其他线程跳过
 omp single:指定代码由单一线程运行(anyone),所有线程阻塞用来同步,不同步需要nowait
 omp sections:指定任务组,一个section分配给一个线程
 omp flush(data1,data2):保证每个线程拥有的变量的一致性
*/
/*
omp parallel firstprivate(data):用于声明私有变量,并且初始化同名变量
omp parallel lastprivate(data):用于声明私有变量,在退出时同步给同名变量(根据逻辑上最后一个线程)
*/
void test_section() {
#pragma omp parallel sections
    {
#pragma omp section 
        printf("Section 1 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
        printf("Section 2 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
        printf("Section 3 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
        printf("Section 4 ThreadId = %d\n", omp_get_thread_num());
    }
    return;
}
void test_copyin() {
    counter = 10; //主线程的值
    printf("counter is %d\n", counter);
#pragma omp parallel copyin(counter) //将主线程的counter复制到各个线程中
    {
        counter = omp_get_thread_num() + counter + 1;
        printf(" thread %d : counter is %d\n", omp_get_thread_num(), counter);
    }
    printf("counter is %d\n", counter);
}
void testiter(int n) {
    if (n == 0)    return;
    printf("%d\n", n);
    testiter(n - 1);
    return;
}
int main(int argc,char *argv[]) {
    omp_set_num_threads(8);
#pragma omp parallel
    testiter(2);
    return 0;
}