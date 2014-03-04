#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"

using namespace std;

node *findkth(node *head, int k)
{
    node *runner = head;
    node *traverse = head;

    for(int i = 0; i < k - 1; i++){
        if(runner == NULL) return NULL;
        runner = runner->next;
    }
    
    if(runner->next == NULL) return NULL;

    while(runner->next != NULL){
        runner = runner->next;
        traverse = traverse->next;
    }

    return traverse;
}

int main()
{
    node *head = NULL;
    node *n = new node(0);
    head = n;
    head = n->addNode(head, 1); 
    head = n->addNode(head, 2); 
    head = n->addNode(head, 3); 
    head = n->addNode(head, 4); 
    head = n->addNode(head, 5); 
    head = n->addNode(head, 6); 
    head = n->addNode(head, 7); 
    head = n->addNode(head, 8); 
    head->printNodes();
    cout << "3rd : " << findkth(head, 3)->data << endl;
    head->printNodes();
    return 0;
}
