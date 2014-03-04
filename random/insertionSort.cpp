#include <iostream>

void swap(int &num1, int &num2)
{
    int temp;
    temp = num1;
    num1 = num2;
    num2 = temp;
}

void insertionSort(int *a , int len)
{
    for(int i = 1; i < len; i++){
        for(int j = i; j > 0; j--){
            if(a[j] < a[j - 1])
                swap(a[j], a[j - 1]);
        }
    }
}

int main()
{
    int a[] = {5,3,6,8,9,1};
    insertionSort(a, 6);
    for(int i = 0; i < 6; i++){
        cout << a[i] << endl;
    }
}
