#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"

using namespace std;

node *partition(node *head, int x)
{
    node *small = NULL;
    node *big = NULL;
    node *traverse = head;

    while (traverse != NULL){
        
        node *temp = NULL;
        if(traverse->data < x){
            //push into small
            temp = traverse->next;
            traverse->next = small;
            small = traverse;
            traverse = temp;
        } else {
            temp = traverse->next;
            traverse->next = big;
            big = traverse;
            traverse = temp;
        }
    }

    if(small == NULL)
        return big;

    traverse = small;
    while(traverse->next != NULL){
        traverse = traverse->next;
    }

    traverse->next = big;
    return small;
}


int main()
{
    node *head = NULL;
    node *n = new node(0);
    head = n;
    head = n->addNode(head, 1);
    head = n->addNode(head, 9);
    head = n->addNode(head, 3);
    head = n->addNode(head, 5);
    head = n->addNode(head, 4);
    head = n->addNode(head, 6);
    head = n->addNode(head, 2);
    head = n->addNode(head, 7);
    n->printNodes();
    head = partition(head, 5);
    head->printNodes();
    return 0;
}

