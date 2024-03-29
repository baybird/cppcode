///////////////////////////////////////////////////////////
//  Main.cpp
//  Group Project Hasing
//  Student: Robert Tang
//  IDE: Visual Studio
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Hashing.h"
#include "BloomFilter.h"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                          Welcome to Group Project                                     *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                  Group: Soham Pardeshi, Ben Fong, Samantha Seymour                           *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate following Hashing and Bloom Filter.                            *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Hashing                                                                                  *" << endl;
    cout << "*  2) Bloom Filter                                                                             *" << endl;
    cout << "************************************************************************************************" << endl;
}

void main()
{
    bool exit = false;
    int input;

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-2]:";
        cin >> input;

        if (input == 1)
        {
            HashMap<string, double, int> h;
            h.main();
        }
        else if (input == 2)
        {
            BloomFilter<string> b;
            b.main();
        }
        else
        {
            exit = true;
        }
    } while (exit != true);

    cout << "Going to close application. ";
    system("pause");
}
