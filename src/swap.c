#include "../include/sort.h"

void bubble_swap(union data *arr, int index_a, int index_b)
{
    // 抑或用不了哈
    /*
    in[index_a] ^= in[index_b];
    in[index_b] ^= in[index_a];
    in[index_a] ^= in[index_b];
    */
    union data tmp;
    tmp = arr[index_a];
    arr[index_a] = arr[index_b];
    arr[index_b] = tmp;
}

void heap_swap(union data *arr, int index_a, int index_b)
{
    // 抑或用不了哈
    /*
    in[index_a] ^= in[index_b];
    in[index_b] ^= in[index_a];
    in[index_a] ^= in[index_b];
    */
    union data tmp;
    tmp = arr[index_a];
    arr[index_a] = arr[index_b];
    arr[index_b] = tmp;
}