#include <stdio.h>

int naive_power_recur(int x, int pow)
{
    if(pow == 0)
    {
        return 1;
    }
    return x * naive_power_recur(x, pow - 1);
}

int main(void)
{
    int power = naive_power_recur(6, 11);
    printf("%d", power);
    return 0;
}