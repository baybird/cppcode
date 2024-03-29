///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 8
//  Student: Robert Tang
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <math.h>

// #include "PriorityQueue.cpp"
// #include "HuffmanTree.h"
using namespace std;

// Node class
template <class T>
class Node
{
public:
    T key;
    string val;
    int freq = 0;
    string code;

    Node<T> *left = nullptr;
    Node<T> *right = nullptr;

    // Constructors
    Node()
    {
        right = nullptr;
        left = nullptr;
    }

    Node(T akey)
    {
        key = akey;
        freq = 1;
    }

    Node(T akey, T aVal)
    {
        key = akey;
        val = aVal;
        freq = 1;
    }

    Node(Node *n1) : left(n1)
    {
        key = left->getSymbol();
        freq = left->freq;
    };

    Node(Node *n0, Node *n1) : left(n0), right(n1)
    {
        key = left->getSymbol() + right->getSymbol();
        freq = left->freq + right->freq;
    };

    int getFreq()
    {
        return freq;
    }

    T getSymbol()
    {
        return key;
    }
};

// Interface of PriorityQueue
template <class T>
class PriorityQueue
{
private:
    int count = 0; // To track number of entries in the list
    int size = 0;  // To track the total size of characters
    bool sorted = false;
    Node<T> *front;
    Node<T> *rear;

public:
    PriorityQueue();  // Constructor
    ~PriorityQueue(); // Destructor

    // Functions
    int getCurrentSize();                  // Gets the current number of entries in the list
    int getCharSize();                     // Gets the total size of characters
    bool isEmpty();                        // Sees whether the list is empty
    void enqueue(T);                       // Adds a new entry to the list
    bool dequeue(T);                       // Removes one occurrence of a given entry fro m the list
    void clear();                          // Removes all entries from the list
    Node<T> *find(T);                      // Tests whether the list contains the entry
    void moveBefore(Node<T> *, Node<T> *); // Move node before another node

    Node<T> *min();   // Get minimum node
    void removeMin(); // Remove minimum node

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

    template <class T>
    friend class HuffmanTree;
};

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

template <class T>
int PriorityQueue<T>::getCharSize()
{
    return size;
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
    // Handle node links
    //if (nodePtr->right)
    //{
    //    nodePtr->right->left = nodePtr->left;
    //}

    //if (nodePtr->left)
    //{
    //    nodePtr->left->right = nodePtr->right;
    //    cout << "move: n->l->r = n->r " << endl; system("pause");
    //}

    // Handle target node
    if (targetPtr->left) // not null
    {
        targetPtr->left->right = nodePtr;
        nodePtr->left = targetPtr->left;
    }

    nodePtr->left->right = nodePtr->right;
    if (nodePtr->right)
    {
        nodePtr->right->left = nodePtr->left;
    }

    targetPtr->left = nodePtr;
    nodePtr->right = targetPtr;

    system("pause");

    //if (targetPtr == front) // is front
    //{
    //    //cout << "target is front " << endl;

    //    targetPtr->left = nodePtr;
    //    nodePtr->right = targetPtr;
    //    front = nodePtr;
    //}
    //else if (targetPtr == rear) // is rear
    //{
    //    //cout << "target is rear " << endl;
    //    targetPtr->right = nodePtr;
    //    nodePtr->left = targetPtr;
    //    rear = nodePtr;
    //}
    //else
    //{
    //    if (targetPtr->left) // not null
    //    {
    //        targetPtr->left->right = nodePtr;
    //        nodePtr->left = targetPtr->left;
    //    }

    //    targetPtr->left = nodePtr;
    //    nodePtr->right = targetPtr;
    //}
}
// Get minimum node
template <class T>
Node<T> *PriorityQueue<T>::min()
{
    if (rear != NULL)
    {
        return rear;
    }

    return false;
}

