#include "../../include/sort.h"

// 桶排序

/*
桶排序（Bucket sort）或所谓的箱排序，是一个排序算法，工作的原理是将数组分到有限数量的桶里。
每个桶再个别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序），最后依次把各个桶中的记录列出来记得到有序序列。
桶排序是鸽巢排序的一种归纳结果。当要被排序的数组内的数值是均匀分配的时候，桶排序使用线性时间（Θ(n)）。
但桶排序并不是比较排序，他不受到O(n log n)下限的影响。
*/



int bucket_sort(int *input, int len, int on)
{
    if (!on)
    {
        return 0;
    }

    // 造个桶 获取最大值以减少内存使用 注意数组大小和下标索引关系
    int max = get_max(input, len) + 1;
    int bucket[max];

    for (size_t i = 0; i < max; i++)
    {
        /* code */
        bucket[i] = 0;
        // 初始化 不然有可能是错的
    }

    for (int i = 0; i < len; i++)
    {
        /* code */
        bucket[input[i]] = 1; // 有数组就做标记
    }

    for (int i = 0; i < len; i++)
    {
        // 重新用bucket对数组赋值
        for (int p = 0; p < max; p++)
        {
            if (bucket[p])
            {
                /* code */
                // 把标记设置为0并且加回到input中
                input[i] = p;
                bucket[p] = 0;
                break;
            }
        }
    }
}