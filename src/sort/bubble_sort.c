#include "../../include/sort.h"


// 冒泡排序
int bubble_sort(int *input, int len, int on)
{
    if (!on)
    {
        return 0;
    }

    /*
    第一个循环（外循环），负责把需要冒泡的那个数字排除在外；实际上是保证至少每个数据都有全len长度的移动
    第二个循环（内循环），负责两两比较交换。
    */
    for (size_t i = 0; i < len; i++)
    {
        // 因为涉及前一位值的下标所以这里应该是1 每完成一次外循环排到最后的一定是最大(最小)的数因此可以少做i次循环
        for (size_t p = 1; p < len - i; p++)
        {
            //这里大小与决定从大到小还是从小到大
            if (input[p] > input[p-1])
            {
                swap(input,p,p-1);
            }
        }
    }
}