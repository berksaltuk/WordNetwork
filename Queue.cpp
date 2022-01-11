/**
* Title : Queue Implementation
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : Implementation of Pointer Based Queue Class,
* In general this code is taken from the CS201 slides of previous semester.
*/
#include "Queue.h"

Queue::Queue() // Taken from slides only added size
{
    front = NULL;
    back = NULL;
    size = 0;
}

Queue::~Queue() //...
{

    while( !isEmpty())
    {
        dequeue();
    }
}

bool Queue::isEmpty() const //...
{
    return back == NULL;
}

bool Queue::enqueue(int newItem){ //...
    size++;
    // create a new node
    node *newPtr = new node;
    // set data portion of new node
    newPtr->item = newItem;
    newPtr->next = NULL;
    // insert the new node
    if (isEmpty()) // insertion into empty queue
        front = newPtr;
    else // insertion into nonempty queue
        back->next = newPtr;

    back = newPtr; // new node is at back
    return true;
}

bool Queue::dequeue(){ //...
    if (isEmpty())
        return false;
    else{
            size--;
    // queue is not empty; remove front
        node *tempPtr = front;
        if (front == back){ // special case
            front = NULL;
            back = NULL;
        }
        else
            front = front->next;

        tempPtr->next = NULL; // defensive strategy
        delete tempPtr;
        return true;
    }
}

bool Queue::getFront(int& queueFront)const { //...
    if (isEmpty())
        return false;
    else {
        // queue is not empty; retrieve front
        queueFront = front->item;
        return true;
    }
}

void Queue::display() // For testing purposes display added.
{
    node* cur = front;

    while( cur!= NULL)
    {
        cout << cur->item <<  " ";
        cur = cur->next;
    }
    cout << endl;
}
