#include "../include/sort.h"

void swap(int *in, int index_a, int index_b)
{
    // 抑或位运算
    in[index_a] ^= in[index_b];
    in[index_b] ^= in[index_a];
    in[index_a] ^= in[index_b];
}

int get_max(int *input, int len)
{
    if (len == 0)
    {
        return 0;
    }

    int tmp = input[0];
    for (size_t i = 0; i < len; i++)
    {
        if (input[i] > tmp)
        {
            tmp = input[i];
        }
        /* code */
    }
    return tmp;
}