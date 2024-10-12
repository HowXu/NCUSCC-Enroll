#include "../Unity/src/unity.h"
#include <stdio.h>
// #include "../include/random.h" 包含多了哈
#include "../include/sort.h"

#define INT 0
#define FLOAT 1

#define TIMES 10

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

// 生成随机数组的测试
void test_gen_arr()
{

    // int
    union data *arr1 = get_random_array(10, 20, TIMES, INT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr1[i].i);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
        
    }

    // float
    union data *arr2 = get_random_array(10, 20, TIMES, FLOAT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr2[i].f);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }
}

// 冒泡排序测试
void test_bubble_sort()
{

    // int
    union data *arr1 = get_random_array(10, 20, TIMES, INT);
    bubble_sort(arr1, TIMES, INT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr1[i].i);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }

    // float
    union data *arr2 = get_random_array(10, 20, TIMES, FLOAT);
    bubble_sort(arr2, TIMES, FLOAT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr2[i].f);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }
}

// 基础堆排序测试
void test_heap_sort()
{

    // int
    union data *arr1 = get_random_array(10, 200, TIMES, INT);
    heap_sort(arr1, TIMES, INT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr1[i].i);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }

    // float
    union data *arr2 = get_random_array(10, 20000, TIMES, FLOAT);
    heap_sort(arr2, TIMES, FLOAT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr2[i].f);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }
}

// 斐波纳契堆排序测试
void test_fbi_heap_sort()
{

    // int
    union data *arr1 = get_random_array(10, 200, TIMES, INT);
    fibonacciHeapSort(arr1, TIMES, INT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr1[i].i);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }

    // float
    union data *arr2 = get_random_array(10, 20000, TIMES, FLOAT);
    fibonacciHeapSort(arr2, TIMES, FLOAT);
    for (size_t i = 0; i < TIMES; i++)
    {
        /* code */
        printf("%d ",arr2[i].f);
        if (i == TIMES -1)
        {
            /* code */
            printf("\n");
        }
    }
}

