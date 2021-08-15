///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 8
//  Created on: 3/11/2017
//  Student: Robert Tang
//  IDE: Visual Studio 2013
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "PriorityQueue.cpp"
#include "HuffmanTree.h"

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                                   Lab 8 - Encoding                                           *" << endl;
    cout << "*                                 Student: Robert Tang                                         *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* This program will demonstrate:                                                               *" << endl;
    cout << "*  + Using the Huffman encoding algorithm as explained in class, encode and decode             *" << endl;
    cout << "*    the Speech.txt file using frequency tree and priority queue.                              *" << endl;
    cout << "*  + Implement Huffman style of tree (built from the bottom-up) and use it to                  *" << endl;
    cout << "*    encode/decode the text file.                                                              *" << endl;
    cout << "*                                                                                              *" << endl;
    cout << "* Choices:                                                                                     *" << endl;
    cout << "*  0) Exit program                                                                             *" << endl;
    cout << "*  1) Encode                                                                                   *" << endl;
    cout << "*  2) Decode                                                                                   *" << endl;
    //cout << "*  3) Display tree size                                                                        *" << endl;
    //cout << "*  4) Display encode string length                                                             *" << endl;
    //cout << "*  5) Display decode string length                                                             *" << endl;
    //cout << "*  1) Import Data                                                                              *" << endl;
    //cout << "*  2) Show HEAP/Priority Queue                                                                 *" << endl;
    //cout << "*  3) Get size of HEAP                                                                         *" << endl;
    //cout << "*  4) Get size of characters                                                                   *" << endl;
    cout << "************************************************************************************************" << endl;
}

PriorityQueue<char> List;

void main()
{
    string code, infile = "Speech.txt", outfile = "Speech.encode.txt", decodeFile = "Speech.decode.txt";
    int input;

    List.importDataFile();
    List.bubbleSort();

    // Build Huffman tree
    HuffmanTree<char> tree;
    tree.buildTreeFromHeap(List);

    //tree.search(tree.root, 'G', code);
    //cout << "search G:" << code << endl;
    //system("pause");

    do
    {
        system("cls");
        menu(); // Show welcome message
        cout << "Please enter your choice [0-5]:";
        cin >> input;
        switch (input)
        {
        case 1:
            tree.encode(infile, outfile);
            system("pause");
            break;

        case 2:
            tree.decode(outfile, decodeFile);
            system("pause");
            break;

        case 3:
            cout << "Tree has " << tree.getSize() << " characters/leaves. \n"
                 << endl;
            system("pause");
            break;

        case 4:
            cout << "Encode string length: " << tree.getEncodeStringLength() << "\n"
                 << endl;
            system("pause");
            break;

        case 5:
            cout << "Decode string length: " << tree.getDecodeStringLength() << "\n"
                 << endl;
            system("pause");
            break;

            //case 2:
            //    List.showList(true, List.front, 0); // fordwards

            //    //nodePtr = List.rear;
            //    //List.showList(false, nodePtr, 0); // backwards

            //    system("pause");
            //    break;

            //case 3:
            //    cout << "Size:" << List.getCurrentSize() << endl;
            //    system("pause");
            //    break;

            //case 4:
            //    cout << "Size:" << List.getCharSize() << endl;
            //    system("pause");
            //    break;
        }

    } while (input != 0);

    cout << "Going to close application. ";
    system("pause");
}
