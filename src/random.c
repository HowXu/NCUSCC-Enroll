#include "../include/random.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*
为什么你没有像样的随机数生成器 o.O
int random_number = rand() % (max - min + 1) + min;
min ＋ 1.0 * ( rand() % RAND_MAX ) / RAND_MAX * ( max - min )
*/

union data *get_random_array(int min, int max, int size, int type)
{

    srand((unsigned int)time(NULL)); // seed
    //动态分配内存
    union data *arr = (union data *) malloc(size * sizeof(union data)); //return

    switch (type)
    {
    case 0:
        // 生成int类型
        int num_i;

        for (int i = 0; i < size; i++)
        {
            //添加
            num_i = rand() % (max - min + 1) + min;
            arr[i].i = num_i;
        }
        break;

    case 1:
        // 生成float类型
        float num_f;
        //分配内存
        for (int i = 0; i < size; i++)
        {
            //添加
            num_f = (float)min + 1.0 * ( rand() % RAND_MAX ) / RAND_MAX * ( (float)max - (float)min );
            arr[i].f = num_f;
        }
        break;
    }
    //什么异常处理o.O?
    return arr;
}

union data *get_random_array_with_seed(int min, int max, int size, int type,unsigned int seed){

    srand(seed); // seed
    //动态分配内存
    union data *arr = (union data *) malloc(size * sizeof(union data)); //return

    switch (type)
    {
    case 0:
        // 生成int类型
        int num_i;

        for (int i = 0; i < size; i++)
        {
            //添加
            num_i = rand() % (max - min + 1) + min;
            arr[i].i = num_i;
        }
        break;

    case 1:
        // 生成float类型
        float num_f;
        //分配内存
        for (int i = 0; i < size; i++)
        {
            //添加
            num_f = (float)min + 1.0 * ( rand() % RAND_MAX ) / RAND_MAX * ( (float)max - (float)min );
            arr[i].f = num_f;
        }
        break;
    }
    //什么异常处理o.O?
    return arr;
}