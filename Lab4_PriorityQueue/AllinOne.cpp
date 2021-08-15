///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 4
//  Created on: 2/11/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#ifndef _DOUBLY_PriorityQueue
#define _DOUBLY_PriorityQueue

//#include <iostream>

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
    int count = 0; // To count number of entries in the list
    bool sorted = false;
    Node<T> *front;
    Node<T> *rear;

public:
    PriorityQueue();  // Constructor
    ~PriorityQueue(); // Destructor

    // Functions
    int getCurrentSize();                  // Gets the current number of entries in the list
    bool isEmpty();                        // Sees whether the list is empty
    void enqueue(T);                       // Adds a new entry to the list
    bool dequeue(T);                       // Removes one occurrence of a given entry fro m the list
    void clear();                          // Removes all entries from the list
    Node<T> *find(T);                      // Tests whether the list contains the entry
    void moveBefore(Node<T> *, Node<T> *); // Move node before another node

    // Student added extra functions
    void importDataFile();               // Import data file
    void showList(bool, Node<T> *, int); // Print all nodes

    // Sorting
    void swap(Node<T> *, Node<T> *);
    int bubbleSort();
    int selectionSort();
    int mergeSort(PriorityQueue<T> &S, int);
    void merge(PriorityQueue<T> &S1, PriorityQueue<T> &S2, PriorityQueue<T> &S);
    int quickSort(PriorityQueue<T> &S, int);

    friend void testImportDataFile();
    friend void main();
};
#endif
// definition end **********************************************************************************

//#include "PriorityQueue.h"

// Implementation begin **********************************************************************************

// Constructor
template <class T>
PriorityQueue<T>::PriorityQueue() // Constructor inline
{
    front = nullptr;
    rear = nullptr;
}

// Destructor
template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    clear(); // Removes all entries from the list
}

// Gets the current number of entries in the list
template <class T>
int PriorityQueue<T>::getCurrentSize()
{
    return count;
}

// Sees whether the list is empty
template <class T>
bool PriorityQueue<T>::isEmpty()
{
    return getCurrentSize() == 0;
}

// Move node to place before another node
template <class T>
void PriorityQueue<T>::moveBefore(Node<T> *nodePtr, Node<T> *targetPtr)
{
    // Handle target things
    nodePtr->prev->next = nodePtr->next;
    if (nodePtr->next)
    {
        nodePtr->next->prev = nodePtr->prev;
    }

    // Handle newNode
    if (targetPtr->title == front->title) // is front
    {
        targetPtr->prev = nodePtr;
        nodePtr->next = targetPtr;
        front = nodePtr;
    }
    else if (targetPtr->title == rear->title) // is rear
    {
        targetPtr->next = nodePtr;
        nodePtr->prev = targetPtr;
        rear = nodePtr;
    }
    else
    {
        nodePtr->prev = targetPtr->prev;
        targetPtr->prev->next = nodePtr;
        nodePtr->next = targetPtr;
        targetPtr->prev = nodePtr;
    }
}

