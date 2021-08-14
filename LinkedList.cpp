// A class template for holding a linked list.
// The node type is also a class template.
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//*********************************************
// The ListNode class creates a type used to  *
// store a node of the linked list.           *
//*********************************************

template <class T>
class ListNode
{
public:
	T value;           // Node value
	ListNode<T> *next; // Pointer to the next node

	// Constructor
	ListNode(T nodeValue)
	{
		value = nodeValue;
		next = nullptr;
	}

    ListNode()
    {
        next = nullptr;
    }
};

//*********************************************
// LinkedList class                           *
//*********************************************

template <class T>
class LinkedList
{
private:
	ListNode<T> *head;   // List head pointer

public:
	// Constructor
	LinkedList()
	{
		head = nullptr;
	}

	// Destructor
	~LinkedList();

	// Linked list operations
	void appendNode(T);
	void insertNode(T);
	void deleteNode(T);
	void displayList() const;
};


//**************************************************
// appendNode appends a node containing the value  *
// pased into newValue, to the end of the list.    *
//**************************************************

template <class T>
void LinkedList<T>::appendNode(T newValue)
{
	ListNode<T> *newNode;  // To point to a new node
	ListNode<T> *nodePtr;  // To move through the list


	// Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

    //cout << newNode->value << endl; system("pause");


	// If there are no nodes in the list
	// make newNode the first node.
	if (!head)
	{
		head = newNode;
        //cout << newValue << ":" << head->next << " is first node \n"; system("pause");

	}
	else// Otherwise, insert newNode at end.
	{
		// Initialize nodePtr to head of list.
		nodePtr = head;
        //cout << "Initialize nodePtr to head of list: " << nodePtr->next << endl; system("pause");

		// Find the last node in the list.
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}


		// Insert newNode as the last node.
		nodePtr->next = newNode;

        //cout << "New node: " << newNode << endl;
        //cout << "Prev node linked to :" << nodePtr->next << endl;
        //system("pause");
	}
}

//**************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head.          *
//**************************************************

template <class T>
void LinkedList<T>::displayList() const
{
	ListNode<T> *nodePtr;  // To move through the list

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		// Display the value in this node.
		cout << nodePtr->value << endl;

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// The insertNode function inserts a node with     *
// newValue copied to its value member.            *
//**************************************************

template <class T>
void LinkedList<T>::insertNode(T newValue)
{
	ListNode<T> *newNode;				// A new node
	ListNode<T> *nodePtr;				// To traverse the list
	ListNode<T> *previousNode = nullptr; // The previous node


    //cout << "Insert a node " << newValue << "*****" << endl;

	// Allocate a new node and store newValue there.
	newNode = new ListNode<T>(newValue);

	// If there are no nodes in the list
	// make newNode the first node
	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else  // Otherwise, insert newNode
	{
		// Position nodePtr at the head of list.
		nodePtr = head;

		// Initialize previousNode to nullptr.
		previousNode = nullptr;

		// Skip all nodes whose value is less than newValue.
		while (nodePtr != nullptr && nodePtr->value < newValue)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		// If the new node is to be the 1st in the list,
		// insert it before all other nodes.
		if (previousNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else  // Otherwise insert after the previous node.
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

//*****************************************************
// The deleteNode function searches for a node        *
// with searchValue as its value. The node, if found, *
// is deleted from the list and from memory.          *
//*****************************************************

template <class T>
void LinkedList<T>::deleteNode(T searchValue)
{
	ListNode<T> *nodePtr;       // To traverse the list
	ListNode<T> *previousNode;  // To point to the previous node

    previousNode = new ListNode<T>(); // Instantiate a node for previousNode


    //cout << "delete: " << searchValue << endl;

	// If the list is empty, do nothing.
    if (!head)
    {
        return;
    }


	// Determine if the first node is the one.
	if (head->value == searchValue)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		// Initialize nodePtr to head of list
		nodePtr = head;

		// Skip all nodes whose value member is
		// not equal to num.
		while (nodePtr != nullptr && nodePtr->value != searchValue)
		{
			previousNode = nodePtr;     // link to perv node
			nodePtr = nodePtr->next;    // link to next node
            //cout << "searching node: " << nodePtr->value << endl;
		}

        // If nodePtr is not at the end of the list,
		// link the previous node to the node after
		// nodePtr, then delete nodePtr.
		if (nodePtr)
		{
            //cout << "at node: " << nodePtr->value << endl;
            //cout << "prev node: " << previousNode->value << endl;
			previousNode->next = nodePtr->next; // Link prev node to next node
			delete nodePtr; // Remove current node
        }
        else
        {
            cout << "at end or not found" << endl;
        }
	}
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

template <class T>
LinkedList<T>::~LinkedList()
{
	ListNode<T> *nodePtr;   // To traverse the list
	ListNode<T> *nextNode;  // To point to the next node

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr is not at the end of the list...
	while (nodePtr != nullptr)
	{
		// Save a pointer to the next node.
		nextNode = nodePtr->next;

		// Delete the current node.
		delete nodePtr;

		// Position nodePtr at the next node.
		nodePtr = nextNode;
	}
}

#endif