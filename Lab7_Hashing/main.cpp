///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab7 - Hashing
//  Created on: 3/3/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Hashing.h"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                               Welcome to Lab7 - Hashing                                      *" << endl;
    cout << "*                                 Student: Robert Tang                                         *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Place each ADT data object into a Hashing structure using a custom hashing function.      *" << endl;
    cout << "*  + Hash the name data as key and id as value, and vice versa.                                *" << endl;
    cout << "*  + Overloading appropriate operators (in C++) to support the < operator.                     *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Hash name as key                                                                         *" << endl;
    cout << "*  2) Hash ID as key                                                                           *" << endl;
    cout << "*  3) Get current size                                                                         *" << endl;
    cout << "*  4) Dispaly hash table                                                                       *" << endl;
    cout << "*  5) Test overloading operator                                                                *" << endl;
    cout << "************************************************************************************************" << endl;
}

string trim(string s)
{
    // Find absence of character in string
    size_t p = s.find_first_not_of(" \t");

    // Erase characters from string
    s.erase(0, p);

    // Finds the last character equal to none of the
    // characters in the given character sequence.
    p = s.find_last_not_of(" \t");

    if (string::npos != p)
    {
        s.erase(p + 1);
    }

    return s;
}

void main()
{
    bool exit = false;
    int input, size = 512;
    string dataFile = "Customer.csv";

    HashMap<string, string, int> h(size);

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-5]:";
        cin >> input;

        if (input == 1)
        {
            h.clear();
            h.importDataFile(dataFile, "name");
            h.testAll(dataFile);
        }
        else if (input == 2)
        {
            h.clear();
            h.importDataFile(dataFile, "id");
            h.testAll(dataFile);
        }
        else if (input == 3)
        {
            cout << "Current size: " << h.size() << endl;
        }
        else if (input == 4)
        {
            h.display();
        }
        else if (input == 5)
        {
            for (int i = 0; i < size; i++)
            {
                cout << setw(10) << i
                     << setw(20) << h[i] << endl;
            }
        }
        else
        {
            exit = true;
        }

        system("pause");
    } while (exit != true);

    cout << "Going to close application. ";
    system("pause");
}