// Remove minimum node
template <class T>
void PriorityQueue<T>::removeMin()
{
    Node<T> *nodePtr = rear;

    if (rear)
    {
        rear = nodePtr->left;
        delete nodePtr;
        count--;
    }

    if (rear == nullptr)
    {
        front = nullptr;
    }
}

// Adds a new entry to the list
template <class T>
void PriorityQueue<T>::enqueue(T akey)
{
    Node<T> *newNode;
    Node<T> *nodePtr;

    //cout << "(" << count << ") " << akey << endl;

    if (!front) // If front is unused then hold newNode in front
    {
        newNode = new Node<T>(akey); // allocate a new node to hold aValue

        //cout << newNode->freq; system("pause");
        front = newNode;
        rear = newNode;
        count++;
    }
    else
    {
        // Check weaher new item already existed?
        if (nodePtr = find(akey)) // if new node already existed
        {
            // then, increase its frequency

            nodePtr->freq++;
        }
        else // otherwise
        {
            newNode = new Node<T>(akey); // allocate a new node to hold aValue

            rear->right = newNode;
            newNode->left = rear;
            rear = newNode;
            count++;
        }
    }

    //front->left = nullptr;
    //rear->right = nullptr;
}

// Removes one occurrence of a given entry fro m the list
template <class T>
bool PriorityQueue<T>::dequeue(T akey)
{
    // Instantiate node pointers
    Node<T> *nodePtr;
    Node<T> *leftiousNode;

    leftiousNode = new Node<T>;

    //cout << "remove: " << akey << endl;

    // If list is empty do nothing and return
    if (isEmpty())
    {
        //cout << "List is empty." << endl;
        return false;
    }

    if (front->key == akey)
    {
        nodePtr = front->right; // if delete 1, then here is 2
        delete front;           // delete 1
        nodePtr->left = front;
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
        while (nodePtr != nullptr && nodePtr->key != akey)
        {
            leftiousNode = nodePtr;
            nodePtr = nodePtr->right;
        }

        //cout << "node: " << nodePtr->key << ": "<< nodePtr->right << endl;  system("pause");
        //nodePtr = nodePtr->right;
        //cout << "right node: " << nodePtr->key << ": " << nodePtr->right << endl;  system("pause");

        // If value found, then delete it
        if (nodePtr != nullptr)
        {

            //cout << " is not nullptr " << endl; system("pause");
            //cout << nodePtr->key << endl;
            //cout << nodePtr->right << endl;

            if (nodePtr->right == nullptr)
            {
                //cout << "is nullptr" << endl;

                //cout << "going to link leftiousnode to nullptr" << endl; system("pause");
                leftiousNode->right = nullptr;

                //cout << "going to delete node" << endl; system("pause");
                //delete[] nodePtr;

                count--;
                return true;
            }
            else
            {
                //cout << "is not nullptr" << endl;

                leftiousNode->right = nodePtr->right;
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
    Node<T> *rightNode;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to delele all nodes
    while (nodePtr != nullptr)
    {
        rightNode = nodePtr->right;

        //cout << "Going to delete " << nodePtr->key << endl;
        //cout << "right node:" << rightNode << endl; system("pause");

        if (rightNode)
        {
            delete nodePtr;
            nodePtr = rightNode;
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
    size = 0;
}

// Tests whether the list contains the entry
template <class T>
Node<T> *PriorityQueue<T>::find(T akey)
{
    // Instantiate pointers
    Node<T> *nodePtr;

    // Initialize nodepointer to front
    nodePtr = front;

    // Looping to search
    // According to book, the time complexity for searching PriorityQueue is O(n)
    while (nodePtr != nullptr)
    {
        //if (akey =='$')
        //{
        //    cout << ">>> find right: " << nodePtr->key << endl;
        //}

        if (nodePtr->key == akey)
        {
            //cout << akey << " found " << endl; system("pause");
            return nodePtr;
        }

        nodePtr = nodePtr->right;
    }

    return false;
}

template <class T>
void PriorityQueue<T>::importDataFile()
{
    fstream dataInfile;
    string file = "Speech.txt", line, s;
    int key_INDEX = 0, VALUE_INDEX = 1;
    char c;

    dataInfile.open(file);
    if (dataInfile.fail())
    {
        cout << "Error: couldn't open the data file '" << file << "'." << endl;
        system("pause");
        exit(0);
    }
    else
    {
        int row = 0, strlength;

        List.clear();
        while (getline(dataInfile, line))
        {
            //cout << line.length() << endl;
            line += "\r\n";
            //cout << line.length() << endl; system("pause");

            strlength = line.length();
            for (int i = 0; i < strlength; i++)
            {
                // Only track ASCII between 32-128
                //if (line[i] >= 32 || line[i] <= 128)
                //{
                //cout << line[i] << endl;
                //s = string(1, line[i]);
                //cout << line[i] << ": " << (int) line[i] << endl;

                c = line[i];
                List.enqueue(c);
                List.size++;
                //system("pause");
                //}
            }
            //system("pause");
        }
        //system("pause");
        List.sorted = false;

        //cout << "\t " << List.getCurrentSize() << " characters imported." << endl; //system("pause");

        //cout << "Going to sort list. "; system("pause");
        //List.mergeSort(List, 0);
    }
}

// Print all nodes
template <class T>
void PriorityQueue<T>::showList(bool forward, Node<T> *nodePtr, int i = 0)
{
    if (nodePtr)
    {
        i++;
        cout << setw(8) << left << i;
        cout << setw(1) << left << nodePtr->key;
        cout << setw(10) << right << nodePtr->freq << endl;

        if (forward)
        {
            showList(forward, nodePtr->right, i);
        }
        else
        {
            showList(forward, nodePtr->left, i);
        }
    }
}

template <class T>
void PriorityQueue<T>::swap(Node<T> *u, Node<T> *v)
{
    T key = u->key;
    string val = u->val;
    int freq = u->freq;

    u->key = v->key;
    u->val = v->val;
    u->freq = v->freq;

    v->key = key;
    v->val = val;
    v->freq = freq;
}

// Bubble Sort
// Find the largest, seconde largest..., put them to the end till all ended.
template <class T>
int PriorityQueue<T>::bubbleSort()
{
    int iterator_count = 0;

    Node<T> *nodePtr;
    //Node<T> * rightPtr;

    int todo = getCurrentSize() - 1;
    //cout << "todo:" << todo << endl; system("pause");

    nodePtr = front;
    while (todo > 0)
    {
        iterator_count++;
        //cout << nodePtr->key << endl; system("pause");

        for (int i = 0; i < todo; i++)
        {
            iterator_count++;
            if (nodePtr->freq < nodePtr->right->freq)
            {
                //cout << "swap: " << nodePtr->key << " <-> " << nodePtr->right->key << endl;
                swap(nodePtr, nodePtr->right);
            }

            nodePtr = nodePtr->right;
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
        //cout << "smallest: " << smallest->key << endl;

        nodePtr = smallest->right;
        while (nodePtr)
        {
            iterator_count++;
            j++;

            //cout << "\t " << j << "/" << todo << " - node: " << nodePtr->key << endl;
            //cout << "\t compare: " << smallest->key << " <-> " << nodePtr->key << endl;
            //cout << "**********************" << endl;

            if (smallest->key > nodePtr->key)
            {
                //cout << "swap: " << smallest->key << " <-> " << nodePtr->key << endl;
                swap(nodePtr, smallest);
            }

            nodePtr = nodePtr->right;
        }

        smallest = smallest->right;
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
        S1.enqueue(nodePtr->key);
        nodePtr = nodePtr->right;
    }
    //cout << "show S1: ";  S1.showList(true); system("pause");

    //cout << " S2: " << todo << " - " << n ;  system("pause");
    for (int i = todo; (i <= n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        //S2.push back(*p++); // copy second half to S2
        S2.enqueue(nodePtr->key, nodePtr->freq);
        nodePtr = nodePtr->right;
    }
    //cout << "show S2: ";  S2.showList(true); system("pause");

    iterator_count = mergeSort(S1, iterator_count); // recur on first half

    iterator_count = mergeSort(S2, iterator_count); // recur on second half

    S.clear();        // clear S’s contents
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
        //cout << "compare: " << nodePtr1->key << " && " << nodePtr2->key << endl;

        if (nodePtr1->key < nodePtr2->key) // append smaller to S
        {
            //cout << "push: " << nodePtr1->key << endl;
            S.enqueue(nodePtr1->key, nodePtr1->freq);
            nodePtr1 = nodePtr1->right;
        }
        else
        {
            //cout << "push: " << nodePtr2->key << endl;
            S.enqueue(nodePtr2->key, nodePtr2->freq);
            nodePtr2 = nodePtr2->right;
        }
    }

    //cout << "push rest S1 ******************************" << endl;
    while (nodePtr1) // copy rest of S1 to S
    {
        S.enqueue(nodePtr1->key, nodePtr1->freq);
        //cout << "push: " << nodePtr1->key << nodePtr1->freq << endl;
        nodePtr1 = nodePtr1->right;
    }

    //cout << "push rest S2 ******************************" << endl;
    while (nodePtr2) // copy rest of S2 to S
    {
        S.enqueue(nodePtr2->key, nodePtr2->freq);
        //cout << "push: " << nodePtr2->key << nodePtr2->freq << endl;
        nodePtr2 = nodePtr2->right;
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
        nodePtrPivot = nodePtrPivot->right;
    }
    SE.enqueue(nodePtrPivot->key, nodePtrPivot->freq);

    // Divide ********************
    // Separate nodes groups: less than pivot, equal to pivot, greater than pivot
    Node<T> *nodePtr = S.front;
    for (int i = 0; (i < n && nodePtr != nullptr); i++)
    {
        iterator_count++;
        if (i != half)
        {
            //cout << iterator_count << endl;
            //cout << "compare: " << nodePtr->key << " AND " << nodePtrPivot->key << endl;
            if (nodePtr->key < nodePtrPivot->key)
            {
                SL.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SL" << endl;
            }
            else if (nodePtr->key > nodePtrPivot->key)
            {
                SG.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SG" << endl;
            }
            else
            {
                SE.enqueue(nodePtr->key, nodePtr->freq);
                //cout << "\t push " << nodePtr->key << " to SE" << endl;
            }
        }

        nodePtr = nodePtr->right;
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
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SL: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    nodePtr = SE.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SE: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    nodePtr = SG.front;
    while (nodePtr)
    {
        //iterator_count++;
        S.enqueue(nodePtr->key, nodePtr->freq);
        //cout << "\t push SG: " << nodePtr->key << " to S" << endl;
        nodePtr = nodePtr->right;
    }

    SL.clear();
    SE.clear();
    SG.clear();
    //cout << "END --------------------------------------------------------\n\n\n" << endl;
    return iterator_count;
}
// Implementation begin **********************************************************************************

// definition begin ********************************************************************************

template <class T>
class HuffmanTree
{

private:
    int size = 0; // the tree¡¯s size, that is, the number of nodes in the tree
    int encodeStrLength, decodeStrLength;

public:
    Node<T> *root = nullptr; // a pointer to the root of the tree.

    HuffmanTree()
    {
        root = nullptr;
    }

    Node<T> *getRoot()
    {
        return root;
    }

    int getSize()
    {
        return size;
    }

    void buildTreeFromHeap(PriorityQueue<T> &heap)
    {
        Node<T> *nodePtr = heap.front;
        Node<T> *newNodeR, *newNodeL;
        Node<T> *newBranch, *rootBranch;

        while (heap.count)
        {
            nodePtr = List.min();
            newNodeR = new Node<T>(nodePtr->key);
            size++;
            //cout << nodePtr->key << " = " << newNodeR->getSymbol() << endl;
            heap.removeMin();

            // create branch
            if (heap.count)
            {
                nodePtr = heap.min();
                newNodeL = new Node<T>(nodePtr->key);
                size++;
                //cout << nodePtr->key << " = " << newNodeL->getSymbol() << endl;
                heap.removeMin();

                // two nodes
                newBranch = new Node<T>(newNodeL, newNodeR);
                //cout << "Branch1: " << newBranch->getSymbol() << endl;
            }
            else // one node
            {
                newBranch = new Node<T>(newNodeR);
                //cout << "Branch2: " << newBranch->getSymbol() << endl;
            }

            // creat root branch
            if (root == nullptr)
            {
                root = newBranch;
                //cout << "root1: " << root->getSymbol() << endl;
                //cout << "left: " << root->left->getSymbol() << endl;
                //cout << "right: " << root->right->getSymbol() << endl;
            }
            else
            {
                //cout << "root2: " << newBranch->getSymbol() << endl;
                //cout << "left: " << newBranch->left->getSymbol() << endl;
                //cout << "right: " << newBranch->right->getSymbol() << endl;

                //cout << "inorder" << endl;
                //inOrder(newBranch, 0);

                //cout << "inorder" << endl;
                //inOrder(root, 0);

                rootBranch = new Node<T>(newBranch, root);
                root = rootBranch;

                //inOrder(root, 0);
                //system("pause");
            }

            //cout << "size: "<< heap.getCurrentSize() << endl;
            //system("pause");
        }
        //cout << "-------------------------------------------" << endl;
        assignCode(root);

        //inOrder(root, 0);
        //system("pause");
    }

    void insert(T x)
    {
        Node<T> *newNode = new Node<T>(x);
        Node<T> *nodePtr;
        size++;

        cout << "insert: " << x;

        nodePtr = root;
        if (nodePtr == NULL)
        {
            root = newNode;
            cout << " in Root " << endl;
        }
        else
        {
            bool exit = false;
            do
            {
                if (x < nodePtr->data) // Goes to left
                {
                    cout << " <<< Left ";
                    if (nodePtr->right == NULL)
                    {
                        nodePtr->right = newNode;
                        exit = true;
                        cout << endl;
                    }
                    else
                    {
                        nodePtr = nodePtr->right;
                    }
                }
                else // Goes to right
                {
                    cout << " Right >>> ";
                    if (nodePtr->right == NULL)
                    {
                        nodePtr->right = newNode;
                        exit = true;
                        cout << endl;
                    }
                    else
                    {
                        nodePtr = nodePtr->right;
                    }
                }
            } while (exit == false && nodePtr);
        }
    }

    void search(Node<T> *nodePtr, T x, string &code)
    {
        if (nodePtr != NULL)
        {
            search(nodePtr->right, x, code);

            if (nodePtr->left == nullptr && nodePtr->right == nullptr && nodePtr->getSymbol() == x)
            {
                //cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;
                code = nodePtr->code;
                return;
            }

            search(nodePtr->left, x, code);
        }
    }

    void parent(int x)
    {
        --x;
        while (x != 0)
        {
            x--;
            cout << "---|";
        }
    }

    void assignCode(Node<T> *nodePtr, string code = "", int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;
            assignCode(nodePtr->right, code + "1", level);

            //parent(level);

            nodePtr->code = code;
            //cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;

            assignCode(nodePtr->left, code + "0", level);
        }
    }

    int bits2Int(string str)
    {
        int ch = 0;
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            if (str[i] == '1')
            {
                ch += pow(2, (double)(7 - i));
            }
        }
        return ch;
    }

    char bits2char(string str)
    {
        char ch = 0;
        int i = 7;
        for (i = 7; i >= 0; i--)
        {
            if (str[i] == '1')
            {
                ch += (int)pow(2, (double)(7 - i));
            }
        }
        return ch;
    }

    string charToBits(char ch)
    {
        int num = static_cast<unsigned char>(ch);
        string bits = "";

        for (int i = 7; i >= 0; i--)
        {
            if (num - pow(2, i) >= 0)
            {
                num -= (int)pow(2, i);
                bits += "1";
            }
            else
                bits += "0";
        }
        return bits;
    }

    int getEncodeStringLength()
    {
        return encodeStrLength;
    }

    int getDecodeStringLength()
    {
        return decodeStrLength;
    }

    void encode(string infile, string outfile)
    {
        fstream dataInfile, dataOutfile;
        string line, code, str, eight;
        ;
        int strlength;
        char c;

        dataInfile.open(infile);
        if (dataInfile.fail())
        {
            cout << "Error: couldn't open the input file '" << infile << "'." << endl;
            return;
        }
        else
        {

            dataOutfile.open(outfile, ios::out);
            if (dataOutfile.fail())
            {
                cout << "Error: couldn't open the output file '" << outfile << "'." << endl;
                return;
            }
            else
            {
                cout << "Encoding, please wait a moment..." << endl;
            }

            // encode each char to bit string - eg '00100100'
            while (getline(dataInfile, line))
            {
                line += "\r\n";
                strlength = line.length();
                for (int i = 0; i < strlength; i++)
                {
                    c = line[i];
                    search(root, c, code);
                    str = str + code;
                    //cout << c << " = " << code << endl;
                }
            }
            //cout << str << endl;

            // convert string to bit
            int times = 0;
            encodeStrLength = str.length();
            // write length
            dataOutfile << encodeStrLength << endl;

            while (str.length() >= 8)
            {
                times++;
                eight = str.substr(0, 8);
                str = str.substr(8, str.length() - 8);
                //cout << eight << "\t" << bits2char(eight) << endl;
                //dataOutfile << (eight) << endl;
                dataOutfile << bits2char(eight);
            }

            // fill trailing zero to make it 8-bit long
            if (str.length() > 0)
            {
                //cout << "remain: " << str << endl;
                while (str.length() % 8)
                {
                    str += '0';
                }
                dataOutfile << bits2char(str);
                //cout << "fill as:" << str << endl;
            }

            //system("pause");

            dataOutfile.close();
            dataInfile.close();
            cout << "Done. Saved to file \"" << outfile << "\"" << endl;
        }
    }

    void decode(string infile, string outfile)
    {

        fstream dataInfile, dataOutfile;
        string line, code, str;
        int strlength;
        Node<T> *nodePtr = root;
        char c;

        dataInfile.open(infile);
        if (dataInfile.fail())
        {
            cout << "Error: couldn't open the input file '" << infile << "'. Please do encode first." << endl;
            return;
        }
        else
        {
            dataOutfile.open(outfile, ios::out);
            if (dataOutfile.fail())
            {
                cout << "Error: couldn't open the output file '" << outfile << "'." << endl;
                return;
            }
            else
            {
                cout << "Decoding, please wait a moment..." << endl;
            }

            // decode each char to bit string - eg '00100100'
            int rows = 0;
            while (getline(dataInfile, line))
            {
                rows++;
                if (rows == 1) // read length
                {
                    encodeStrLength = atoi(line.c_str());
                    continue;
                }

                strlength = line.length();
                for (int i = 0; i < strlength; i++)
                {
                    str += charToBits(line[i]);
                    //cout << line << endl;
                    //system("pause");
                }
            }

            decodeStrLength = str.length();

            /*cout << str << endl;
            cout << decodeStrLength << endl;
            system("pause");*/

            // convert bit to char
            for (int i = 0; i < getEncodeStringLength(); i++)
            {
                c = str[i];
                code += c;
                //cout << "c: " << c << endl;

                if (c == '1')
                {
                    nodePtr = nodePtr->right;
                    //cout << ">>> 1 to right" << endl;
                }
                else // c==0
                {
                    nodePtr = nodePtr->left;
                    //cout << ">>> 0 to left" << endl;
                }

                // determine, weather is leaf or not
                if (nodePtr->left == nullptr && nodePtr->right == nullptr)
                {
                    dataOutfile << (nodePtr->key);
                    //cout << code << " = " << nodePtr->key << endl; system("pause");

                    nodePtr = root;
                    code = "";
                }
            }

            //system("pause");
            dataOutfile.close();
            dataInfile.close();
            cout << "Done. Saved to file \"" << outfile << "\"" << endl;
        }
    }

    void inOrder(Node<T> *nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;
            inOrder(nodePtr->right, level);
            parent(level);
            cout << nodePtr->getSymbol() << " (" << nodePtr->code << ") " << endl;
            inOrder(nodePtr->left, level);
        }
    }

    void preOrder(Node<T> *nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;

            parent(level);
            cout << nodePtr->data << endl;
            preOrder(nodePtr->right, level);
            preOrder(nodePtr->right, level);
        }
    }

    void postOrder(Node<T> *nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;
            postOrder(nodePtr->right, level);
            postOrder(nodePtr->right, level);
            parent(level);
            cout << nodePtr->data << endl;
        }
    }

    void printArray()
    {
        for (int i = 0; i < size; i++)
            if (array[i])
                cout << array[i] << ' ';
            else
                cout << '.';
        cout << endl;
    }
};
// definition end **********************************************************************************

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                            Lab 8 - Encoding                                           *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Using the Huffman encoding algorithm as explained in class, encode and decode             *" << endl;
    cout << "*    the Speech.txt file using frequency tree and priority queue.                              *" << endl;
    cout << "*  + Implement Huffman style of tree (built from the bottom-up) and use it to                  *" << endl;
    cout << "*    encode/decode the text file.                                                              *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Encode                                                                                   *" << endl;
    cout << "*  2) Decode                                                                                   *" << endl;
    //cout << "*  3) Display tree size                                                                        *" << endl;
    //cout << "*  4) Display encode string length                                                             *" << endl;
    //cout << "*  5) Display decode string length                                                             *" << endl;
    //cout << "*  1) Import Data                                                                              *" << endl;
    //cout << "*  2) Show HEAP/Priority Queue                                                                 *" << endl;
    //cout << "*  3) Get size of HEAP                                                                         *" << endl;
    //cout << "*  4) Get size of characters                                                                   *" << endl;
    cout << "************************************************************************************************" << endl;
}

PriorityQueue<char> List;

void main()
{
    string code, infile = "Speech.txt", outfile = "Speech.encode.txt", decodeFile = "Speech.decode.txt";
    int input;

    List.importDataFile();
    List.bubbleSort();

    // Build Huffman tree
    HuffmanTree<char> tree;
    tree.buildTreeFromHeap(List);

    //tree.search(tree.root, 'G', code);
    //cout << "search G:" << code << endl;
    //system("pause");

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-5]:";
        cin >> input;
        switch (input)
        {
        case 1:
            tree.encode(infile, outfile);
            system("pause");
            break;

        case 2:
            tree.decode(outfile, decodeFile);
            system("pause");
            break;

        case 3:
            cout << "Tree has " << tree.getSize() << " characters/leaves. \n"
                 << endl;
            system("pause");
            break;

        case 4:
            cout << "Encode string length: " << tree.getEncodeStringLength() << "\n"
                 << endl;
            system("pause");
            break;

        case 5:
            cout << "Decode string length: " << tree.getDecodeStringLength() << "\n"
                 << endl;
            system("pause");
            break;

            //case 2:
            //    List.showList(true, List.front, 0); // fordwards

            //    //nodePtr = List.rear;
            //    //List.showList(false, nodePtr, 0); // backwards

            //    system("pause");
            //    break;

            //case 3:
            //    cout << "Size:" << List.getCurrentSize() << endl;
            //    system("pause");
            //    break;

            //case 4:
            //    cout << "Size:" << List.getCharSize() << endl;
            //    system("pause");
            //    break;
        }

    } while (input != 0);

    cout << "Going to close application. ";
    system("pause");
}