// 数据测试 10000
void test_10000_data()
{
    // 获取八段10000data
    int len = 10000;
    union data *arr1 = get_random_array(1, 250000, len, INT);
    union data *arr2 = get_random_array(1, 250000, len, INT);
    union data *arr3 = get_random_array(1, 250000, len, INT);

    union data *arr4 = get_random_array(1, 250000, len, FLOAT);
    union data *arr5 = get_random_array(1, 250000, len, FLOAT);
    union data *arr6 = get_random_array(1, 250000, len, FLOAT);

    // 分别调用
    bubble_sort(arr1, len, INT);
    heap_sort(arr2, len, INT);
    fibonacciHeapSort(arr3, len, INT);

    bubble_sort(arr4, len, FLOAT);
    heap_sort(arr5, len, FLOAT);
    fibonacciHeapSort(arr6, len, FLOAT);

    //断言
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        TEST_ASSERT_EQUAL_INT(arr1[i].i, arr2[i].i);
        TEST_ASSERT_EQUAL_INT(arr2[i].i, arr3[i].i);
        TEST_ASSERT_EQUAL_INT(arr3[i].i, arr1[i].i);

        TEST_ASSERT_EQUAL_FLOAT(arr4[i].f, arr5[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr5[i].f, arr6[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr6[i].f, arr4[i].f);
    }
    
}

// 数据测试 100000
void test_100000_data()
{
    // 获取八段10000data
    int len = 100000;
    union data *arr1 = get_random_array(1, 250000, len, INT);
    union data *arr2 = get_random_array(1, 250000, len, INT);
    union data *arr3 = get_random_array(1, 250000, len, INT);

    union data *arr4 = get_random_array(1, 250000, len, FLOAT);
    union data *arr5 = get_random_array(1, 250000, len, FLOAT);
    union data *arr6 = get_random_array(1, 250000, len, FLOAT);

    // 分别调用
    bubble_sort(arr1, len, INT);
    heap_sort(arr2, len, INT);
    fibonacciHeapSort(arr3, len, INT);

    bubble_sort(arr4, len, FLOAT);
    heap_sort(arr5, len, FLOAT);
    fibonacciHeapSort(arr6, len, FLOAT);

    //断言
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        TEST_ASSERT_EQUAL_INT(arr1[i].i, arr2[i].i);
        TEST_ASSERT_EQUAL_INT(arr2[i].i, arr3[i].i);
        TEST_ASSERT_EQUAL_INT(arr3[i].i, arr1[i].i);

        TEST_ASSERT_EQUAL_FLOAT(arr4[i].f, arr5[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr5[i].f, arr6[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr6[i].f, arr4[i].f);
    }
    
}

// 数据测试 200000
void test_200000_data()
{
    // 获取八段10000data
    int len = 200000;
    union data *arr1 = get_random_array(1, 250000, len, INT);
    union data *arr2 = get_random_array(1, 250000, len, INT);
    union data *arr3 = get_random_array(1, 250000, len, INT);

    union data *arr4 = get_random_array(1, 250000, len, FLOAT);
    union data *arr5 = get_random_array(1, 250000, len, FLOAT);
    union data *arr6 = get_random_array(1, 250000, len, FLOAT);

    // 分别调用
    bubble_sort(arr1, len, INT);
    heap_sort(arr2, len, INT);
    fibonacciHeapSort(arr3, len, INT);

    bubble_sort(arr4, len, FLOAT);
    heap_sort(arr5, len, FLOAT);
    fibonacciHeapSort(arr6, len, FLOAT);

    //断言
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        TEST_ASSERT_EQUAL_INT(arr1[i].i, arr2[i].i);
        TEST_ASSERT_EQUAL_INT(arr2[i].i, arr3[i].i);
        TEST_ASSERT_EQUAL_INT(arr3[i].i, arr1[i].i);

        TEST_ASSERT_EQUAL_FLOAT(arr4[i].f, arr5[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr5[i].f, arr6[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr6[i].f, arr4[i].f);
    }
    
}

// 数据测试 300000
void test_300000_data()
{
    // 获取八段10000data
    int len = 300000;
    union data *arr1 = get_random_array(1, 250000, len, INT);
    union data *arr2 = get_random_array(1, 250000, len, INT);
    union data *arr3 = get_random_array(1, 250000, len, INT);

    union data *arr4 = get_random_array(1, 250000, len, FLOAT);
    union data *arr5 = get_random_array(1, 250000, len, FLOAT);
    union data *arr6 = get_random_array(1, 250000, len, FLOAT);

    // 分别调用
    bubble_sort(arr1, len, INT);
    heap_sort(arr2, len, INT);
    fibonacciHeapSort(arr3, len, INT);

    bubble_sort(arr4, len, FLOAT);
    heap_sort(arr5, len, FLOAT);
    fibonacciHeapSort(arr6, len, FLOAT);

    //断言
    for (size_t i = 0; i < len; i++)
    {
        /* code */
        TEST_ASSERT_EQUAL_INT(arr1[i].i, arr2[i].i);
        TEST_ASSERT_EQUAL_INT(arr2[i].i, arr3[i].i);
        TEST_ASSERT_EQUAL_INT(arr3[i].i, arr1[i].i);

        TEST_ASSERT_EQUAL_FLOAT(arr4[i].f, arr5[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr5[i].f, arr6[i].f);
        TEST_ASSERT_EQUAL_FLOAT(arr6[i].f, arr4[i].f);
    }
    
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_unity);
    RUN_TEST(test_gen_arr);
    RUN_TEST(test_bubble_sort);
    RUN_TEST(test_heap_sort);
    RUN_TEST(test_fbi_heap_sort);

    //data测试
    RUN_TEST(test_10000_data);
    RUN_TEST(test_100000_data);
    RUN_TEST(test_200000_data);
    RUN_TEST(test_300000_data);
    return UNITY_END();
    
}
