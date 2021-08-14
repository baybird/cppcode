#include<iostream>
using namespace std;

template <class T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode()
    {
        left = nullptr;
        right = nullptr;
    }

    TreeNode(T aData)
    {
        data = aData;
        left = nullptr;
        right = nullptr;
    }
};


template <class T>
class BinarySearchTree
{
private:
    int size = 0;           // the tree¡¯s size, that is, the number of nodes in the tree
    TreeNode<T> * root;     // a pointer to the root of the tree.

public:

    BinarySearchTree()
    {
        root = nullptr;
    }

    int getSize()
    {
        return size;
    }

    void insert(T x)
    {
        TreeNode<T> * newNode = new TreeNode<T>(x);;
        TreeNode<T> * nodePtr;
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
                    if (nodePtr->left == NULL)
                    {
                        nodePtr->left = newNode;
                        exit = true;
                        cout << endl;
                    }
                    else
                    {
                        nodePtr = nodePtr->left;
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

    void search(T x)
    {
        cout << "Search: " << x << endl;

        TreeNode<T> *nodePtr = root;
        int level = 0;
        bool exit = false;
        do
        {
            if (nodePtr == NULL)
            {
                cout << "Not Found" << endl;
                exit = true;
            }
            else if (nodePtr->data == x)
            {
                cout << "Found at level: " << level << endl;
                exit = true;
            }
            else if (nodePtr->left && x < nodePtr->data)
            {
                cout << " <<< Left " << endl;
                nodePtr = nodePtr->left;
            }
            else
            {
                cout << " >>> Right " << endl;
                nodePtr = nodePtr->right;
            }

            level++;
        } while (exit == false);
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

    
    void inOrder(TreeNode<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;

            inOrder(nodePtr->left, level);
            parent(level);
            cout << nodePtr->data << endl;
            inOrder(nodePtr->right, level);
        }
    }

    void preOrder(TreeNode<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;

            parent(level);
            cout << nodePtr->data << endl;
            preOrder(nodePtr->left, level);
            preOrder(nodePtr->right, level);
        }
    }

    void postOrder(TreeNode<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;            
            postOrder(nodePtr->left, level);
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

    TreeNode<T> * getRoot()
    {
        return root;
    }

};