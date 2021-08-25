///////////////////////////////////////////////////////////
//  stack.cpp
//  Definition and implementation of Stack
//  Student: Robert Tang
///////////////////////////////////////////////////////////

#include "stack.h"
using namespace std;

// Implementation begin **********************************************************************************
// Constructor
template <class T>
Stack<T>::Stack() // Constructor inline
{
    head = nullptr;
}

// Destructor
template <class T>
Stack<T>::~Stack()
{
    clear(); // Removes all entries from the list
}

// Return a reference to the top element on the stack
// without removing it; an error occurs if the stack
// is empty.
template <class T>
Node<T> *Stack<T>::top()
{
    return head;
}

// Adds a new entry to the list
template <class T>
void Stack<T>::push(T aValue)
{
    // Instantiate a new node and holds aValue
    Node<T> *newNode = new Node<T>(aValue);

    newNode->prev = head;
    head = newNode;
    count++;
}

// Removes one occurrence of a given entry fro m the list
template <class T>
T Stack<T>::pop()
{
    if (head != nullptr)
    {
        T ret;

        // Instantiate node pointers
        Node<T> *nodePtr;
        nodePtr = head->prev;

        ret = head->value;
        //cout << "goint to return: " << head->value << ":" << ret << endl;

        delete head;
        head = nodePtr;
        count--;

        return ret;
    }
    else
    {
        throw StackException("ERROR: stack is empty");
    }
}

// Removes all entries from the list
template <class T>
void Stack<T>::clear()
{
    for (int i = 0; i < count; i++)
    {
        pop();
    }
}

// Gets the current number of entries in the list
template <class T>
int Stack<T>::getCurrentSize()
{
    return count;
}

// Sees whether the list is empty
template <class T>
bool Stack<T>::isEmpty()
{
    return getCurrentSize() == 0;
}

// Print all nodes
template <class T>
void Stack<T>::showList()
{
    // Instantiat a nodepoint
    Node<T> *nodePtr;

    // initialize to top
    nodePtr = top();

    // Looping whole list
    cout << "list:" << endl;
    while (nodePtr != nullptr)
    {

        cout << setw(28) << left << nodePtr->value << endl;
        nodePtr = nodePtr->prev; // point to previous node
    }
}

// Get value of top node
template <class T>
T Stack<T>::getTopValue()
{
    if (head != nullptr)
    {
        return head->value;
    }
    else
    {
        throw StackException("ERROR: stack is empty");
    }
}
// Implementation end **********************************************************************************
