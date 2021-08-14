///////////////////////////////////////////////////////////
//  Main.cpp
//  CIS22C - Lab 0
//  Created on: 1/12/2017 
//  Student: Xu Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

//#include "LinkedList.cpp"

using namespace std;

///////////////////////////////////////////////////////////
//  LinkedList.cpp
//  Definition and implementation for LinkedList
//  Created on:1/20/2017
//  Student: Xu Tang
///////////////////////////////////////////////////////////

#ifndef _CIS22C_LINKEDLIST
#define _CIS22C_LINKEDLIST

// definition begin **********************************************************************************
// Node class
template <class T>
class Node
{
public:
    T title;
    T value;
    Node<T> *next;

    // Constructors
    Node()
    {
        next = nullptr;
    }

    Node(T aTitle, T val)
    {
        title = aTitle;
        value = val;
        next = nullptr;
    }
};


// Interface of LinkedList
template <class T>
class LinkedList
{
private:
    int count = 0;  // To count number of entries in the list
    Node<T> *head;

public:
    LinkedList();  // Constructor
    ~LinkedList(); // Destructor

    // Functions
    int getCurrentSize();   // Gets the current number of entries in the list
    bool isEmpty();         // Sees whether the list is empty
    void insert(T, T);      // Adds a new entry to the list
    bool remove(T);         // Removes one occurrence of a given entry fro m the list
    void clear();           // Removes all entries from the list
    bool contains(T);       // Tests whether the list contains the entry


    // Student added extra functions
    void insertAfter(T, T); // Add a new node after another
    void showList();        // Print all nodes
};
#endif
// definition end **********************************************************************************



// Implementation begin **********************************************************************************

// Constructor
template <class T>
LinkedList<T>::LinkedList()// Constructor inline
{
    head = nullptr;
}


// Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
    clear(); // Removes all entries from the list
}


// Gets the current number of entries in the list
template <class T>
int LinkedList<T>::getCurrentSize()
{
    return count;
}

// Sees whether the list is empty
template <class T>
bool LinkedList<T>::isEmpty()
{
    return getCurrentSize() == 0;
}


// Adds a new entry to the list
template <class T>
void LinkedList<T>::insert(T aTitle, T aValue)
{
    Node<T> *newNode;
    Node<T> *nodePtr;

    // allocate a new node to hold aValue
    newNode = new Node<T>(aTitle, aValue);


    if (!head)// If head is unused then hold newNode in head
    {
        head = newNode;
        count++;
        //cout << aValue << ":" << head->next << " is first node \n"; system("pause");
    }
    else
    {
        // Initialize nodePtr to head
        nodePtr = head;
        //cout << "Initialize nodePtr to head of list: " << nodePtr->next << endl; system("pause");

        // Loop to the last node
        while (nodePtr->next)
        {
            nodePtr = nodePtr->next;
        }


        // Add new node to the end of nodes
        nodePtr->next = newNode;
        count++;

        //cout << "New node: " << newNode << endl;
        //cout << "Prev node linked to :" << nodePtr->next << endl;
        //system("pause");
    }
}

