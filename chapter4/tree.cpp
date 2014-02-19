#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

template <class T>
class treeNode{
    
public:
    T data;
    treeNode *left;
    treeNode *right;    
    
    treeNode(T d){
        data = d;
        left = NULL;
        right = NULL;
    }
//methods
    treeNode<T> * insertNode(treeNode *node, T d);
    void inOrder(treeNode *node);
    void preOrder(treeNode *node);
    void postOrder(treeNode *node);
    int maxDepth(treeNode *node);
    int checkHeight(treeNode *node);
    bool isBalanced(treeNode *node);
};

//Method to insert a node
template <class T>
treeNode<T> * treeNode<T>::insertNode(treeNode *node, T d)
{
    if(node == NULL)
        return new treeNode<T>(d);

    if(d < node->data){
        node->left = insertNode(node->left, d);
    } else if(d > node->data){
        node->right = insertNode(node->right, d);
    }

    return node;
}

//In Order Traversal
template<class T>
void treeNode<T>::inOrder(treeNode *node)
{
    if(node != NULL){
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}

//Pre Order Traversal
template<class T>
void treeNode<T>::preOrder(treeNode *node)
{
    if(node != NULL){
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

//Post Order Traversal
template<class T>
void treeNode<T>::postOrder(treeNode *node)
{
    if(node != NULL){
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
}

int max(int c1, int c2)
{
    return (c1 >= c2 ? c1 : c2);
}

//find the maximum depth of a node in the tree
template<class T>
int treeNode<T>::maxDepth(treeNode *node)
{
    if(node == NULL)
        return 0;

    return 1 + max(maxDepth(node->left), maxDepth(node->right));
    
}

//helper function to check the height difference
template<class T>
int treeNode<T>::checkHeight(treeNode *node)
{
    if(node == NULL)
        return 0;

    int leftheight = checkHeight(node->left);
    if(leftheight == -1)
        return -1;

    int rightheight = checkHeight(node->right);
    if(rightheight == -1)
        return -1;

    int diffheight = leftheight - rightheight;
    if(abs(diffheight) > 1){
        return -1;
    } else {
        return max(leftheight, rightheight) + 1;
    }
}

//check if the tree is balanced
template<class T>
bool treeNode<T>::isBalanced(treeNode *node)
{
    int result = checkHeight(node);
    return result == -1 ? false : true;
}


int main()
{
    treeNode<int> *root;
    root = new treeNode<int>(5);
    root = root->insertNode(root, 3);    
    root = root->insertNode(root, 4);    
    root = root->insertNode(root, 2);    
    root = root->insertNode(root, 1);    
    root = root->insertNode(root, 7);    
    root = root->insertNode(root, 6);    
    root = root->insertNode(root, 8);    
    root = root->insertNode(root, 9);
    
    cout << "inorder : ";
    root->inOrder(root);
    cout << endl;   
    
    cout << "preOrder : " ;
    root->preOrder(root);
    cout << endl;
    
    cout << "postOrder : " ;
    root->postOrder(root);
    cout << endl;
    
    cout << "MAX DEPTH : " << root->maxDepth(root) << endl ;
    
    bool isbalanced = root->isBalanced(root);
    isbalanced == 1 ? cout << "balanced" << endl : cout << "unbalanced" << endl;

    
}
