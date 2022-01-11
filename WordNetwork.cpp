/**
* Title : WordNetwork Implementation
* Author : Berk Saltuk Yýlmaz
* ID: 21903419
* Section : 3
* Assignment : 4
* Description : This is the implementation of WordNetwork by Donald Knuth.
* Detailed information and comments can be found inside the code.
*/
#include "WordNetwork.h"
#include <fstream>

WordNetwork::WordNetwork(const string vertexFile , const string edgeFile)
{
    tableSize = 101; // Table size is choosen as a prime num to have a more equally distributed hash Table.
    string fileName = vertexFile; // Taking the filename

    ifstream inputFile;

    string vertex;


    hashList = new List[tableSize]; // hash Table created

    nodeNo = 0; // Nodes are starting by 0 to 5756

    //Open the stream for the input file
    inputFile.open( fileName.c_str(), ios_base::in );


    while( inputFile >> vertex) // Reading until the end of first txt file
    {

        int index = hashFunction3(vertex, tableSize); // Getting the index for current node
        hashList[index].addToTail(vertex, nodeNo); // Adding the node to the appropriate index
        nodeNo++; // increasing nodeNo;

    }
    inputFile.close();


    adjMat = new int*[nodeNo]; // Creating the adjacency matrix (2D)
    for(int i = 0; i < nodeNo; i++)
    {
        adjMat[i] = new int[nodeNo];
    }

    for( int a = 0; a < nodeNo; a++) // Initializing each index to 0.
    {
        for( int b = 0; b < nodeNo; b++)
        {
            adjMat[a][b] = 0;
        }
    }

    ifstream inputFile2;
    string source, destination;
    string fileName2 = edgeFile;
    inputFile2.open( fileName2.c_str(), ios_base::in );

    string get;
    while ( getline(inputFile2, get)) {
        //Read until a comma
        source = get.substr(0,5); // get the first vertex
        int indexS = hashFunction3(source, tableSize); // find its index from hash table
        int adj1 = hashList[indexS].retrieveIndex(source); // retrieving the index of vertex

        destination = get.substr(6,5); // same as above
        int indexD = hashFunction3(destination, tableSize);
        int adj2 = hashList[indexD].retrieveIndex(destination);

        adjMat[adj1][adj2] = 1; // setting this index to 1
        adjMat[adj2][adj1] = 1; // and its symmetric index to 1

    }

    inputFile2.close();


}

WordNetwork::~WordNetwork()
{

    for (int i = 0; i < nodeNo; i++) // Deleting the matrix
    {
        delete[] adjMat[i];

    }
    delete[] adjMat;


    delete [] hashList; // Deleting the list
}

void WordNetwork::listNeighbors ( const string word )
{
    int index = hashFunction3(word, tableSize);
    int row = hashList[index].retrieveIndex(word); // Getting the row of the adjacency matrix

    if( row == -1) // If row does not exist display a warning message
    {
        cout << "This word does not exist in the graph." << endl;
        return;
    }
    cout << "Neighbors of " << word << ": " << endl;

    for(int i = 0; i < nodeNo; i++)
    {

        if( adjMat[row][i] == 1) // Finding all neighbors and display them
        {

            cout << findByIndex(i) << endl;
        }
    }
    cout << endl;
}

void WordNetwork::listNeighbors ( const string word , const int distance )
{


    int index = hashFunction3(word, tableSize);
    int row = hashList[index].retrieveIndex(word); // Finding the row num of adjacency matrix

    if( row == -1) // If this word is not exist display a warning.
    {
        cout << "This word does not exist in the graph." << endl;
        return;
    }
    bool *visited = new bool[nodeNo];
    for(int i = 0; i < nodeNo; i++) // A bool array to keep track of visited nodes.
    {
        visited[i] = false;
    }
    cout << "Neighbors of " << word << " within a distance " << distance << ":" << endl;

    listNeighborsRecursive(row, distance, visited); // calling the recursive list neighbors method with given distance
    cout << endl;

    delete [] visited; // deallocate...
}


void WordNetwork::listConnectedComponents()
{
    bool *visited = new bool[nodeNo]; // A bool array to keep track of visited nodes.
    for(int i = 0; i< nodeNo; i++)
    {
        visited[i] = false;
    }
    int counter = 1; // counter for display purposes
    for( int i = 0; i < nodeNo; i++)
    {
        if( visited[i] == false) // For every unvisited node I will find the neighbors at any distance
        {
            bool flag = false;
            for(int j = 0; j < nodeNo; j ++)
            {
                if( adjMat[i][j] == 1 && visited[j] == false)
                {
                    flag = true; // this flag is indicating whether the given node has a neighbor
                }
            }
            if( flag ) // If this node has neighbors list them
            {
                cout << "Connected component " << counter++ << ":" <<endl;
                listNeighborsRecursive(i, nodeNo, visited); // here calling the function with max distance = nodeNo
                cout << endl;
            }

        }

    }
    delete [] visited; // deallocate...
}

