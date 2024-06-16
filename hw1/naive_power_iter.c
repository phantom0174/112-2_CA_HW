#include <stdio.h>

int naive_power_iter(int x, int pow)
{
    int res = 1;
    for(int i = 0; i < pow; ++i)
    {
        res = res * x;
    }
    return res;
}

int main(void)
{
    int power = naive_power_iter(6, 11);
    printf("%d", power);
    return 0;
}