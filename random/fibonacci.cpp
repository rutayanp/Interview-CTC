#include <iostream>
#include <stdlib.h>

using namespace std;

int fibonacci(int n)
{
    if(n == 1 || n == 0)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    int n = 6;
    cout << fibonacci(n) << endl;
    return 0;
}
