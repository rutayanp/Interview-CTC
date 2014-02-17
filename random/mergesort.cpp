#include <iostream>
#include <stdlib.h>

using namespace std;
int *a;
int *aux;
void merge(int *a, int *aux, int high, int low, int middle)
{
    for(int i = low; i < high; i++){
        aux[i] = a[i];
    } 
    
    int i, j, current;
    i = low;
    j = middle + 1;
    current = low;
    while(i <= middle && j <= high){
        if(aux[i] < aux[j]) 
            a[current++] = aux[i++];
        else
            a[current++] = aux[j++]; 
    }

    //int remaining = middle - i;
    for(i = i; i <= middle; i++){
        a[current++] = aux[i];
    }    
    
}

void mergesort(int *a, int low, int high)
{
    int middle;
    middle = (low + high)/2;
    int aux[sizeof(a)/sizeof(a[0])];
    
    if (low < high){
        mergesort(a,low,middle);
        mergesort(a, middle + 1, high);
        merge(a, aux, low, high, middle);
    }
}

int main()
{
    int arr[] = {2,4,3,7,6,3,1,7,5,39,67};
    a = arr;
    int len = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;
    mergesort(a, 0, len - 1);
    for(int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;
    return 0;
}
