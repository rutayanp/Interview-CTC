#include <iostream>
#include <stdlib.h>

using namespace std;

int a[5][5] = {
                {1,2,3,4,5},
                {6,7,8,9,10},
                {11,12,13,14,15},
                {16,17,18,19,20},
                {21,22,23,24,25}
               };

int N = 5;

void rotateMatrix()
{
    int first, last;
    for (int layer = 0; layer < N/2; layer++){
        first = layer;
        last = N - layer - 1;
        for(int i = first; i < last; i++){
            int offset = i - first;
            int top = a[first][i];
            
            //left -> top
            a[first][i] = a[last - offset][first];
            
            //bottom->left
            a[last - offset][first] = a[last][last - offset];

            //right->bottom
            a[last][last - offset] = a[first + offset][last];

            //top->right
            a[i][last] = top;
        }
    }
}

void printMatrix()
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N ; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;  
    }    
}
int main()
{
    printMatrix();
    cout << endl << endl;
    rotateMatrix();
    rotateMatrix();
    printMatrix();
}
