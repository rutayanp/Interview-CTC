#include <iostream>
#include <stdlib.h>
#include "linkedlist.cpp"

using namespace std;

class result {
public:    
    node *mirror;
    bool is_equal;

    result(node *next, bool res)
    {
        mirror = next;
        is_equal = res;
    }
    
    result()
    {
        mirror = NULL;
        is_equal = false;
    }
};

int length(node *head)
{
    int len = 0;
    node *traverse = head;

    while (traverse != NULL){
        traverse = traverse->next;
        len++;
    }

    return len;
}

result *isPalindromRec(node *head, int len)
{
    if ( head == NULL){
        return new result();
    } else if(len == 1){
        result *res = new result(head->next, 1);
        return res;
    } else if(len == 2){
        result *res = new result(head->next->next, head->data == head->next->data);
        return res;
    }

    result *res = isPalindromRec(head->next, len - 2);

    if(!res->is_equal || res == NULL){
        return res;
    } else {
        res->is_equal = (head->data == res->mirror->data);
        res->mirror = res->mirror->next;
        return res;
    }

    return new result(head, true);
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
    head = n->addNode(head, 0);
    head = n->addNode(head, 0);
    n->printNodes();
    return isPalindromRec(head, length(head))->is_equal;
}

