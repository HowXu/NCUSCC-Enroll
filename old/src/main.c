#include <stdio.h>
#include "../include/sort.h"

#define false 0
#define true 1

// 时间复杂度：时间频度，一个算法执行所耗费的时间。算法中通常用数据比较次数与数据移动次数 进行衡量。
int main(int index, char **args)
{
    int arr[10] = {7, 3, 4, 6, 10, 8, 1, 2, 89, 13};
    // 获取数组长度
    int len = sizeof(arr) / sizeof(arr[0]);

    // 插入排序
    insertion_sort(arr, len, false);
    // 桶排序
    bucket_sort(arr, len, false);
    //冒泡排序
    bubble_sort(arr,len,true);

    // 输出检测
    for (size_t i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}