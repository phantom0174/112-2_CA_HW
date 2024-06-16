#include <stdio.h>

int fast_power_recur(int x, int pow)
{
    if(pow == 0)
    {
        return 1;
    }

    int m = fast_power_recur(x, pow >> 1);
    if(pow & 1)
    {
        return x * m * m;
    }
    return m * m;
}

int main(void)
{
    int power = fast_power_recur(6, 11);
    printf("%d", power);
    return 0;
}