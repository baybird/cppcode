
#ifndef _DOUBLY_LINKEDLIST
#define _DOUBLY_LINKEDLIST

#include <iostream>

// definition begin **********************************************************************************
// Node class
template <class T>
class Node
{
public:
    T title;
    T value;
    Node<T> *next;
    Node<T> *prev;

    // Constructors
    Node()
    {
        next = nullptr;
        prev = nullptr;
    }

    Node(T aTitle, T val)
    {
        title = aTitle;
        value = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Interface of LinkedList
template <class T>
class LinkedList
{
private:
    int count = 0; // To count number of entries in the list
    bool sorted = false;
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList();  // Constructor
    ~LinkedList(); // Destructor

    // Functions
    int getCurrentSize(); // Gets the current number of entries in the list
    bool isEmpty();       // Sees whether the list is empty
    void insert(T, T);    // Adds a new entry to the list
    bool remove(T);       // Removes one occurrence of a given entry fro m the list
    void clear();         // Removes all entries from the list
    bool contains(T);     // Tests whether the list contains the entry

    // Student added extra functions
    void insertAfter(T, T);              // Add a new node after another
    void importDataFile();               // Import data file
    void showList(bool, Node<T> *, int); // Print all nodes

    // Sorting
    void swap(Node<T> *, Node<T> *);
    int bubbleSort();
    int selectionSort();
    int mergeSort(LinkedList<T> &S, int);
    void merge(LinkedList<T> &S1, LinkedList<T> &S2, LinkedList<T> &S);
    int quickSort(LinkedList<T> &S, int);

    friend void testImportDataFile();
    friend void main();
};
#endif
// definition end **********************************************************************************
