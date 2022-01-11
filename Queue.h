/**
* Title : Queue Header File
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : Function prototypes for Pointer Based Queue.
*/
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using namespace std;

class Queue
{
    public:
        Queue();
        ~Queue();
        bool isEmpty() const;
        bool enqueue(int newItem);
        bool dequeue();
        bool getFront(int &frontItem) const;
        void display();
        int getLength()
        {
            return size;
        }
    private:
        struct node
        {
            int item;
            node *next;
        };

        int size;
        node *front;
        node *back;
};

#endif // QUEUE_H
