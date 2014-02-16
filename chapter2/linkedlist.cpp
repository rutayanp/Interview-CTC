#include <iostream>
#include <stdlib.h>

using namespace std;

class node{
    int data;
    node *next;
    
public:
    node(int d){
        data = d;
        next = NULL;
    }
    
    node *addNode(node *head, int d)
    {
        node *end = new node(d);
        node *traverse = head;
        while(traverse->next != NULL){
            traverse = traverse->next;
        }

        traverse->next = end;
        return head;    
    } 

    node *deleteNode(node *head, int d)
    {
        node *dlt = NULL;
        node *traverse = head;
        if(traverse->data == d){
            dlt = traverse;
            head = traverse->next;
            delete dlt;
            return head;
        }
        
        while(traverse->next != NULL){
            if(traverse->next->data == d){
                dlt = traverse->next;
                traverse->next = traverse->next->next;
                delete dlt;
                return head;
            }
            traverse = traverse->next;
        }
            
        return head;
    }

    void printNodes(){
        node *traverse = this;
        cout << "list : ";
        while(traverse != NULL){
            cout << traverse->data << "->";
            traverse = traverse->next;
        }
        cout << endl;
    }

    friend node *removeDuplicates(node *head);
};

/*
int main()
{
    node *head = NULL;
    node *n = new node(0);
    head = n;
    head = n->addNode(head, 1);
    head = n->addNode(head, 2);
    head = n->addNode(head, 3);
    head = n->addNode(head, 4);
    n->printNodes();
    head = n->deleteNode(head, 0);
    head->printNodes();
    return 0;
}*/
