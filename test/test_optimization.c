#include <stdio.h>
// #include "../include/random.h" 包含多了哈
#include "../include/sort.h"

#define INT 0
#define FLOAT 1

#define SEED 114514
#define SIZE 10000 //这个size不要取得太小了不然total会是0 不修了哈
//为了测试精准度 使用统一的种子生成随机数 但是在函数调用中来这一出还是感觉不太严谨

void test_bubble_sort(){
    union data *arr1 = get_random_array_with_seed(1, 250000, SIZE, INT,SEED);
    union data *arr2 = get_random_array_with_seed(1, 250000, SIZE, FLOAT,SEED);

    bubble_sort(arr1,SIZE,INT);
    bubble_sort(arr2,SIZE,FLOAT);
}

void test_heap_sort(){
    union data *arr1 = get_random_array_with_seed(1, 250000, SIZE, INT,SEED);
    union data *arr2 = get_random_array_with_seed(1, 250000, SIZE, FLOAT,SEED);

    heap_sort(arr1,SIZE,INT);
    heap_sort(arr2,SIZE,FLOAT);
}

void test_fib_heap_sort(){
    union data *arr1 = get_random_array_with_seed(1, 250000, SIZE, INT,SEED);
    union data *arr2 = get_random_array_with_seed(1, 250000, SIZE, FLOAT,SEED);

    fibonacciHeapSort(arr1,SIZE,INT);
    fibonacciHeapSort(arr2,SIZE,FLOAT);
}

int main()
{
    // 这里应该不使用测试单元
    test_bubble_sort();
    test_heap_sort();
    test_fib_heap_sort();
    return 0;
}
