#include <iostream>
#include <stdlib.h>
#include "tree.cpp"

using namespace std;

treeNode<int> *createBST(int *a, int start, int end)
{
    if (start > end)
        return NULL;

    int middle = (start + end)/2;
    treeNode<int> *n = new treeNode<int>(a[middle]);
    n->left = createBST(a, start, middle - 1);
    n->right = createBST(a, middle + 1, end);

    return n;
}

int main()
{
    int arr[] = {1,2,3,4,5,6,7,8,9};
    treeNode<int> * root = createBST(arr, 0,8);
    cout << "IN-ORDER : " ;
    root->inOrder(root);
    return 0;
}
