///////////////////////////////////////////////////////////
//  DynamicArrayContainer.cpp
//  Implementation for dynamic array
//  Student: Robert Tang
///////////////////////////////////////////////////////////

// Create a "Dynamic Array" container with this user interface:
// * Implement dynamic resizing using this algorithm:
// 1.Starting with a dynamic size of 10, if the number of elements exceed this number :
//	a.Reallocate the container size to double the current size
//	b.Move the contents of the current container to the newly sized container
//	c.Delete the previously sized container.
// 2.Repeat from step 1a. as necessary.
// 3.Note the data file called "Words.CSV" is in the documents folder for this week.
// 4.Read the data file and store the words in the dynamic array.

//#ifndef LAB0_001
//#define LAB0_001

#include <iostream>
using namespace std;

// Definition Begin #######################################################################################
template <class T>
class DynamicArray
{
private:
	T *arrayPt;

	int capacity; // capacity

	int count = 0;

public:
	DynamicArray(int size);
	~DynamicArray();

	// Gets the current number of entries in container
	int getCurrentSize()
	{
		return count;
	}

	// Returns the current capacity of the container
	int getCapacity()
	{
		return capacity;
	}

	// Checks whether the container is empty.
	bool isEmpty()
	{
		return count == 0 ? true : false;
	}

	// Adds a new entry to the container
	bool insert(T newEntry);

	// Removes an entry from the container and moves all entries above anEntry down one
	bool remove(T anEntry);

	// Get index value
	T getValue(int index);

	// Removes all entries from the container
	void clear();

	// Resize a container by doubling current capacity
	int resize();

	// Studen added extra functions
	// Show all entries
	void show();

	// Bubble sort
	void BubbleSort()
	{
		int x, y;
		int n = 0;
		for (x = 1; x < count; ++x)
		{
			for (y = count - 1; y >= x; --y)
			{
				n++;

				if (arrayPt[y - 1] > arrayPt[y])
				{
					Exchange(arrayPt[y], arrayPt[y - 1]);
				}
			}
		}
		//cout << "N: " << n << endl;
		//system("pause");
	}

	// Swap
	void Exchange(T &a, T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}
};

//#endif
// Definition End #######################################################################################

// Implementation BEGIN #################################################################################
// Default constructor
template <class T>
DynamicArray<T>::DynamicArray(int size)
{
	capacity = size;

	arrayPt = new T[size];
}

// Default destructor
template <class T>
DynamicArray<T>::~DynamicArray()
{
	delete[] arrayPt;
}

// Adds a new entry to the container
template <class T>
bool DynamicArray<T>::insert(T newEntry)
{
	if (count >= capacity)
	{
		resize();
	}
	arrayPt[count] = newEntry;
	count++;

	return true;
}

// Show all entries
template <class T>
void DynamicArray<T>::show()
{
	cout << "show all elements:" << endl;

	if (isEmpty())
	{
		cout << "array is empty" << endl;
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << "\t" << getValue(i) << endl;
		}
	}
}

// Resize a container by doubling current capacity
template <class T>
int DynamicArray<T>::resize()
{
	const int newSize = capacity * 2;
	T *ptemp = new T[newSize];
	for (int i = 0; i < count; i++)
	{
		ptemp[i] = arrayPt[i];
	}

	delete[] arrayPt;
	arrayPt = ptemp;
	capacity = newSize;

	return newSize;
}

// Get index value
template <class T>
T DynamicArray<T>::getValue(int index)
{
	return arrayPt[index];
}

// Removes all entries from the container
template <class T>
void DynamicArray<T>::clear()
{
	delete[] arrayPt;

	capacity = 10;
	arrayPt = new T[capacity];

	count = 0;
}

// Removes an entry from the container and moves all entries above anEntry down one
template <class T>
bool DynamicArray<T>::remove(T anEntry)
{
	int index;
	bool flagWordFound = false;

	// find enter
	for (int i = 0; i < count; i++)
	{
		if (arrayPt[i] == anEntry)
		{
			index = i;
			flagWordFound = true;
			//cout << "found: " << anEntry << " at " << i << endl;
		}
	}

	// moves all entries above anEntry down one
	// not sure above an entery is greater than or less than (index < x OR index > x)?
	if (flagWordFound == true)
	{
		int i;
		for (i = index; i < count; i++)
		{
			arrayPt[i] = arrayPt[i + 1];
		}

		arrayPt[i] = ""; // remove last one from array
		count--;

		return true;
	}
	else
	{
		return false;
	}
}
// Implementation End #################################################################################
