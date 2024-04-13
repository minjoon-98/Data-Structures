#include <stdio.h>

int mytest(int a, int b)
{
    int result = a + b;
    return result;
}

int main()
{
    int c;
    c = mytest(10, 20);
    printf("c = %d\\n", c);
}
