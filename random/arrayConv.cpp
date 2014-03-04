#include <iostream>
#include <stdlib.h>

using namespace std;

int findIndex(int i, int N)
{
    int index = (i % 3) * N + (i / 3);
    return index;
}

void swap(string &s1, string &s2)
{
    string temp; 

    temp = s1;
    s1 = s2;
    s2 = temp;
}

void arrayConv(string *a, int len)
{
    int N = len/3;
    int index;

    for(int i = 0; i < len; i++){
        index = findIndex(i, N);
        while(index < i)
            index = findIndex(index, N);
    
        if(i != index)
            swap(a[i], a[index]);
    }
}

int main()
{
    string a[] = {"a1", "a2", "a3", "b1", "b2", "b3", "c1", "c2", "c3"};
    arrayConv(a, 9);
    for(int i = 0; i < 9; i++){
        cout << a[i] << ", ";
    }
    return 0;
}