// Adds a new entry to the list
template <class T>
void PriorityQueue<T>::enqueue(T aTitle)
{
    Node<T> *newNode;
    Node<T> *nodePtr;
    Node<T> *tempPtr;

    //cout << "(" << count << ") " << aTitle << endl;

    if (!front) // If front is unused then hold newNode in front
    {
        newNode = new Node<T>(aTitle); // allocate a new node to hold aValue

        //cout << newNode->freq; system("pause");
        front = newNode;
        rear = newNode;
    }
    else
    {
        // Check weaher new item already existed?
        if (nodePtr = find(aTitle)) // if new node already existed
        {
            //cout << "found: " << nodePtr->title << " with frequency " << front->freq << endl; system("pause");

            // then, increase its frequency
            nodePtr->freq = nodePtr->freq + 1;

            // then, find the first node that less than newNode
            tempPtr = front;
            while (tempPtr->freq > nodePtr->freq && tempPtr != NULL && tempPtr->title != nodePtr->title)
            {
                tempPtr = tempPtr->next;
            }

            // then, place newNode befor it
            if (tempPtr->title != nodePtr->title)
            {
                //cout << "place " << nodePtr->title << " before " << tempPtr->title << endl; system("pause");
                moveBefore(nodePtr, tempPtr);
            }
            //else
            //{
            //    cout << nodePtr->title << " doesn't need to replace " << endl; system("pause");
            //}
        }
        else // otherwise
        {
            newNode = new Node<T>(aTitle); // allocate a new node to hold aValue

            // Add new node to the end of list
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        //cout << "New node: " << newNode << endl;
        //cout << "Next node:" << newNode->next << endl;
        //cout << "Prev node:" << newNode->prev << endl;
        //system("pause");
    }

    count++;
}

// Removes one occurrence of a given entry fro m the list
template <class T>
bool PriorityQueue<T>::dequeue(T aTitle)
{
    // Instantiate node pointers
    Node<T> *nodePtr;
    Node<T> *previousNode;

    previousNode = new Node<T>;

    //cout << "remove: " << aTitle << endl;

    // If list is empty do nothing and return
    if (isEmpty())
    {
        //cout << "List is empty." << endl;
        return false;
    }

    if (front->title == aTitle)
    {
        nodePtr = front->next; // if delete 1, then here is 2
        delete front;          // delete 1
        nodePtr->prev = front;
        front = nodePtr; // assign new front as 2
        count--;

        //cout << " found at front and deleted " << endl;
        return true;
    }
    else
    {
        // Initialize nodePtr to front
        nodePtr = front;

        // Looping to find value till end of nodes
        while (nodePtr != nullptr && nodePtr->title != aTitle)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        //cout << "node: " << nodePtr->title << ": "<< nodePtr->next << endl;  system("pause");
        //nodePtr = nodePtr->next;
        //cout << "next node: " << nodePtr->title << ": " << nodePtr->next << endl;  system("pause");

        // If value found, then delete it
        if (nodePtr != nullptr)
        {

            //cout << " is not nullptr " << endl; system("pause");
            //cout << nodePtr->title << endl;
            //cout << nodePtr->next << endl;

            if (nodePtr->next == nullptr)
            {
                //cout << "is nullptr" << endl;

                //cout << "going to link previousnode to nullptr" << endl; system("pause");
                previousNode->next = nullptr;

                //cout << "going to delete node" << endl; system("pause");
                //delete[] nodePtr;

                count--;
                return true;
            }
            else
            {
                //cout << "is not nullptr" << endl;

                previousNode->next = nodePtr->next;
                delete[] nodePtr;
                count--;
                return true;
            }

            //system("pause");
        }
    }

    return false;
}

// Removes all entries from the list
template <class T>
void PriorityQueue<T>::clear()
{
    // Instantiate pointers
    Node<T> *nodePtr;
    Node<T> *nextNode;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to delele all nodes
    while (nodePtr != nullptr)
    {
        nextNode = nodePtr->next;

        //cout << "Going to delete " << nodePtr->title << endl;
        //cout << "next node:" << nextNode << endl; system("pause");

        if (nextNode)
        {
            delete nodePtr;
            nodePtr = nextNode;
        }
        else
        {
            delete nodePtr;
            nodePtr = nullptr;
        }
    }
    front = nullptr;
    rear = nullptr;

    count = 0;
}

// Tests whether the list contains the entry
template <class T>
Node<T> *PriorityQueue<T>::find(T aTitle)
{
    // Instantiate pointers
    Node<T> *nodePtr;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to search
    // According to book, the time complexity for searching PriorityQueue is O(n)
    while (nodePtr != nullptr)
    {
        if (nodePtr->title == aTitle)
        {
            //cout << aTitle << " found " << endl; system("pause");
            return nodePtr;
        }
        else
        {
            nodePtr = nodePtr->next;
        }
    }

    return false;
}

template <class T>
void PriorityQueue<T>::importDataFile()
{
    fstream datafile;
    string file = "Speech.txt", line;
    int TITLE_INDEX = 0, VALUE_INDEX = 1;

    datafile.open(file);
    if (datafile.fail())
    {
        cout << "Error: couldn't open the data file '" << file << "'." << endl;
        system("pause");
        exit(0);
    }
    else
    {
        int row = 0, strlength, count = 0;

        List.clear();
        while (getline(datafile, line))
        {
            strlength = line.length();
            for (int i = 0; i < strlength; i++)
            {
                // Only track ASCII between 32-128
                if (line[i] >= 32 || line[i] <= 128)
                {
                    count++;
                    //cout << line[i] << endl;
                    List.enqueue(line[i]);
                }
            }
        }
        List.sorted = false;

        cout << "\t " << List.getCurrentSize() << " characters imported." << endl; //system("pause");

        //cout << "Going to sort list. "; system("pause");
        //List.mergeSort(List, 0);
    }
}

// Print all nodes
template <class T>
void PriorityQueue<T>::showList(bool forward, Node<T> *nodePtr, int i = 0)
{
    i++;
    while (nodePtr)
    {
        cout << setw(8) << left << i;
        cout << setw(1) << left << nodePtr->title;
        cout << setw(10) << right << nodePtr->freq << endl;

        nodePtr = nodePtr->next;
    }
}

template <class T>
void PriorityQueue<T>::swap(Node<T> *u, Node<T> *v)
{
    T title = u->title;
    T freq = u->freq;

    u->title = v->title;
    u->freq = v->freq;

    v->title = title;
    v->freq = freq;
}

// Bubble Sort
// Find the largest, seconde largest..., put them to the end till all ended.
template <class T>
int PriorityQueue<T>::bubbleSort()
{
    int iterator_count = 0;

    Node<T> *nodePtr;
    //Node<T> * nextPtr;

    int todo = count - 1;
    //cout << "todo:" << todo << endl; system("pause");

    nodePtr = front;
    while (todo > 0)
    {
        iterator_count++;
        //cout << nodePtr->title << endl; system("pause");

        for (int i = 0; i < todo; i++)
        {
            iterator_count++;
            if (nodePtr->title > nodePtr->next->title)
            {
                //cout << "swap: " << nodePtr->title << " <-> " << nodePtr->next->title << endl;
                swap(nodePtr, nodePtr->next);
            }

            nodePtr = nodePtr->next;
        }

        nodePtr = front;
        todo--;
    }

    return iterator_count;
}

// Selection Sort - n^2
// Find the smallest, seconde smallest..., put them to the begin till all found.
template <class T>
int PriorityQueue<T>::selectionSort()
{
    Node<T> *nodePtr;
    Node<T> *smallest = front;
    int size = 1, j = 0;
    int iterator_count = 0;

    while (smallest)
    {
        iterator_count++;
        //cout << "smallest: " << smallest->title << endl;

        nodePtr = smallest->next;
        while (nodePtr)
        {
            iterator_count++;
            j++;

            //cout << "\t " << j << "/" << todo << " - node: " << nodePtr->title << endl;
            //cout << "\t compare: " << smallest->title << " <-> " << nodePtr->title << endl;
            //cout << "**********************" << endl;

            if (smallest->title > nodePtr->title)
            {
                //cout << "swap: " << smallest->title << " <-> " << nodePtr->title << endl;
                swap(nodePtr, smallest);
            }

            nodePtr = nodePtr->next;
        }

        smallest = smallest->next;
        size++;
        //system("pause");
    }

    return iterator_count;
}

// Merge Sort - O(n long n)
// divide-and-conquer
template <class T>
int PriorityQueue<T>::mergeSort(PriorityQueue<T> &S, int iterator_count)
{
    //typedef typename PriorityQueue<T>::iterator Itor; // sequence of elements
    //cout << "sort list "; system("pause");

    int n = S.count;
    int todo = 0;
    //cout << "n: " << n << endl;
    if (n <= 1)
    {
        return iterator_count; // already sorted or empty
    }

    PriorityQueue<T> S1, S2;
    //Itor p = S.begin();
    Node<T> *nodePtr = S.front;

    todo = n / 2;
    //cout << " S1: 0 - " << todo;  system("pause");
    for (int i = 0; (i < todo && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S1.push back(*p++); // copy first half to S1
        S1.enqueue(nodePtr->title);
        nodePtr = nodePtr->next;
    }
    //cout << "show S1: ";  S1.showList(true); system("pause");

    //cout << " S2: " << todo << " - " << n ;  system("pause");
    for (int i = todo; (i <= n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S2.push back(*p++); // copy second half to S2
        S2.enqueue(nodePtr->title, nodePtr->freq);
        nodePtr = nodePtr->next;
    }
    //cout << "show S2: ";  S2.showList(true); system("pause");

    iterator_count = mergeSort(S1, iterator_count); // recur on first half

    iterator_count = mergeSort(S2, iterator_count); // recur on second half

    S.clear();        // clear S��s contents
    merge(S1, S2, S); // merge S1 and S2 into S

    //cout << "show result: \n";  S.showList(true); system("pause");
    //cout << "iterator_count: " << iterator_count << " of " << count << "\n";

    return iterator_count;
}

template <typename T>
void PriorityQueue<T>::merge(PriorityQueue<T> &S1, PriorityQueue<T> &S2, PriorityQueue<T> &S)
{

    //typedef typename PriorityQueue<E>::iterator Itor; // sequence of elements
    //Itor p1 = S1.begin();
    //Itor p2 = S2.begin();

    Node<T> *nodePtr1 = S1.front;
    Node<T> *nodePtr2 = S2.front;

    // until either is empty
    while (nodePtr1 != nullptr && nodePtr2 != nullptr)
    {
        //cout << "compare: " << nodePtr1->title << " && " << nodePtr2->title << endl;

        if (nodePtr1->title < nodePtr2->title) // append smaller to S
        {
            //cout << "push: " << nodePtr1->title << endl;
            S.enqueue(nodePtr1->title, nodePtr1->freq);
            nodePtr1 = nodePtr1->next;
        }
        else
        {
            //cout << "push: " << nodePtr2->title << endl;
            S.enqueue(nodePtr2->title, nodePtr2->freq);
            nodePtr2 = nodePtr2->next;
        }
    }

    //cout << "push rest S1 ******************************" << endl;
    while (nodePtr1) // copy rest of S1 to S
    {
        S.enqueue(nodePtr1->title, nodePtr1->freq);
        //cout << "push: " << nodePtr1->title << nodePtr1->freq << endl;
        nodePtr1 = nodePtr1->next;
    }

    //cout << "push rest S2 ******************************" << endl;
    while (nodePtr2) // copy rest of S2 to S
    {
        S.enqueue(nodePtr2->title, nodePtr2->freq);
        //cout << "push: " << nodePtr2->title << nodePtr2->freq << endl;
        nodePtr2 = nodePtr2->next;
    }

    //cout << "end ------------------------ \n\n" << endl;
}

// QuickSort -- divide-and-conquer
// O(n log n)
template <typename T>
int PriorityQueue<T>::quickSort(PriorityQueue<T> &S, int iterator_count = 0)
{
    int n = S.count;
    int half = n / 2;

    if (n < 2)
    {
        //cout << "n < 2 then return " << endl;
        return iterator_count; // already sorted or empty
    }

    PriorityQueue<T> SL, SE, SG;

    // Delcare pivot
    //Node<T> * nodePtrPivot = S.rear; // Choose the last node to be pivot can increase running times if the linked list already sorted.
    Node<T> *nodePtrPivot = S.front;
    for (int x = 0; x < half; x++)
    {
        nodePtrPivot = nodePtrPivot->next;
    }
    SE.enqueue(nodePtrPivot->title, nodePtrPivot->freq);

    // Divide ********************
    // Separate nodes groups: less than pivot, equal to pivot, greater than pivot
    Node<T> *nodePtr = S.front;
    for (int i = 0; (i < n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        if (i != half)
        {
            //cout << iterator_count << endl;
            //cout << "compare: " << nodePtr->title << " AND " << nodePtrPivot->title << endl;
            if (nodePtr->title < nodePtrPivot->title)
            {
                SL.enqueue(nodePtr->title, nodePtr->freq);
                //cout << "\t push " << nodePtr->title << " to SL" << endl;
            }
            else if (nodePtr->title > nodePtrPivot->title)
            {
                SG.enqueue(nodePtr->title, nodePtr->freq);
                //cout << "\t push " << nodePtr->title << " to SG" << endl;
            }
            else
            {
                SE.enqueue(nodePtr->title, nodePtr->freq);
                //cout << "\t push " << nodePtr->title << " to SE" << endl;
            }
        }

        nodePtr = nodePtr->next;
    }
    //cout << "Divide END ---------------------------" << endl;
    //system("pause");

    // Recur ********************
    iterator_count = quickSort(SL, iterator_count);
    iterator_count = quickSort(SG, iterator_count);

    // Conquer ********************
    S.clear();
    nodePtr = SL.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->title, nodePtr->freq);
        //cout << "\t push SL: " << nodePtr->title << " to S" << endl;
        nodePtr = nodePtr->next;
    }

    nodePtr = SE.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->title, nodePtr->freq);
        //cout << "\t push SE: " << nodePtr->title << " to S" << endl;
        nodePtr = nodePtr->next;
    }

    nodePtr = SG.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->title, nodePtr->freq);
        //cout << "\t push SG: " << nodePtr->title << " to S" << endl;
        nodePtr = nodePtr->next;
    }

    SL.clear();
    SE.clear();
    SG.clear();
    //cout << "END --------------------------------------------------------\n\n\n" << endl;
    return iterator_count;
}
// Implementation begin **********************************************************************************

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                                   Welcome to Lab 4                                           *" << endl;
    cout << "*                                 Student: Robert Tang                                         *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Create a ADT to read the Speech.txt file in this week's document folder.                  *" << endl;
    cout << "*  + Store each character in the Doubly Linked PriorityQueue and increment it's frequency      *" << endl;
    cout << "*    every time it's encountered in the file.                                                  *" << endl;
    cout << "*  + When finished processing the file, print the PriorityQueue and you should see the         *" << endl;
    cout << "*    frequency in order from highest to lowest.                                                *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Import Data                                                                              *" << endl;
    cout << "*  2) Print list                                                                               *" << endl;
    cout << "*  3) Get current size                                                                         *" << endl;
    cout << "************************************************************************************************" << endl;
}

PriorityQueue<char> List;

void main()
{

    int input;
    Node<char> *nodePtr;
    List.importDataFile();
    nodePtr = List.front;
    List.showList(true, nodePtr, 0); // fordwards
    system("pause");

    system("cls");
    menu(); // Show welcome message

    do
    {
        cout << "Please enter your choice [0-4]:";
        cin >> input;
        switch (input)
        {
        case 1:
            List.importDataFile();
            break;

        case 2:
            nodePtr = List.front;
            List.showList(true, nodePtr, 0); // fordwards
            system("pause");
            system("cls");
            menu();
            break;

        case 3:
            cout << "Size:" << List.getCurrentSize() << endl;
            break;
        }

        //system("cls");
    } while (input != 0);

    //testImportDataFile();

    cout << "Going to close application. ";
    system("pause");
}
