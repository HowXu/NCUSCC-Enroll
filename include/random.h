
union data
{
    //鉴于牢E要求既要整型又要浮点型所以这里用Union
    int i;
    float f;
};
//随机数生成器 返回一个数组
union data *get_random_array(int min,int max,int size,int type);

union data *get_random_array_with_seed(int min, int max, int size, int type,unsigned int seed);