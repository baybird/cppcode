///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 9
//  Created on: 3/17/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#define N 12
#include "adjacencyMatrix.h"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                            CIS22C-Lab 9 - Graphing                                           *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*    Given the Airport's listed in the weighted graph on the Airport.PNG file in the documents *" << endl;
    cout << "*  folder, find the shortest path that visits each airport node starting at San Francisco.     *" << endl;
    cout << "*  Start by using a dynamic Adjacency Matrix, and then implement the Shortest Path algorithm   *" << endl;
    cout << "*  as shown in class.  Output should be the airports from SFO to end city in order if visits.  *" << endl;
    cout << "*    Also output the total distance.                                                           *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Show shortest path                                                                       *" << endl;
    cout << "************************************************************************************************" << endl;
}

void main()
{
    //string name[N] = { "A", "B", "C", "D", "E" };
    //int m[N][N] = {
    //    { 0, 3, 0, 1, 0 },
    //    { 3, 0, 2, 5, 2 },
    //    { 0, 2, 0, 0, 5 },
    //    { 1, 2, 0, 0, 1 },
    //    { 0, 2, 5, 1, 0 },
    //};

    string name[N] = {"San Franisco", "Seattle", "Minneapolis", "Chicago", "Boston", "Las Vegas", "Denver", "Dallas", "Wash DC", "New York", "Los Angeles", "Miami"};
    int m[N][N] = {
        {0, 1306, 0, 0, 0, 919, 0, 0, 0, 0, 629, 0},
        {1306, 0, 2661, 0, 0, 0, 2161, 0, 0, 0, 0, 0},
        {0, 2661, 0, 661, 0, 0, 1483, 1532, 0, 0, 0, 0},
        {0, 0, 661, 0, 1613, 0, 0, 0, 1145, 0, 0, 0},
        {0, 0, 0, 1613, 0, 0, 0, 0, 725, 338, 0, 0},
        {919, 0, 0, 0, 0, 0, 1225, 1983, 0, 0, 435, 0},
        {0, 2161, 1483, 0, 0, 1225, 0, 1258, 0, 0, 0, 0},
        {0, 0, 1532, 0, 0, 1983, 1258, 0, 2113, 0, 0, 2161},
        {0, 0, 0, 1145, 725, 0, 0, 2113, 0, 383, 0, 1709},
        {0, 0, 0, 0, 338, 0, 0, 0, 383, 0, 0, 2145},
        {629, 0, 0, 0, 0, 435, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2161, 1709, 2145, 0, 0},
    };

    menu();
    AdjacencyMatrix<string> Graph(name, m);
    Graph.shortestPath(m, 0);
    Graph.print();
    system("pause");

    int input;
    bool exit = false;
    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-1]:";
        cin >> input;
        switch (input)
        {
        default:
            Graph.shortestPath(m, 0);
            Graph.print();
            system("pause");
            break;

        case 0:
            exit = true;
            break;
        }

    } while (exit == false);

    cout << "Going to close application. ";
    system("pause");
}
