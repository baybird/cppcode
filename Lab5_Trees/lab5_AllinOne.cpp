///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 5
//  Created on: 2/18/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

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
    int size = 0;      // the tree’s size, that is, the number of nodes in the tree
    TreeNode<T> *root; // a pointer to the root of the tree.

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
        TreeNode<T> *newNode = new TreeNode<T>(x);
        ;
        TreeNode<T> *nodePtr;
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

    void inOrder(TreeNode<T> *nodePtr, int level = 0)
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

    void preOrder(TreeNode<T> *nodePtr, int level = 0)
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

    void postOrder(TreeNode<T> *nodePtr, int level = 0)
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

    TreeNode<T> *getRoot()
    {
        return root;
    }
};

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                              Welcome to CIS22C-Lab 5                                         *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Convert the TreeArray C++ source code into a LinkedList BinaryTree.                       *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Test - from predefined data                                                              *" << endl;
    cout << "*  2) Test - from data file ( UProducts.csv )                                                  *" << endl;
    cout << "************************************************************************************************" << endl;
}

string *csv2arr(string line)
{
    char delimiter = ',';
    const int SIZE = 2;
    string str, *ret = new string[SIZE];

    istringstream is(line); // Input string stream

    int i = 0;
    while (getline(is, str, delimiter))
    {
        //cout << str << endl;
        ret[i] = str;
        i++;
    }

    return ret;
}

void importDataFile()
{
    BinarySearchTree<string> bst;

    fstream datafile;
    string file = "UProducts.csv", line, *item;
    int TITLE_INDEX = 0, VALUE_INDEX = 1;

    datafile.open(file);
    if (datafile.fail())
    {
        cout << "Error: couldn't open the data file '" << file << "'." << endl;
    }
    else
    {
        int row = 0;
        while (getline(datafile, line))
        {
            item = csv2arr(line); // parse csv string to array
            bst.insert(item[TITLE_INDEX]);
            row++;
        }

        cout << "\t " << bst.getSize() << " words imported." << endl;

        cout << "Going to print tree in Inorder ********************" << endl;
        system("pause");
        bst.inOrder(bst.getRoot(), 0);

        cout << "Going to print tree in Preorder ********************" << endl;
        system("pause");
        bst.preOrder(bst.getRoot(), 0);

        cout << "Going to print tree in Postorder ********************" << endl;
        system("pause");
        bst.postOrder(bst.getRoot(), 0);

        cout << "Going to do Search ********************" << endl;
        system("pause");
        string keyword = "Lettuce";
        bst.search(keyword);

        keyword = "Fruit";
        bst.search(keyword);
    }

    datafile.close();
}

void test()
{
    int array[] = {42, 68, 35, 1, 70, 25, 79, 59, 63, 65};
    //string array[] = { "coffee", "bee", "apple", "orange", "banana" };
    int size = sizeof(array) / sizeof(array[0]);

    BinarySearchTree<int> bst;
    //BinarySearchTree bst(size);

    for (int i = 0; i < size; i++)
    {
        bst.insert(array[i]);
    }
    cout << bst.getSize() << " inserted." << endl;
    //system("pause");

    cout << "Inorder ********************" << endl;
    bst.inOrder(bst.getRoot(), 0);
    //system("pause");

    cout << "Preorder ********************" << endl;
    bst.preOrder(bst.getRoot(), 0);
    //system("pause");

    cout << "Postorder ********************" << endl;
    bst.postOrder(bst.getRoot(), 0);
    //system("pause");

    cout << "Search ********************" << endl;
    bst.search(65);

    //cout << "In memory" << endl;
    //bst.printArray();
}

int main()
{

    bool exit = false;
    int choice;

    do
    {
        system("cls");
        menu();
        cout << "Enter your choice [0-2]:";
        cin >> choice;

        if (choice == 1)
        {
            test();
            system("pause");
        }
        else if (choice == 2)
        {
            importDataFile();
            system("pause");
        }
        else
        {
            exit = true;
        }
    } while (exit == false);

    system("pause");
};