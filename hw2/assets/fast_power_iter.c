#include <stdio.h>

int fast_power_iter(int x, int pow)
{
    int res = 1;
    while(pow)
    {
        if(pow & 1)
        {
            res = res * x;
        }
        x = x * x;
        pow >>= 1;
    }
    return res;
}

int main(void)
{
    int power = fast_power_iter(6, 11);
    printf("%d", power);
    return 0;
}