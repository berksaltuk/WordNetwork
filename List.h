/**
* Title : List Header File
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : Function Prototypes for LinkedList Class
*/
#ifndef LIST_H
#define LIST_H
#include <iostream>
using namespace std;

class List
{
    public:
        List();
        ~List();

        int getSize();
        void addToTail(string vertex, int index);
        void remove();
        bool isEmpty();

        int retrieveIndex(string vertex);
        string retrieveWord(int index);
        bool contains(int index, string &retrieve);
        void display();
        bool contains2( string str, int &indexGet);
    private:
        struct vertexNode // Nodes are keeping a string and an integer.
        {
            string vertex;
            int index;
            vertexNode *next;
        };

        vertexNode *head;
        int size;

        friend class WordNetwork; // To access private data members defined WordNetwork as friend class
};

#endif // LIST_H
