#include "../Unity/src/unity.h"
#include <stdio.h>

void setUp()
{
}

void tearDown()
{
}

void test_a()
{
    printf("Test Unity is Running ! n_n\n");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_a);
    return UNITY_END();
}
