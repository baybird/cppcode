#include<iostream>
using namespace std;

template <class T>
class TreeNode
{
public:
    T key;
    int value;
    TreeNode<T> *left;
    TreeNode<T> *right;

    TreeNode()
    {
        left = nullptr;
        right = nullptr;
    }

    TreeNode(T aKey, T aValue)
    {
        key = aKey;
        value = aValue;
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

    void insert(T aKey, T aValue)
    {
        TreeNode<T> * newNode = new TreeNode<T>(aKey, aValue);
        TreeNode<T> * nodePtr;
        size++;

        //cout << "insert: " << aKey;

        nodePtr = root;
        if (nodePtr == NULL)
        {
            root = newNode;
            //cout << " in Root " << endl;
        }
        else
        {
            bool exit = false;
            do
            {
                if (aKey < nodePtr->key) // Goes to left
                {
                    //cout << " <<< Left ";
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
                    //cout << " Right >>> ";
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

    void search(T aKey)
    {
        cout << "Search: " << aKey << endl;

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
            else if (nodePtr->key == aKey)
            {
                cout << "Found at level: " << level << endl;
                exit = true;
            }
            else if (nodePtr->left && aKey < nodePtr->key)
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

    bool update(T aKey)
    {

        TreeNode<T> *nodePtr = root;
        int level = 0;
        bool exit = false;
        do
        {
            if (nodePtr == NULL)
            {
                exit = true;
            }
            else if (nodePtr->key == aKey)
            {
                //cout << nodePtr->value << " + 1 = ";
                nodePtr->value += 1;
                //cout << nodePtr->value << endl;
                //system("pause");

                return true;
            }
            else if (nodePtr->left && aKey < nodePtr->key)
            {
                nodePtr = nodePtr->left;
            }
            else
            {
                nodePtr = nodePtr->right;
            }

            level++;
        } while (exit == false);

        return false;
    }

    void parent(int aKey)
    {
        --aKey;
        while (aKey != 0)
        {
            aKey--;
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
            cout << nodePtr->key << " (" << nodePtr->value << ")" << endl;
            inOrder(nodePtr->right, level);
        }
    }

    void preOrder(TreeNode<T> * nodePtr, int level = 0)
    {
        if (nodePtr != NULL)
        {
            ++level;

            parent(level);
            cout << nodePtr->key << " (" << nodePtr->value << ")" << endl;
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
            cout << nodePtr->key << " (" << nodePtr->value << ")" << endl;
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

    void importDataFile()
    {
        fstream keyfile;
        string file = "Speech.txt", line;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;
        TreeNode<T> nodePtr;

        keyfile.open(file);
        if (keyfile.fail())
        {
            cout << "Error: couldn't open the key file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int row = 0, strlength, count = 0;

            while (getline(keyfile, line))
            {
                strlength = line.length();
                for (int i = 0; i < strlength; i++)
                {
                    // Only track ASCII between 32-128
                    if (line[i] >= 32 || line[i] <= 128)
                    {
                        

                        //cout << line[i] << endl;
                        // find key from tree
                        if (update(line[i]))
                        {
                            //cout << "updated." << endl;
                        }
                        else
                        {
                            count++;
                            insert(line[i], 1);
                            //cout << "inserted." << endl;
                        }                        
                        //system("pause");
                        
                    }

                }
            }

            //cout << "\t " << List.getCurrentSize() << " characters imported." << endl; //system("pause");

            //cout << "Going to sort list. "; system("pause");
            //List.mergeSort(List, 0);
        }
    }

};