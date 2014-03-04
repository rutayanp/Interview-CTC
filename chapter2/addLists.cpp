#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"

using namespace std;

node *addLists(node *l1, node *l2, int c)
{
    if(l1 == NULL && l2 == NULL && c == 0)
        return NULL;

    int sum = c;
    if(l1 != NULL){
        sum += l1->data;    
    }

    if(l2 != NULL){
        sum += l2->data;
    }

    c = sum / 10;
    sum = sum % 10;

    node *result = new node(sum);

    node *n = addLists(l1 == NULL ? NULL : l1->next, l2 == NULL ? NULL : l2->next, c);
    result->next = n;

    return result;
}

int main()
{
    node *head1 = NULL;
    node *l1 = new node(1);
    node *head2 = NULL;
    node *l2 = new node(9);
    node *result = NULL;
    head1 = l1;
    head2 = l2;
    head1 = l1->addNode(head1, 1);
    head1 = l1->addNode(head1, 1);
    head2 = l2->addNode(head2, 9);
    head2 = l2->addNode(head2, 8);
    l1->printNodes();
    l2->printNodes();
    result = addLists(l1, l2, 0);
    result->printNodes();
    return 0;
}


