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

#include "PriorityQueue.cpp"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                              Welcome to CIS22C-Lab 4                                         *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Create a ADT to read the Speech.txt file in this week's document folder.                  *" << endl;
    cout << "*  + Store each character in the Doubly Linked PriorityQueue and increment it's frequency      *" << endl;
    cout << "*    every time it's encountered in the file.                                                  *" << endl;
    cout << "*  + When finished processing the file, print the PriorityQueue and you should see the         *" << endl;
    cout << "*    frequency in order from highest to lowest.                                                *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Import Data                                                                              *" << endl;
    cout << "*  2) Print list                                                                               *" << endl;
    cout << "*  3) Get current size                                                                         *" << endl;
    cout << "************************************************************************************************" << endl;
}

PriorityQueue<char> List;

void main()
{

    int input;
    Node<char> *nodePtr;
    List.importDataFile();
    nodePtr = List.front;
    List.showList(true, nodePtr, 0); // fordwards
    system("pause");

    system("cls");
    menu(); // Show welcome message

    do
    {
        cout << "Please enter your choice [0-4]:";
        cin >> input;
        switch (input)
        {
        case 1:
            List.importDataFile();
            break;

        case 2:
            nodePtr = List.front;
            List.showList(true, nodePtr, 0); // fordwards
            system("pause");
            system("cls");
            menu();
            break;

        case 3:
            cout << "Size:" << List.getCurrentSize() << endl;
            break;
        }

        //system("cls");
    } while (input != 0);

    //testImportDataFile();

    cout << "Going to close application. ";
    system("pause");
}
