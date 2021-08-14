///////////////////////////////////////////////////////////
//  Main.cpp
//  CIS22C - Midterm
//  Created on: 2/18/2017
//  Student: Xu Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;


#ifndef _CIS22C_MIDTERM
#define _CIS22C_MIDTERM


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
	int count = 0;  // To count number of entries in the list
	bool sorted = false;
	Node<T> *head;
	Node<T> *tail;

public:
	LinkedList();  // Constructor
	~LinkedList(); // Destructor

	// Functions
	void insertAfter(T, T); // Add a new node after another
	void insertAtBeginning(T, T); // Adds a new entry to the begining of list
	void insertAtEnd(T, T); // Adds a new entry to the end of list
	bool search(T);         // Search the linkedlist

	// Sorting
	int quickSort(LinkedList<T>& S, int);
};
#endif
// definition end **********************************************************************************

// Implementation begin **********************************************************************************
// Constructor
template <class T>
LinkedList<T>::LinkedList()// Constructor inline
{
	head = nullptr;
	tail = nullptr;
}


// Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
	//clear(); // Removes all entries from the list
}

// Adds a new entry to the list
template <class T>
void LinkedList<T>::insertAtEnd(T aTitle, T aValue)
{
	Node<T> *newNode;
	Node<T> *nodePtr;

	// allocate a new node to hold aValue
	newNode = new Node<T>(aTitle, aValue);

	if (!head)// If head is unused then hold newNode in head
	{
		head = newNode;
		tail = newNode;
		count++;
		//cout << aTitle << " " <<aValue << ":" << head << " is first node \n"; system("pause");
	}
	else
	{
		//cout << aTitle << " " << aValue << ":" << head->next << " \n";

		// Initialize nodePtr to head
		nodePtr = head;
		//cout << "Initialize nodePtr to head of list: " << nodePtr->next << endl; system("pause");

		// Loop to the last node
		while (nodePtr->next != NULL)
		{
			nodePtr = nodePtr->next;
		}

		// Add new node to the end of list


		nodePtr->next = newNode; // Last node
		newNode->next = nullptr;
		newNode->prev = nodePtr; // new node's prev is last node
		tail = newNode;          // Tail set as new node

		count++;

		//cout << "New node: " << newNode << endl;
		//cout << "Next node:" << newNode->next << endl;
		//cout << "Prev node:" << newNode->prev << endl;
		//system("pause");
	}
}

template <class T>
void LinkedList<T>::insertAtBeginning(T aTitle, T aValue)
{
	Node<T> *newNode;

	// allocate a new node to hold aValue
	newNode = new Node<T>(aTitle, aValue);

	if (!head)// If head is unused then hold newNode in head
	{
		head = newNode;
		tail = newNode;
		count++;
		//cout << aTitle << " " <<aValue << ":" << head << " is first node \n"; system("pause");
	}
	else
	{
		// Initialize nodePtr to head
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		count++;
	}
}

// Tests whether the list contains the entry
template <class T>
bool LinkedList<T>::search(T aTitle)
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
void LinkedList<T>::insertAfter(T targetTitle, T aTitle)
{
	Node<T> *newNode;
	Node<T> *nodePtr;

	newNode = new Node<T>(aTitle, "000");

	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		// Point to head
		nodePtr = head;

		// Looping to find target value
		while (nodePtr)
		{

			if (nodePtr->title == targetTitle)
			{
				//cout << targetTitle << " found " << endl;
				break;
			}
			else
			{
				nodePtr = nodePtr->next;
			}
		}

		if (nodePtr->next)
		{
			nodePtr->next->prev = newNode;
			newNode->next = nodePtr->next;
		}


		nodePtr->next = newNode;
		newNode->prev = nodePtr;


	}
}


