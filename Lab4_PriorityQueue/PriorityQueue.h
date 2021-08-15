
#ifndef _CIS22C_DOUBLY_PriorityQueue
#define _CIS22C_DOUBLY_PriorityQueue

#include <iostream>

// definition begin **********************************************************************************
// Node class
template <class T>
class Node
{

public:
    T title;
    int freq;

    Node<T> *next;
    Node<T> *prev;

    // Constructors
    Node()
    {
        next = nullptr;
        prev = nullptr;
    }

    Node(T aTitle)
    {
        title = aTitle;
        freq = 1;

        next = nullptr;
        prev = nullptr;
    }
};


// Interface of PriorityQueue
template <class T>
class PriorityQueue
{
private:
    int count = 0;  // To count number of entries in the list
    bool sorted = false;
    Node<T> *front;
    Node<T> *rear;

public:
    PriorityQueue();  // Constructor
    ~PriorityQueue(); // Destructor

    // Functions
    int getCurrentSize();   // Gets the current number of entries in the list
    bool isEmpty();         // Sees whether the list is empty
    void enqueue(T);        // Adds a new entry to the list
    bool dequeue(T);        // Removes one occurrence of a given entry fro m the list
    void clear();           // Removes all entries from the list
    Node<T> * find(T);      // Tests whether the list contains the entry
    void moveBefore(Node<T> *, Node<T> *);  // Move node before another node


    // Student added extra functions
    void importDataFile();  // Import data file
    void showList(bool, Node<T> *, int);        // Print all nodes

    // Sorting
    void swap(Node<T> *, Node<T> *);
    int bubbleSort();
    int selectionSort();
    int mergeSort(PriorityQueue<T>& S, int);
    void merge(PriorityQueue<T>& S1, PriorityQueue<T>& S2, PriorityQueue<T>& S);
    int quickSort(PriorityQueue<T>& S, int);

    friend void testImportDataFile();
    friend void main();
};
#endif
// definition end **********************************************************************************

