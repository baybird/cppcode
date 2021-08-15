///////////////////////////////////////////////////////////
//  Main.cpp
//  Lab 0
//  Student: Robert Tang
///////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "DynamicArrayContainer.cpp"

using namespace std;

void test1()
{
	const int SIZE = 10;
	DynamicArray<int> intArray(SIZE);

	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 100;
		cout << "insert " << num << endl;
		intArray.insert(num);
	}

	//intArray.clear();
	//intArray.remove(2);

	intArray.show();
	cout << "capacity: " << intArray.getCapacity() << endl;
	cout << "current size: " << intArray.getCurrentSize() << endl;
	intArray.clear();
}

void testImportDataFile()
{
	fstream datafile;
	string file = "Words.csv";
	string word;

	datafile.open(file);
	if (datafile.fail())
	{
		cout << "Error: couldn't open data file." << endl;
		system("pause");
		exit(0);
	}
	else
	{

		const int SIZE = 10;
		DynamicArray<string> strArray(SIZE);

		cout << "Going to import words from CSV file: " << file << endl;
		system("pause");
		int i = 0;
		while (getline(datafile, word))
		{
			i++;
			strArray.insert(word);
		}
		cout << "\t " << i << " words imported." << endl;

		cout << "Going to display all those words " << endl;
		system("pause");
		strArray.show();

		cout << "Going to perform bubble sorting " << endl;
		system("pause");
		strArray.BubbleSort();
		strArray.show();

		cout << "Going to display size and capacity " << endl;
		system("pause");
		cout << "\t current size: " << strArray.getCurrentSize() << endl;
		cout << "\t capacity: " << strArray.getCapacity() << endl;

		string keyword = "yourself";
		cout << "Going to remove the word '" << keyword << "' " << endl;
		system("pause");
		bool result = strArray.remove(keyword);
		if (result == true)
		{
			cout << "\t " << keyword << " has been removed from array" << endl;
		}
		else
		{
			cout << "\t " << keyword << " is not existed in array" << endl;
		}

		cout << "\t current size: " << strArray.getCurrentSize() << endl;
		cout << "\t capacity: " << strArray.getCapacity() << endl;

		cout << "Going to clear all words " << endl;
		system("pause");
		strArray.clear();
		//strArray.show();
		cout << "\t current size: " << strArray.getCurrentSize() << endl;
		cout << "\t capacity: " << strArray.getCapacity() << endl;
	}
}

void main()
{
	// Show welcome message
	cout << "*************************************************************" << endl;
	cout << "*                  Welcome to -Lab 0                  *" << endl;
	cout << "*                     Student: Robert Tang                      *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*   This program will demonstrate Dynamic Array Container.  *" << endl;
	cout << "*************************************************************" << endl;

	//test1();

	testImportDataFile();

	system("pause");
}
