template <class T>
void PriorityQueue<T>::swap(Node<T> * u, Node<T> * v)
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

    Node<T> * nodePtr;
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
    Node<T> * nodePtr;
    Node<T> * smallest = front;
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
int PriorityQueue<T>::mergeSort(PriorityQueue<T>& S, int iterator_count)
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
    Node<T> * nodePtr = S.front;

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

    S.clear(); // clear S¡¯s contents
    merge(S1, S2, S); // merge S1 and S2 into S

    //cout << "show result: \n";  S.showList(true); system("pause");
    //cout << "iterator_count: " << iterator_count << " of " << count << "\n";

    return iterator_count;
}

template <typename T>
void PriorityQueue<T>::merge(PriorityQueue<T>& S1, PriorityQueue<T>& S2, PriorityQueue<T>& S)
{

    //typedef typename PriorityQueue<E>::iterator Itor; // sequence of elements
    //Itor p1 = S1.begin();
    //Itor p2 = S2.begin();

    Node<T> * nodePtr1 = S1.front;
    Node<T> * nodePtr2 = S2.front;

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
int PriorityQueue<T>::quickSort(PriorityQueue<T>& S, int iterator_count = 0)
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
    //Node<T> * nodePtrPivot = S.rear; // Because it is not stable sort, so choose the last node to be pivot can increase running times if the linked list already sorted.
    Node<T> * nodePtrPivot = S.front;
    for (int x = 0; x < half; x++)
    {
        nodePtrPivot = nodePtrPivot->right;
    }
    SE.enqueue(nodePtrPivot->key, nodePtrPivot->freq);

    // Divide ********************
    // Separate nodes groups: less than pivot, equal to pivot, greater than pivot
    Node<T> * nodePtr = S.front;
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
