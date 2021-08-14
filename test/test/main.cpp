///////////////////////////////////////////////////////////
//  Main.cpp
//  CIS22C - Lab 8
//  Created on: 3/11/2017 
//  Student: Xu Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Node.h"

using namespace std;

class Base
{
public:
    static void show()
    {
        cout << "Base class\n";
    }

    void name()
    {
        cout << "Base " << endl;
    }
};

class Derived :public Base
{
public:
    void show() 
    {
        cout << "Derived Class\n";
        this->name();
    }

    void name()
    {
        cout << "Derived" << endl;
    }
};


template<class T>
class Solution {
    

public:
    TreeNode<T>  * root = nullptr;

    TreeNode<T> * invertTree(TreeNode<T> * root) {
        if (root){
            invertTree(root->left);
            invertTree(root->right);

            TreeNode<T>  * temp = root->left;
            root->left = root->right;
            root->right = temp;
        }

        return root;
    }

    TreeNode<T> * invertTree2(TreeNode<T> * root) {
        if (root->left != NULL){
            invertTree(root->left);
            invertTree(root->right);
        }

        TreeNode<T>  * temp = root->left;
        root->left = root->right;
        root->right = temp;

        return root;
    }

    void createTree(){
        root = new TreeNode<T>(4);
        root->left = new TreeNode<T>(2);
        root->right = new TreeNode<T>(7);

        root->left->left = new TreeNode<T>(1);
        root->left->right = new TreeNode<T>(3);

        root->right->left = new TreeNode<T>(6);
        root->right->right = new TreeNode<T>(9);
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

    void inOrder(TreeNode<T> * TreeNodePtr, int level = 0)
    {
        if (TreeNodePtr != NULL)
        {
            ++level;
            inOrder(TreeNodePtr->right, level);
            parent(level);
            cout << TreeNodePtr->key << endl;
            inOrder(TreeNodePtr->left, level);
        }
    }
};

void main()
{
    Solution<int> tree;
    tree.createTree();
    //tree.inOrder(tree.root);

    tree.invertTree(tree.root);
    tree.inOrder(tree.root);

    Derived a;
    a.show(); 
    system("pause");


    cout << "Going to close application. ";
    system("pause");
}

