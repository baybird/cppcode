#include "double_linkedlist.h"


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

// Removes one occurrence of a given entry fro m the list
template <class T>
bool LinkedList<T>::remove(T aTitle)
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

    if (head->title == aTitle)
    {
        nodePtr = head->next;   // if delete 1, then here is 2
        delete head;            // delete 1
        nodePtr->prev = head;
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
        //cout << "next node:" << nextNode << endl; system("pause");

        if (nextNode)
        {
            nextNode->prev = nodePtr->prev;
            delete nodePtr;
            nodePtr = nextNode;
        }
        else
        {
            delete nodePtr;
            nodePtr = nullptr;
        }

    }

    count = 0;
    head = nullptr;
    tail = nullptr;
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

template <class T>
void LinkedList<T>::importDataFile()
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
        int row = 0;
        List.clear();
        while (getline(datafile, line))
        {
            item = csv2arr(line); // parse csv string to array
            List.insert(item[TITLE_INDEX], item[VALUE_INDEX]);
            row++;
        }
        List.sorted = false;

        cout << "\t " << List.getCurrentSize() << " words imported." << endl; //system("pause");

        //cout << "Going to sort list. "; system("pause");
        //List.mergeSort(List, 0);
    }
}


// Print all nodes
template <class T>
void LinkedList<T>::showList(bool forward, Node<T> *nodePtr, int i=0)
{
    i++;

    if (forward) // forwards 
    {
        cout << setw(8) << left << i;
        cout << setw(28) << left << nodePtr->title;
        cout << setw(10) << right << nodePtr->value << endl;

        if (nodePtr->next)
        {
            showList(forward, nodePtr->next, i);
        }
        
    }
    else // backwards 
    {
        cout << setw(8) << left << i;
        cout << setw(28) << left << nodePtr->title;
        cout << setw(10) << right << nodePtr->value << endl;

        if (nodePtr->prev)
        {
            showList(forward, nodePtr->prev, i);
        }
    }    
}


template <class T>
void LinkedList<T>::swap(Node<T> * u, Node<T> * v)
{
    T title = u->title;
    T value = u->value;

    u->title = v->title;
    u->value = v->value;

    v->title = title;
    v->value = value;
    
}


// Bubble Sort
// Find the largest, seconde largest..., put them to the end till all ended.
template <class T>
int LinkedList<T>::bubbleSort()
{
    int iterator_count = 0;

    Node<T> * nodePtr;
    //Node<T> * nextPtr;

    int todo = count-1;
    //cout << "todo:" << todo << endl; system("pause");

    nodePtr = head;
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

        nodePtr = head;
        todo--;
    }

    return iterator_count;
}


// Selection Sort - n^2
// Find the smallest, seconde smallest..., put them to the begin till all found.
template <class T>
int LinkedList<T>::selectionSort()
{
    Node<T> * nodePtr;
    Node<T> * smallest = head;
    int size = 1, j=0;
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
int LinkedList<T>::mergeSort(LinkedList<T>& S, int iterator_count)
{
    //typedef typename LinkedList<T>::iterator Itor; // sequence of elements
    //cout << "sort list "; system("pause");
    
    int n = S.count;
    int todo = 0;
    //cout << "n: " << n << endl;
    if (n <= 1)
    {
        return iterator_count; // already sorted or empty
    }
    
    LinkedList<T> S1, S2;
    //Itor p = S.begin();
    Node<T> * nodePtr = S.head;

    todo = n / 2;
    //cout << " S1: 0 - " << todo;  system("pause");
    for (int i = 0; (i < todo && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S1.push back(*p++); // copy first half to S1
        S1.insert(nodePtr->title, nodePtr->value);
        nodePtr = nodePtr->next;
    }
    //cout << "show S1: ";  S1.showList(true); system("pause");

    //cout << " S2: " << todo << " - " << n ;  system("pause");
    for (int i = todo; (i <= n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S2.push back(*p++); // copy second half to S2        
        S2.insert(nodePtr->title, nodePtr->value);
        nodePtr = nodePtr->next;
    }
    //cout << "show S2: ";  S2.showList(true); system("pause");

    
    iterator_count = mergeSort(S1, iterator_count); // recur on first half

    iterator_count = mergeSort(S2, iterator_count); // recur on second half

    S.clear(); // clear S¡¯s contents
    merge(S1, S2, S); // merge S1 and S2 into S
    
    //cout << "show result: \n";  S.showList(true); system("pause");
    //cout << "iterator_count: " << iterator_count << " of " << count << "\n";

    return iterator_count;
}

template <typename T>  
void LinkedList<T>::merge(LinkedList<T>& S1, LinkedList<T>& S2, LinkedList<T>& S)
{

    //typedef typename LinkedList<E>::iterator Itor; // sequence of elements
    //Itor p1 = S1.begin();
    //Itor p2 = S2.begin();

    Node<T> * nodePtr1 = S1.head;
    Node<T> * nodePtr2 = S2.head;

    // until either is empty
    while (nodePtr1 != nullptr && nodePtr2 != nullptr)
    { 
        //cout << "compare: " << nodePtr1->title << " && " << nodePtr2->title << endl;


        if (nodePtr1->title < nodePtr2->title) // append smaller to S
        {
            //cout << "push: " << nodePtr1->title << endl;
            S.insert(nodePtr1->title, nodePtr1->value);
            nodePtr1 = nodePtr1->next;
        }            
        else
        {
            //cout << "push: " << nodePtr2->title << endl;
            S.insert(nodePtr2->title, nodePtr2->value);
            nodePtr2 = nodePtr2->next;
        }
    }
     
    //cout << "push rest S1 ******************************" << endl;
    while (nodePtr1) // copy rest of S1 to S
    {
        S.insert(nodePtr1->title, nodePtr1->value);
        //cout << "push: " << nodePtr1->title << nodePtr1->value << endl;
        nodePtr1 = nodePtr1->next;
    }
        
    //cout << "push rest S2 ******************************" << endl;
    while (nodePtr2) // copy rest of S2 to S
    {
        S.insert(nodePtr2->title, nodePtr2->value);
        //cout << "push: " << nodePtr2->title << nodePtr2->value << endl;
        nodePtr2 = nodePtr2->next;
    }

    //cout << "end ------------------------ \n\n" << endl;
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
    SE.insert(nodePtrPivot->title, nodePtrPivot->value);
    
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
                SL.insert(nodePtr->title, nodePtr->value);
                //cout << "\t push " << nodePtr->title << " to SL" << endl;
            }
            else if (nodePtr->title > nodePtrPivot->title)
            {
                SG.insert(nodePtr->title, nodePtr->value);
                //cout << "\t push " << nodePtr->title << " to SG" << endl;
            }
            else
            {
                SE.insert(nodePtr->title, nodePtr->value);
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
        S.insert(nodePtr->title, nodePtr->value);
        //cout << "\t push SL: " << nodePtr->title << " to S" << endl;
        nodePtr = nodePtr->next;
    }

    nodePtr = SE.head;
    while (nodePtr)
    {
        //iterator_count++;
        S.insert(nodePtr->title, nodePtr->value);
        //cout << "\t push SE: " << nodePtr->title << " to S" << endl;
        nodePtr = nodePtr->next;
    }

    nodePtr = SG.head;
    while (nodePtr)
    {
        //iterator_count++;
        S.insert(nodePtr->title, nodePtr->value);
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

