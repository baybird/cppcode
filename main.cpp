///////////////////////////////////////////////////////////
//  main.cpp
//  Author: Robert T
///////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "PriorityQueue.cpp"
#include "HuffmanTree.h"

#include "Cashier.h"
#include "Inventory.h"
#include "Report.h"

using namespace std;

int mainMenu()
{
	int choice;

	cout << "*****************************************" << endl;
	cout << " Booksellers" << endl;
	cout << "       Main Menu        " << endl
		 << endl;
	cout << "1. Cashier Module" << endl;
	cout << "2. Inventory Database Module" << endl;
	cout << "3. Report Module" << endl;
	cout << "4. Exit" << endl;
	cout << "*****************************************" << endl
		 << endl;

	cout << "Enter Your Choice:";

	while (!(cin >> choice))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid choice, please enter a whole number:";
	}

	return choice;
}

void exportTree()
{
	// Encoding
	string infile = "books.txt", outfile = "books.db";

	PriorityQueue<char> Heap;
	Heap.importDataFile(infile);
	Heap.bubbleSort();

	// Build Huffman tree
	HuffmanTree<char> tree;
	tree.buildTreeFromHeap(Heap);
	tree.encode(infile, outfile);
}

void importTree()
{
	// Encoding
	string infile = "books.db";

	// Build Huffman tree
	HuffmanTree<char> tree;
	tree.importTree(infile);
}

int main()
{
	bool exit = false;
	int user_choise;

	// Polymorphism
	Inventory *baseObj;
	Cashier cashierObj;
	Inventory inventoryObj;
	Report reportObj;

	//exportTree(); // Dump tree
	importTree();

	do
	{

		try
		{
			user_choise = mainMenu();

			if (user_choise < 1 || user_choise > 4)
			{
				string error = "Invalid choice. Please re-enter.";
				throw error;
			}
			else
			{
				if (user_choise == 1) // Casher
				{
					baseObj = &cashierObj; // Polymorphism
					baseObj->importDatafile();
					baseObj->menu();
					system("cls");
				}
				else if (user_choise == 2) // Inventory
				{
					baseObj = &inventoryObj; // Polymorphism
					baseObj->menu();
					system("cls");
				}
				else if (user_choise == 3) // Report
				{
					reportObj.importDatafile();
					reportObj.menu();
					system("cls");
				}
				else if (user_choise == 4) // Exit
				{
					exit = true;
					cout << "Goodbye!" << endl;
					system("pause");
				}
			}
		}
		catch (string exception)
		{
			cout << exception << endl;
			system("pause");
			system("cls");
		}
	} while (exit == false);

	return 0;
}
