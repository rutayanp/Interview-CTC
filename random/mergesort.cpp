#include <iostream>
#include <stdlib.h>

using namespace std;

void merge(int *a, int *aux, int low, int high, int middle)
{
    for(int i = low; i <= high; i++){
        aux[i] = a[i];
    }

    int i = low;
    int j = middle + 1;
    int current = low;

    while (i <= middle && j <=high){
        if(aux[i] < aux[j])
            a[current++] = aux[i++];
        else
            a[current++] = aux[j++];
    }

    for (int k = i; k <= middle; k++){
        a[current] = aux[k];
    }
}

void mergesort(int *a, int *aux, int low, int high)
{
    if(low < high){
        int middle = (low + high)/2;
        mergesort(a, aux, low, middle);
        mergesort(a, aux, middle + 1, high);
        merge(a, aux, low, high, middle);
    }
}

int main()
{
    int arr[] = {0,1,45,2,6,3,8,9,5,2};
    int *a, *aux;
    int len = sizeof(arr)/sizeof(arr[0]);
    a = arr;
    aux = new int[len];
    for(int i = 0; i < len; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
    mergesort(a, aux, 0, len - 1);
    for(int i = 0; i < len; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
}