// Removes one occurrence of a given entry fro m the list
template <class T>
bool LinkedList<T>::remove(T aTitle)
{
    // Instantiate node pointers
    Node<T> *nodePtr;
    Node<T> *previousNode;

    previousNode = new Node<T>();

    //cout << "remove: " << aTitle << endl;

    // If list is empty do nothing and return
    if (isEmpty())
    {
        //cout << "List is empty." << endl;
        return false;
    }

    if (head->title == aTitle)
    {
        nodePtr = head->next;   // if delete 1, then here is 2
        delete head;            // delete 1
        head = nodePtr;         // assign new head as 2
        count--;

        //cout << " found at head and deleted " << endl;
        return true;
    }
    else
    {
        // Initialize nodePtr to head
        nodePtr = head;

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
void LinkedList<T>::clear()
{
    // Instantiate pointers
    Node<T> *nodePtr;
    Node<T> *nextNode;

    // Initialize nodepointer to head
    nodePtr = head;

    // Looping to delele all nodes
    while (nodePtr != nullptr)
    {
        nextNode = nodePtr->next;
        //cout << "Going to delete " << nodePtr->title << endl;
        delete nodePtr;

        if (nextNode->next != nullptr)
        {
            nodePtr = nextNode;
        }
        else
        {
            nodePtr = nullptr;
        }

    }

    count = 0;
    head = nullptr;
}

// Tests whether the list contains the entry
template <class T>
bool LinkedList<T>::contains(T aTitle)
{
    // Instantiate pointers
    Node<T> *nodePtr;

    // Initialize nodepointer to head
    nodePtr = head;

    // Looping to search
    // According to book, the time complexity for searching linkedlist is O(n)
    while (nodePtr != nullptr)
    {
        if (nodePtr->title == aTitle)
        {
            //cout << aTitle << " found " << endl; system("pause");
            return true;
        }
        nodePtr = nodePtr->next;
    }

    return false;

}


// Add a new node after another
template <class T>
void LinkedList<T>::insertAfter(T targetValue, T aValue)
{
    Node<T> *newNode;
    Node<T> *nodePtr;
    Node<T> *previousNode = nullptr;


    //cout << "Insert a node " << aValue << "*****" << endl;

    newNode = new Node<T>(aValue);

    if (isEmpty())
    {
        head = newNode;
        newNode->next = nullptr;
    }
    else
    {
        // Point to head
        nodePtr = head;

        // Initialize
        previousNode = nullptr;

        // Looping to find target value
        while (nodePtr != nullptr && nodePtr->value == targetValue)
        {
            previousNode = nodePtr;
            nodePtr = nodePtr->next;
        }

        // At head
        if (previousNode == nullptr)
        {
            head = newNode;
            newNode->next = nodePtr;
        }
        else
        {
            previousNode->next = newNode;
            newNode->next = nodePtr;
        }
    }
}

// Print all nodes
template <class T>
void LinkedList<T>::showList()
{
    // Instantiat a nodepoint
    Node<T> *nodePtr;

    // initialize to head
    nodePtr = head;

    // Looping whole list
    while (nodePtr)
    {

        cout << setw(28) << left << nodePtr->title;

        cout << setw(10) << right << nodePtr->value << endl;

        nodePtr = nodePtr->next; // point to next
    }
}
// Implementation begin **********************************************************************************




string* csv2arr(string line)
{
    char delimiter = ',';
    const int SIZE = 2;
    string str, *ret = new string[SIZE];

    istringstream is(line); // Input string stream

    int i = 0;
    while (getline(is, str, delimiter))
    {
        //cout << str << endl;
        ret[i] = str;
        i++;
    }

    return ret;
}


void testImportDataFile()
{
    fstream datafile;
    string file = "UProducts.csv", line, *item;
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

        LinkedList<string> List;

        cout << "Going to import items from CSV file. ";
        system("pause");
        int row = 0;
        while (getline(datafile, line))
        {
            item = csv2arr(line); // parse csv string to array
            List.insert(item[TITLE_INDEX], item[VALUE_INDEX]);
            row++;
        }


        cout << "\t " << List.getCurrentSize() << " words imported." << endl;

        cout << "Going to display all imported items. ";
        system("pause");
        List.showList();


        cout << "Going to display size.";
        system("pause");
        cout << "\t Current size: " << List.getCurrentSize() << endl;

        string keyword = "Fruit";
        cout << "Going to find item with title '" << keyword << "' ";
        system("pause");
        string output = (List.contains(keyword) == true) ? "Found" : "Not existed";
        cout << "\t " << keyword << " " << output << endl;

        cout << "Going to delete " << keyword << " from list.";
        system("pause");
        List.remove(keyword);
        cout << keyword << " deleted. Going to display left items. ";
        system("pause");
        List.showList();


        cout << "Going to clear all node from list.";
        system("pause");
        List.clear();
        cout << "\t Current size: " << List.getCurrentSize() << endl;


    }
}



void main()
{
    // Show welcome message
    cout << "****************************************************************************" << endl;
    cout << "*                  Welcome to CIS22C-Lab 1                                 *" << endl;
    cout << "*                     Student: Xu Tang                                     *" << endl;
    cout << "*                                                                          *" << endl;
    cout << "*   This program will demonstrate followings:                              *" << endl;
    cout << "*   1. Convert the dynamic array class to be a linked list.                *" << endl;
    cout << "*   2. Convert the linked list class to handle generic types               *" << endl;
    cout << "*   3. Create a UDT to handle the data in the UProducts.CSV file           *" << endl;
    cout << "*   4. Read the data from the CSV file and store it in generic linked list *" << endl;
    cout << "*   5. Define a search routine to find a product in the linked list.       *" << endl;
    cout << "****************************************************************************" << endl;


    testImportDataFile();


    cout << "Going to close application. ";
    system("pause");
}