// QuickSort -- divide-and-conquer
// O(n log n)
template <typename T>
int LinkedList<T>::quickSort(LinkedList<T>& S, int iterator_count = 0)
{
	int n = S.count;
	int half = n / 2;

	if (n < 2)
	{
		//cout << "n < 2 then return " << endl;
		return iterator_count; // already sorted or empty
	}

	LinkedList<T> SL, SE, SG;

	// Delcare pivot
	//Node<T> * nodePtrPivot = S.tail; // Choose the last node to be pivot can increase running times if the linked list already sorted.
	Node<T> * nodePtrPivot = S.head;
	for (int x = 0; x < half; x++)
	{
		nodePtrPivot = nodePtrPivot->next;
	}
	SE.insertAtBeginning(nodePtrPivot->title, nodePtrPivot->value);

	// Divide ********************
	// Separate nodes groups: less than pivot, equal to pivot, greater than pivot
	Node<T> * nodePtr = S.head;
	for (int i = 0; (i < n && nodePtr != nullptr); i++)
	{
		iterator_count++;
		if (i != half)
		{
			//cout << iterator_count << endl;
			//cout << "compare: " << nodePtr->title << " AND " << nodePtrPivot->title << endl;
			if (nodePtr->title < nodePtrPivot->title)
			{
				SL.insertAtBeginning(nodePtr->title, nodePtr->value);
				//cout << "\t push " << nodePtr->title << " to SL" << endl;
			}
			else if (nodePtr->title > nodePtrPivot->title)
			{
				SG.insertAtBeginning(nodePtr->title, nodePtr->value);
				//cout << "\t push " << nodePtr->title << " to SG" << endl;
			}
			else
			{
				SE.insertAtBeginning(nodePtr->title, nodePtr->value);
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
	nodePtr = SL.head;
	while (nodePtr)
	{
		//iterator_count++;
		S.insertAtBeginning(nodePtr->title, nodePtr->value);
		//cout << "\t push SL: " << nodePtr->title << " to S" << endl;
		nodePtr = nodePtr->next;
	}

	nodePtr = SE.head;
	while (nodePtr)
	{
		//iterator_count++;
		S.insertAtBeginning(nodePtr->title, nodePtr->value);
		//cout << "\t push SE: " << nodePtr->title << " to S" << endl;
		nodePtr = nodePtr->next;
	}

	nodePtr = SG.head;
	while (nodePtr)
	{
		//iterator_count++;
		S.insertAtBeginning(nodePtr->title, nodePtr->value);
		//cout << "\t push SG: " << nodePtr->title << " to S" << endl;
		nodePtr = nodePtr->next;
	}

	SL.clear();
	SE.clear();
	SG.clear();
	//cout << "END --------------------------------------------------------\n\n\n" << endl;
	return iterator_count;
}
// Implementation end **********************************************************************************

int main()
{
    /*
    1. Given these two node based structures:
        Node<T>
            T data
            Node<T> next
        ...
   
        LinkedList<T>
            Node<T> head
        ...
   
        a. Write a function to insert a Node at the beginning of the list (assuming the list already exists).
        b. Write a function to insert a Node at the end of the list (assuming the list already exists).
        c. Write a function to insert a Node somewhere between the beginning and end of the list.

    2. Write a function to sort LinkedList defined in question #1.  Use a sorting algorithm of your choice.

    3. Java has a function to return a position in an array:  get(int index) reads the object at the given index in an array.  Write an algorithm to get(index) of the LinkedList defined in the previous questions, where the algorithm returns the object in the LinkedList at that index.  Add class data to the structures defined above as necessary to support your algorithm.

    4. Write a function to search the LinkedList defined in the previous questions.  Assume the LinkedList data is sorted in ascending order.  Add class data to the structures as necessary to support your algorithm.  Consider using your get(index) algorithm defined in the previous question to assist in the search.

    5. Determine the BigO of this algorithm, and briefly explain your answer.  Assume n is a node in a sorted data structure.

          Algorithm DoIt(n,k)
          1  if n == NIL or k == n.key
          2        return n 
          3  if k < n.key
          4        return DoIt(n.prev,k)
          5   else
          6        return DoIt(n.next,k)
    */

    LinkedList<string> list;


    system("pause");
    return 0;
}