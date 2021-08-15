///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 4
//  Created on: 2/11/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "LinkedBinaryTree.cpp"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                              Welcome to Lab 6                                         *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Redo the PriorityQueue assignment using your BinaryTree structure from Lab#5.             *" << endl;
    cout << "*  + For each Node in the tree, it has a KEY (character) and a VALUE (frequency).              *" << endl;
    cout << "*  + A tree, constructed this way is called a 'Dictionary'.  Process the speech as in the      *" << endl;
    cout << "*    PriorityQueue lab assignment, and output the frequencies for each character.              *" << endl;
    cout << "*  + Your expectation is the Dictionary will come out in KEY order rather than VALUE order.    *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Import Data                                                                              *" << endl;
    cout << "*  2) Print tree - inorder                                                                     *" << endl;
    cout << "*  3) Print tree - preOrder                                                                    *" << endl;
    cout << "*  4) Print tree - postOrder                                                                   *" << endl;
    cout << "*  5) Get current size                                                                         *" << endl;
    cout << "************************************************************************************************" << endl;
}

void main()
{

    int input;
    BinarySearchTree<char> bTree;
    bTree.importDataFile();

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-4]:";
        cin >> input;
        switch (input)
        {
        case 1:
            bTree.importDataFile();
            break;

        case 2:
            bTree.inOrder(bTree.getRoot(), 0);
            system("pause");
            break;
        case 3:
            bTree.preOrder(bTree.getRoot(), 0);
            system("pause");
            break;
        case 4:
            bTree.postOrder(bTree.getRoot(), 0);
            system("pause");
            break;
        case 5:
            cout << "Size:" << bTree.getSize() << endl;
            system("pause");
            break;
        }

        //system("cls");
    } while (input != 0);

    cout << "Going to close application. ";
    system("pause");
}
