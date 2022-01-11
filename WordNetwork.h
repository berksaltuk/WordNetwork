#ifndef WORDNETWORK_H
#define WORDNETWORK_H
/**
* Title : WordNetwork Header File
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : This header file contains function prototypes given in the assignment and additional
* member functions I added. This prototype also contains a 2D Array will be used as Adjacency matrix and a
* array of LinkedLists to accomplish Separate Chaining.
*/
#include <iostream>
#include "List.h"
#include "Queue.h"

using namespace std;

class WordNetwork {
    public :

    WordNetwork ( const string vertexFile , const string edgeFile );
    ~WordNetwork () ;

    void listNeighbors ( const string word ) ;

    void listNeighbors ( const string word , const int distance );

    void listConnectedComponents () ;

    void findShortestPath ( const string word1 , const string word2 ) ;


    private:
    int hashFunction3(string key, int tableSize);

    int nodeNo;  // 2D array for Adjacency Matrix representation
    int **adjMat;

    int tableSize; // Array of Lists for Separate Chaining
    List *hashList;

    //Additional Functions
    string findByIndex(int index);
    void BFS(int startingVertex, int *arr);
    void listNeighborsRecursive( int i, int curDis, bool *arr);
    void findPath( int startingVertex, int lastVertex, int *previous);
    int findByWord(string str);

};

#endif // WORDNETWORK_H
