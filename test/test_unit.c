#include "../Unity/src/unity.h"
#include <stdio.h>
//#include "../include/random.h" 包含多了哈
#include "../include/sort.h"

#define INT 0
#define FLOAT 1

void setUp()
{
}

void tearDown()
{
}

void test_unity()
{
    printf("Test Unity is Running ! n_n\n");
}

//生成随机数组的测试
void test_gen_arr(){


    //int
    union data *arr1 = get_random_array(10,20,8,INT);
    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        //printf("%d\n",arr1[i].i);
    }

    //float
    union data *arr2 = get_random_array(10,20,8,FLOAT);
    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        //printf("%f\n",arr2[i].f);
    }
    
}

//冒泡排序测试
void test_bubble_sort(){


    //int
    union data *arr1 = get_random_array(10,20,8,INT);
    bubble_sort(arr1,8,INT);
    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        //printf("%d\n",arr1[i].i);
    }

    //float
    union data *arr2 = get_random_array(10,20,8,FLOAT);
    bubble_sort(arr2,8,FLOAT);
    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        //printf("%f\n",arr2[i].f);
    }
    
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_unity);
    RUN_TEST(test_gen_arr);
    RUN_TEST(test_bubble_sort);
    return UNITY_END();
}
