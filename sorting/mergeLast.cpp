#include <iostream>
#include <stdlib.h>

using namespace std;

void merge(int *a, int *b, int last_a, int last_b)
{
    int index_a = last_a;
    int index_b = last_b;
    int index = last_a + last_b + 1;

    while(index_b >= 0){
        if(index_a >= 0 && a[index_a] > b[index_b]){
            a[index--] = a[index_a--];
        }else{
            a[index--] = b[index_b--];
        }
    }
}

int main()
{
    int a[7];
    int b[4] = {1,2,3,4};
    a[0] = 10;
    a[1] = 11;
    a[2] = 12;
    int last_a = 2; 
    int len_a = sizeof(a)/sizeof(a[0]);
    int last_b = sizeof(b)/sizeof(b[0]) - 1;
    merge(a, b, last_a, last_b);
    for(int i = 0; i < len_a; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
}