void WordNetwork::findShortestPath ( const string word1 , const string word2 )
{
    int indexFirst = hashFunction3(word1, tableSize);
    int indexLast = hashFunction3(word2, tableSize); // finding the index of first word

    int startingVertex = hashList[indexFirst].retrieveIndex(word1);
    int destinationVertex = hashList[indexLast].retrieveIndex(word2); // finding the index of first word

    if( startingVertex == -1 || destinationVertex == -1 )
    {
        cout << "Some of the words does not exist. "<<endl;
        return;
    }

    int *nodes = new int[nodeNo]; // an integer array to keep the track of "parent" nodes
    for( int i =0 ; i < nodeNo; i++)
    {
       nodes[i] = 0;
    }
    BFS(startingVertex, nodes); // Calling breadth first search
    cout << "Shortest path from " << word1 << " to " << word2 << ":" <<endl;
    findPath( startingVertex, destinationVertex, nodes); // calling the function that displays path

    delete [] nodes; // deallocate...
}


int WordNetwork::hashFunction3(string key, int tableSize) // Hash function for string from the slides
{
    int hashVal = 0;
    for (long long unsigned i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];

    hashVal %=tableSize;

    if (hashVal < 0)
        hashVal += tableSize;

    return hashVal;
}

string WordNetwork::findByIndex(int index) // Finding the corresponding vertex by the given index
{
    string s;
    for( int i = 0; i < tableSize; i++)
    {

        if(hashList[i].contains(index, s))
        {
            return s; // Traverses all list and finds corresponding vertex
        }
    }

    return NULL; // not exist
}

int WordNetwork::findByWord(string str) // Doing the opposite of function above, I did not use this this was here for testing purposes
{
    int index;
    for( int i = 0; i < tableSize; i++)
    {
        if( hashList[i].contains2(str, index))
        {
            return index;
        }
    }

    return -1;
}

void WordNetwork::BFS(int startingVertex, int *arr)
{
// Breadth first search I have implemented by the pseudo code on the slides with slight differences
    Queue q;
    bool *visited = new bool[nodeNo]; // Keeping the track of visited nodes

    for( int i =0 ; i < nodeNo; i++)
    {
        visited[i] = false;
    }

    q.enqueue(startingVertex);
    visited[startingVertex] = true;

    while( !q.isEmpty())
    {
        int adjacent = 0;
        q.getFront(adjacent);
        q.dequeue();


        for(int i = 0; i < nodeNo; i++)
        {
            if( (adjMat[adjacent][i] == 1 )&& visited[i] == false)
            {

                visited[i] = true;
                q.enqueue(i);
                arr[i] = adjacent; // I am inserting the previous node to the index of current node in this way I am keeping the track of parent or previous nodes

            }
        }

    }

    delete [] visited; // deallocate...

}

void WordNetwork::findPath( int startingVertex, int lastVertex, int *previous)
{
    Queue q; // Using a queue to keep the indexes temporarily

    for( int i = lastVertex; i > 0; i = previous[i]) // each time next index will be the parent of starting node, when I have arrive the first node I will stop
    {
        q.enqueue(i); // Starting from ending vertex, backtracking the initial node
    }

    if( q.isEmpty())
    {
        cout << "There is no path from " << findByIndex(startingVertex) << " to " << findByIndex(lastVertex)<< "..." << endl; // If empty display a warning
        return;
    }

    int pathSize = q.getLength();
    int *path = new int[pathSize]; // Initializing an array to reverse the elements in the queue
    for(int i = 0; i < pathSize; i++)
    {
        path[i] = 0;
    }
    int cnt = 0;
    while(!q.isEmpty()) // Placing the elements of the queue to the array starting from the last index.
    {
        int add;
        q.getFront(add);

        path[ pathSize - 1 - cnt] = add;
        cnt++;
        q.dequeue();
    }

    for( int i = 0; i < pathSize; i++) // Displaying each elements within this path
    {
        cout << findByIndex(path[i]) <<endl;
    }

    delete [] path; // Deallocate...
}

void WordNetwork::listNeighborsRecursive( int row, int curDis, bool *arr)
{

    if( curDis == 0) // if all elements in given distance printed time to return
    {
        return;
    }

    for(int i = 0; i < nodeNo; i++)
    {
        if( adjMat[row][i] == 1 && !arr[i]) // recursively calling this function to find all neighbors
        {
            arr[i] = true;
            cout << findByIndex(i) << endl; // marking as visited, printing the node and calling the same function for its neighbors
            listNeighborsRecursive(i, curDis - 1, arr);
        }
    }
}


