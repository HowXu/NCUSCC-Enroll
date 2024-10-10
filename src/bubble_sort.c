#include "../include/sort.h"

// 冒泡排序
int bubble_sort(union data *arr, int len, int type)
{

    //内循环按数据量减少而减少
    switch (type)
    {
    case 0:
        for (int i = 0; i < len; i++)
        {
            // 内循环
            for (int j = 1; j < len - i; j++)
            {
                if (arr[j - 1].i > arr[j].i)
                {
                    // 大小于就随便吧
                    swap(arr, j - 1, j);
                }
            }
        }
        break;

    case 1:
        for (int i = 0; i < len; i++)
        {
            // 内循环
            for (int j = 1; j < len - i; j++)
            {
                if (arr[j - 1].f > arr[j].f)
                {
                    // 大小于就随便吧
                    swap(arr, j - 1, j);
                }
            }
        }
        break;
    }
}

