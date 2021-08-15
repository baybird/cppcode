#ifndef _CIS22C_STACK
#define _CIS22C_STACK

#include <string>

using namespace std;

// definition begin **********************************************************************************
class StackException{
private:
    string error;

public:
    StackException(const string& err){
        error = err;
    }

    string getMessage() const 
    { 
        return error; 
    }
};


// Node class
template <class T>
class Node
{
public:
    T value;
    Node<T> *prev;

    // Constructors
    Node()
    {
        prev = nullptr;
    }

    Node(T val)
    {
        value = val;
        prev = nullptr;
    }

};


// Interface of Stack
template <class T>
class Stack
{
private:
    int count = 0;  // To count number of entries in the list
    Node<T> *head;

public:
    Stack();  // Constructor
    ~Stack(); // Destructor

    // Functions
    void push(T);       // Insert element e at the top of the stack.
    T pop();        // Remove the top element from the stack; an error occurs if the stack is empty.
    Node<T> * top();    // Return a reference to the top element on the stack, without removing it; an error occurs if the stack is empty.

    // Supporting functions :
    int getCurrentSize();   // Gets the current number of entries in the list
    bool isEmpty();         // Sees whether the list is empty
    void clear();           // Removes all entries from the list
    void showList();        // Print all nodes
    T getTopValue();        // Get value of top node


};
#endif
// definition end **********************************************************************************
