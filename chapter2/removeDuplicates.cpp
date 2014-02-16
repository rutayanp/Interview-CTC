#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"
#include <map>

node *removeDuplicates(node *head)
{
    map<int, int> valCount;
    node *traversal = head;
    node *dlt = NULL;
    
    while (traversal->next != NULL || traversal != NULL){
        if(valCount[traversal->next->data] == 0){
            valCount[traversal->next->data]++;    
        } else {
            dlt = traversal->next;
            traversal->next = traversal->next->next;
            delete dlt;
        }
        if(traversal->next == NULL)
            return head;
        else
            traversal = traversal->next;
    }

    return head;
}


int main()
{
    node *head = NULL;
    node *n = new node(0);
    head = n;
    head = n->addNode(head, 1);
    head = n->addNode(head, 2);
    head = n->addNode(head, 3);
    head = n->addNode(head, 2);
    head = n->addNode(head, 4);
    head = n->addNode(head, 2);
    head = n->addNode(head, 4);
    head = n->addNode(head, 2);
    n->printNodes();
    head = removeDuplicates(head);
    head = n->deleteNode(head, 4);
    head->printNodes();
    return 0;
}

