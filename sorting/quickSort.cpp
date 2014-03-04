#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

int len;

void swap(int *a, int p, int q)
{
    int temp  = a[p];
    a[p] = a[q];
    a[q] = temp; 
}

int partition(int *a, int p, int q)
{
    int pivot = a[(p + q)/2];
    int left = p;
    int right = q; 
    while(left <= right){
        while(a[left] < pivot)
            left++;
        while(a[right] > pivot)
            right--;

        if(left <= right){
            swap(a, left, right);
            left++;
            right--;
        }
    }
    return left;
}

void quicksort(int *a, int p, int q)
{
    int index;
    index = partition(a, p, q);
    for(int i = 0; i < len; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
    if(p < index - 1){
        quicksort(a, p, index - 1);
    }
    if(index < q){
        quicksort(a, index, q);
    }
}

int main()
{
    int arr[] = {1,5,2,7,3,9,5,2,0,9,17};
    int *a = arr;
    len = sizeof(arr)/sizeof(arr[0]);
    
    for(int i = 0; i < len; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
    quicksort(a, 0, len - 1);
    for(int i = 0; i < len; i++){
        cout << a[i] << ",";
    } 
    cout << endl;
}
