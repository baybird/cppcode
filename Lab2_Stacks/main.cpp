///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 2
//  Student: Robert Tang
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctype.h>

//#include "stack.cpp"

using namespace std;

#ifndef _STACK
#define _STACK

// definition begin **********************************************************************************
class StackException
{
private:
    string error;

public:
    StackException(const string &err)
    {
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
    int count = 0; // To count number of entries in the list
    Node<T> *head;

public:
    Stack();  // Constructor
    ~Stack(); // Destructor

    // Functions
    void push(T);   // Insert element e at the top of the stack.
    T pop();        // Remove the top element from the stack; an error occurs if the stack is empty.
    Node<T> *top(); // Return a reference to the top element on the stack, without removing it; an error occurs if the stack is empty.

    // Supporting functions :
    int getCurrentSize(); // Gets the current number of entries in the list
    bool isEmpty();       // Sees whether the list is empty
    void clear();         // Removes all entries from the list
    void showList();      // Print all nodes
    T getTopValue();      // Get value of top node
};
#endif
// definition end **********************************************************************************

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

void testStack()
{
    Stack<int> intStack;
    for (int i = 0; i < 10; i++)
    {
        intStack.push(i);
    }

    intStack.showList();

    for (int i = 0; i < 10; i++)
    {
        intStack.pop();
        cout << "pop " << endl;
        intStack.showList();
        system("pause");
    }
}

double evaluatePostfix(string input)
{
    double result;

    int size = input.size();
    int last = size - 1;
    if (size > 0)
    {
        Stack<double> intStack;
        for (int i = 0; i < size; i++)
        {
            //cout << input[i] << endl;

            if (isdigit(input[i])) // If is a integer push to stack
            {
                // if last element is a integer, throw an exception
                if (i == last)
                {
                    throw StackException(input + "\t Error: last element is not a operator.");
                }
                else
                {
                    int num = input[i] - '0';
                    intStack.push(num);
                }
            }
            else // otherwise
            {

                double numA, numB;
                numB = intStack.pop();
                numA = intStack.pop();

                if (input[i] == '+')
                {
                    result = (double)numA + numB;
                    intStack.push(result);
                }
                else if (input[i] == '-')
                {
                    result = (double)numA - numB;
                    intStack.push(result);
                }
                else if (input[i] == '*')
                {
                    result = (double)numA * numB;
                    intStack.push(result);
                }
                else if (input[i] == '/')
                {
                    result = (double)numA / numB;
                    intStack.push(result);
                }
                else
                {
                    throw StackException("Error: unknown input. Only accept intger and operator: +,-,*,/. ");
                }

                //cout << numA << input[i] << numB << "= " << result << endl;
                //system("pause");
            }
        }
    }

    return result;
}

string convertPostfix2Infix(string input)
{
    string result;
    string open_tag = "(", closing_tag = ")";
    string numA, numB;

    int pop_two = true; // Indicate pop two elements if is true, otherwise pop one
    int size = input.size();
    int last = size - 1;
    if (size > 0)
    {
        Stack<string> strResultStack;
        for (int i = 0; i < size; i++)
        {
            //cout << input[i] << endl;

            if (isdigit(input[i])) // If is a integer push to stack
            {
                // if last element is a integer, throw an exception
                if (i == last)
                {
                    throw StackException(input + " Error: last element is not a operator.");
                }
                else
                {
                    string num = string(1, input[i]);
                    strResultStack.push(num);
                }
            }
            else // otherwise
            {
                //cout << numB << input[i] << numA << endl;
                //system("pause");
                numB = strResultStack.pop();
                numA = strResultStack.pop();

                // If is last element, then do not encapsulate
                if (i == size - 1)
                {
                    open_tag = "";
                    closing_tag = "";
                }
                else
                {
                    open_tag = "(";
                    closing_tag = ")";
                }

                if (input[i] == '+')
                {
                    result = open_tag + numA + "+" + numB + closing_tag;
                }
                else if (input[i] == '-')
                {
                    result = open_tag + numA + "-" + numB + closing_tag;
                }
                else if (input[i] == '*')
                {
                    result = open_tag + numA + "*" + numB + closing_tag;
                }
                else if (input[i] == '/')
                {
                    result = open_tag + numA + "/" + numB + closing_tag;
                }

                if (i < size - 1)
                {
                    //cout << result << endl;
                    strResultStack.push(result);
                }
            }
        }
    }

    return result;
}

bool precedence(string a, string b)
{
    //cout << "compare precedence: " << a << " and " << b << ": ";
    if ((a == "*" || a == "/" || a == "(") && (b == "+" || b == "-" || b == ")"))
    {
        //cout << " true " << endl;
        return true;
    }
    //cout << " false " << endl;
    return false;
}

string convertInfix2Postfix(string input)
{
    string result;
    string numA, numB;

    int size = input.size();
    int last = size - 1;
    if (size > 0)
    {
        Stack<string> strResultStack;

        for (int i = 0; i < size; i++)
        {
            //cout << input[i] << endl;

            // If is operand
            if (isdigit(input[i]) || input[i] == ')')
            {
                // and if stack is not empty add to result
                if (strResultStack.isEmpty())
                {
                    if (input[i] != ')')
                    {
                        result = result + input[i];
                    }
                }
                else
                {
                    bool r;
                    // if precedence is higher than top of stack, push to stack
                    r = precedence(string(1, input[i]), strResultStack.getTopValue());

                    if (r == true)
                    {
                        //cout << "push: " << input[i]  << endl;
                        strResultStack.push(string(1, input[i]));
                    }
                    else
                    {
                        string ret_pop = strResultStack.pop();

                        if (ret_pop == "(" || ret_pop == ")" || input[i] == '(' || input[i] == ')')
                        {

                            if (ret_pop == "(" || ret_pop == ")")
                            {
                                if (input[i] != '(' && input[i] != ')')
                                {
                                    result = result + input[i];
                                }
                            }
                            else if (input[i] == '(' || input[i] == ')')
                            {
                                if (ret_pop != "(" && ret_pop != ")")
                                {
                                    result = result + ret_pop;
                                }
                            }
                        }
                        else
                        {
                            result = result + input[i] + ret_pop;
                        }
                    }
                }
            }
            else
            {

                strResultStack.push(string(1, input[i]));
            }
        }
    }

    return result;
}

void testMathematicalEvaluating()
{
    fstream datafile;
    string file = "Poxtfix.csv", line;
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
        cout << setw(20) << left << "Source";
        cout << setw(20) << left << "Result";
        cout << setw(30) << left << "Postfix-to-Infix";
        cout << setw(30) << left << "Infix-to-Postfix";
        cout << endl
             << endl;

        double ret;
        string ret_infix, ret_postfix;
        int row = 0;
        while (getline(datafile, line))
        {
            try
            {
                ret = evaluatePostfix(line);
                ret_infix = convertPostfix2Infix(line);
                ret_postfix = convertInfix2Postfix(ret_infix);

                cout << setw(20) << left << line;
                cout << setw(20) << left << ret;
                cout << setw(30) << left << ret_infix;
                cout << setw(30) << left << ret_postfix;

                cout << endl;
                row++;
            }
            catch (StackException e)
            {
                cout << e.getMessage() << endl;
            }
        }
    }
}

void main()
{
    // Show welcome message
    cout << "****************************************************************************" << endl;
    cout << "*                        Welcome to Lab 2                                  *" << endl;
    cout << "*                      Student: Robert Tang                                *" << endl;
    cout << "*                                                                          *" << endl;
    cout << "*   This program will demonstrate using a stack to evaluate an expression. *" << endl;
    cout << "*   1. Read in a string that has an expression using post - fix notation   *" << endl;
    cout << "*   2. For each character in the string :                                  *" << endl;
    cout << "*   3. If it is a number, push it on the number stack                      *" << endl;
    cout << "*   4. If it is an operator (like + , -, *, / )                            *" << endl;
    cout << "*      a.pop two numbers off the stack                                     *" << endl;
    cout << "*      b.perform the operation                                             *" << endl;
    cout << "*      c.push the result on the stack                                      *" << endl;
    cout << "****************************************************************************" << endl;

    testMathematicalEvaluating();
    //testStack();

    cout << "Going to close application. ";
    system("pause");
}
