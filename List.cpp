/**
* Title : List Implementation
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : Implementation of Pointer Based LinkedList class. I basically modified
* the codes from the slides as I needed.
*/
#include "List.h"

List::List() //...
{
    head = NULL;
    size = 0;
}

List::~List() //...
{

    while( !isEmpty())
    {
        remove();
    }
}

void List::addToTail(string vertex, int index) // Adding to tail but only difference it takes string and integer
{
    size++;
    vertexNode *newNode = new vertexNode;
    newNode->vertex = vertex;
    newNode->index = index;
    newNode->next = NULL;

    if( head==NULL)
    {
        head = newNode;
    }
    else
    {
        vertexNode *cur = head;
        while( cur->next != NULL)
        {
            cur=cur->next;
        }
        cur->next = newNode;
    }

}

void List::remove() //...
{
    size--;
    vertexNode* current = head;
    head = head->next;
    delete current;

}

bool List::isEmpty() //...
{
    return size == 0;
}

int List::retrieveIndex(string vertex) // Vertex is given and its index is retrieved
{
    vertexNode *cur = head;
    while( cur != NULL)
    {

        if( cur->vertex.compare(vertex) == 0) // If vertices are equal get the index of same node
        {
            return cur->index;
        }
        cur = cur->next;
    }

    return -1;
}

string List::retrieveWord(int index) // Index of a vertex is given and vertex returned
{
    vertexNode *cur = head;
    while( cur != NULL)
    {
        if( cur->index == index)
        {

            return cur->vertex;
        }
        cur = cur->next;
    }

    return NULL;
}

bool List::contains( int index, string &retrieve) // Index is given to a list and this function checks if a vertex with this index exists, and also retrieves vertex.
{
    vertexNode *cur = head;
    while( cur != NULL)
    {
        if( cur->index == index)
        {
            retrieve = cur->vertex;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool List::contains2( string str, int &indexGet) // String is given to a list and this function checks if an index corresponds to the vertex also retrieves index.
{
    vertexNode *cur = head;
    while( cur != NULL)
    {
        if( cur->vertex == str)
        {
            indexGet = cur->index;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void List::display() // Display function for testing purposes
{
    vertexNode* cur = head;
    while( cur!=NULL)
    {
        cout << cur->vertex << ", " << cur->index << " | ";
        cur=cur->next;
    }
    cout << endl;
    cout << "size of this bucket : " << size << endl;
}
