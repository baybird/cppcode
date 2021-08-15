
#include<iostream>
using namespace std;


class BinarySearchTree
{
	int size;
	int* array;

public:
	BinarySearchTree(int s) : size(s)
	{
		size = reSize(size);
		array = new int[size];
		for (int x = 0; x < size; x++) 
			array[x] = NULL;
	}

    double reSize(int x)
	{
		double value = pow(2, x);
		return value;
	}

	void insert(int x) 
	{
		int currentIndex = 0;
		cout << "insert: " << x;
		while (true) 
		{
			if (array[currentIndex] == NULL) 
			{
				array[currentIndex] = x;
				cout << " Inserted at index: " << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				currentIndex = (2 * currentIndex + 1);
                cout << " <<< Left (" << currentIndex << ")" << endl;
			}
			else  
			{
				currentIndex = (2 * currentIndex + 2);
                cout << " Right >>> ";
			}
		}
	}

	void search(int x) 
	{
		cout << "Search: " << x << endl;
		int currentIndex = 0;
		while (true) 
		{
			if (array[currentIndex] == NULL) 
			{
				cout << "Not Found" << endl;
				break;
			}
			if (array[currentIndex] == x) 
			{
				cout << "Found at index: " << currentIndex << endl;
				break;
			}
			else if (x < array[currentIndex]) 
			{
				cout << " <<< Left " << endl;
				currentIndex = (2 * currentIndex + 1);
			}
			else 
			{
				cout << " >>> Right " << endl;
				currentIndex = (2 * currentIndex + 2);
			}
		}
	}

	void parent(int x) 
	{
		while (x != 0) 
		{
			x = (x - 1) / 2;
			cout << "---|";
		}
	}
	void inOrder(int currentIndex) 
	{
		if (array[currentIndex] != NULL) 
		{
			inOrder(2 * currentIndex + 1);
			parent(currentIndex);
			cout << array[currentIndex] << endl;
			inOrder(2 * currentIndex + 2);
		}
	}
	void preOrder(int currentIndex)
	{
		if (array[currentIndex] != NULL)
		{
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
			preOrder(2 * currentIndex + 1);
			preOrder(2 * currentIndex + 2);
		}
	}
	void postOrder(int currentIndex) 
	{
		if (array[currentIndex] != NULL) 
		{
			postOrder(2 * currentIndex + 1);
			postOrder(2 * currentIndex + 2);
			parent(currentIndex);
			cout << array[currentIndex] << " " << endl;
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
};




