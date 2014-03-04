#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"
#include <stack>

using namespace std;

bool isPalindrom(node *head)
{
    node *fast = head;
    node *slow = head;
    
    stack<int> mystack;
    while(fast != NULL && fast->next != NULL){
        mystack.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;
    }

    if(fast != NULL){
        slow = slow->next;
    }

    while(slow != NULL){
        if(slow->data != mystack.top())
            return false;
        mystack.pop();
        slow = slow->next;
    }

    return true;
}

int main()
{
    node *head = NULL;
    node *n = new node(0);
    head = n;
    head = n->addNode(head, 1);
    head = n->addNode(head, 2);
    //head = n->addNode(head, 3);
    head = n->addNode(head, 2);
    head = n->addNode(head, 1);
    head = n->addNode(head, 1);
   // head = n->addNode(head, 4);
   // head = n->addNode(head, 2);
    n->printNodes();
   // head = removeDuplicates(head);
   // head = n->deleteNode(head, 4);
   // head->printNodes();
    return isPalindrom(head);
}

