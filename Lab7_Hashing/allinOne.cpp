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

// #include "Hashing.h"

#ifndef _CIS22C_HASHING
#define _CIS22C_HASHING

#include <iostream>
using namespace std;

// definition begin **********************************************************************************
// Node class
template <class K, class V>
class Entry
{
    K key;
    V value;

public:
    Entry<K, V> *left;
    Entry<K, V> *right;

    // Constructors
    Entry()
    {
        left = nullptr;
        right = nullptr;
    }

    Entry(K aKey, V aVal)
    {
        key = aKey;
        value = aVal;

        left = nullptr;
        right = nullptr;
    }

    K getKey()
    {
        return this->key;
    }

    V getValue()
    {
        return this->value;
    }

    //friend class HashMap;
};

// Interface of PriorityQueue
template <class K, class V, class H>
class HashMap
{
private:
    int capacity;
    int num;             // number of entries
    string askey;        // indicate which field as key
    Entry<K, V> **table; // bucket array

public:
    //typedef Entry<const K, V> Entry;    // a (key,value) pair

    HashMap(int size) // constructor
    {
        capacity = size;
        table = new Entry<K, V> *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }

    H hashFunc(K &k) // hash function
    {
        int len = k.length(), sum = 0;
        string str = "";
        int val;

        for (int i = 0; i < len; i++)
        {
            val = int(k[i]) * int(k[0]) + 7;
            sum += val;
            //cout << k[i] << " = " << val << endl;
        }
        //sum = atoi(str.c_str());
        //cout << str << endl;
        //cout << sum << endl;
        //system("pause");

        return (sum % capacity);
    }

    H hashFunc4(K &k) // hash function
    {
        int len = k.length(), sum;
        string str = "";
        string val;

        for (int i = 0; i < len; i++)
        {
            val = to_string(int(k[i]));
            str += val;
            //cout << k[i] << " = " << val << endl;
        }
        sum = atoi(str.c_str());
        //cout << str << endl;
        //cout << sum << endl;
        //system("pause");

        return (sum % capacity);
    }

    H hashFunc2(K &k) // hash function
    {
        int sum = 0;
        for (char c : k)
        {
            sum += c;
        }

        return sum % capacity;
    }

    H hashFunc3(K &str)
    {
        unsigned int len = str.length();
        unsigned int hash = 5381;
        unsigned int i = 0;

        for (i = 0; i < len; i++)
        {
            hash = ((hash << 5) + hash) + (str[i]);
        }

        return hash % capacity;
    }

    void put(K key, V value) // insert/replace (k,v)
    {
        H hash = hashFunc(key);
        //cout << "hash: " << hash << endl; system("pause");

        if (table[hash] == NULL)
        {
            table[hash] = new Entry<K, V>(key, value);
            num++;
        }
        else
        {
            //cout << "collection happened at " << hash << " for " << key << " with " << table[hash]->getKey() << endl; system("pause");
            Entry<K, V> *entryPtr = table[hash];

            bool cont = true;

            do
            {
                if (entryPtr->getKey() < key) //  To left
                {
                    if (entryPtr->left == NULL)
                    {
                        entryPtr->left = new Entry<K, V>(key, value);
                        num++;
                        cont = false;
                    }
                    else
                    {
                        entryPtr = entryPtr->left;
                    }
                }
                else // To right
                {
                    if (entryPtr->right == NULL)
                    {
                        entryPtr->right = new Entry<K, V>(key, value);
                        num++;
                        cont = false;
                    }
                    else
                    {
                        entryPtr = entryPtr->right;
                    }
                }
            } while (cont && entryPtr != NULL);
        }
    }

    V operator[](K k)
    {
        return get(k);
    }

    V operator[](int index)
    {
        if (table[index])
        {
            return table[index]->getValue();
        }

        return "";
    }

    V get(K key) // find entry with key k
    {
        H hash = hashFunc(key);
        if (table[hash] != NULL)
        {
            Entry<K, V> *entryPtr = table[hash];
            bool cont = true;
            K entryKey;

            do
            {
                entryKey = entryPtr->getKey();

                if (entryKey == key)
                {
                    return entryPtr->getValue();
                }
                else if (entryKey < key) //  To left
                {
                    entryPtr = entryPtr->left;
                }
                else // To right
                {
                    entryPtr = entryPtr->right;
                }

            } while (entryPtr != NULL);
        }

        return "";
    }

    void display() // Print hash table
    {
        int totalRow = capacity, used = 0, collision = 0;
        //double usagePercentage, collisionPercentage;

        for (int i = 0; i < capacity; i++)
        {
            cout << "| " << i << " | ";

            if (table[i] == NULL)
            {
                cout << "NULL";
            }
            else
            {
                used++;
                cout << "(root)";
                traversal(table[i], collision);
            }
            cout << endl;
        }

        cout << "Total: " << totalRow << " rows; Usage:" << used << "; Collision: " << collision << endl;
    }

    void traversal(Entry<K, V> *entryPtr, int &collision)
    {
        if (entryPtr)
        {
            cout << entryPtr->getKey() << ":" << entryPtr->getValue() << " | ";

            if (entryPtr->left != NULL)
            {
                collision++;
                cout << "(<<< left)";
                traversal(entryPtr->left, collision);
            }

            if (entryPtr->right != NULL)
            {
                collision++;
                cout << "(right >>>)";
                traversal(entryPtr->right, collision);
            }
        }
    }

    int size() const // number of entries
    {
        return num;
    }

    bool empty() const // is the map empty
    {
        return num == 0;
    }

    void clear() // clear hash table
    {
        for (int i = 0; i < capacity; i++)
        {
            if (table[i] != NULL)
            {
                removeTree(table[i]);
                table[i] = NULL;
            }
        }

        num = 0;
    }

    void removeTree(Entry<K, V> *entryPtr)
    {
        if (entryPtr)
        {
            removeTree(entryPtr->left);
            removeTree(entryPtr->right);
        }

        delete entryPtr;
    }

    string *csv2arr(string line)
    {
        char delimiter = ',';
        const int SIZE = 3;
        string str, *ret = new string[SIZE];

        istringstream is(line); // Input string stream

        int i = 0;
        while (getline(is, str, delimiter))
        {
            ret[i] = str;
            i++;
        }

        return ret;
    }

    void importDataFile(string file, string askey = "id")
    {
        this->askey = askey;
        fstream datafile;
        string line, *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int row = 0;
            string name, id;
            while (getline(datafile, line))
            {
                item = csv2arr(line); // parse csv string to array
                name = item[0] + " " + item[1];
                id = item[2];
                //v = atof(item[1].c_str()); // string to double
                // typeid(v).name()

                if (askey == "name")
                {
                    put(name, id);
                    //cout << setw(5) << left << "Key: " << setw(20) << name
                    //    << setw(5) << "Value: " << setw(20) << id
                    //    << setw(20) << "Value from hashtable:" << setw(20) << this->get(name) << endl;
                    //system("pause");
                }
                else
                {
                    put(id, name);
                    //cout << setw(5) << left << "Key: " << setw(20) << id
                    //    << setw(5) << "Value: " << setw(20) << name
                    //    << setw(20) << "Value from hashtable:" << setw(20) << this->get(id) << endl;
                    //system("pause");
                }

                row++;
            }

            //cout << "\t " << List.getCurrentSize() << " words imported." << endl; //system("pause");
        }
    }

    void testAll(string file)
    {
        fstream datafile;
        string line, *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;

        //cout << "askey:" << askey << endl; system("pause");

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int errorNum = 0, hashVal;
            V v, v2;
            string name, result;
            while (getline(datafile, line))
            {
                item = csv2arr(line); // parse csv string to array
                if (askey == "name")
                {
                    name = item[0] + " " + item[1];
                    v = item[2];
                    v2 = this->get(name);

                    if (v == v2)
                    {
                        result = "OK";
                    }
                    else
                    {
                        result = "Duplicate Key";
                    }

                    hashVal = this->hashFunc(item[0] + item[1]);

                    cout << setw(30) << item[0] + " " + item[1] << setw(30) << hashVal << setw(20) << v << setw(20) << v2 << setw(20) << result << endl;

                    if (v != v2)
                    {
                        errorNum++;
                    }
                }
                else // id as key
                {
                    v = item[0] + " " + item[1];
                    v2 = this->get(item[2]);
                    hashVal = this->hashFunc(item[2]);

                    if (v == v2)
                    {
                        result = "OK";
                    }
                    else
                    {
                        result = "fail";
                    }

                    cout << setw(8) << left << "key:" << setw(20) << item[2]
                         << setw(8) << left << "hash:" << setw(20) << hashVal
                         << setw(8) << left << "value:" << setw(20) << v
                         << setw(20) << left << "value from hash table: " << setw(20) << v2
                         << setw(20) << left << result << endl;

                    if (v != v2)
                    {
                        errorNum++;
                    }
                }
            }

            cout << "Total rows of duplicate: " << errorNum << endl;
        }
    }

    void testHash(string file)
    {
        fstream datafile;
        string line, *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            int errorNum = 0;
            K key;
            int v;
            string result;
            while (getline(datafile, line))
            {
                item = csv2arr(line); // parse csv string to array
                key = item[0] + item[1];
                v = hashFunc(key);

                cout << setw(30) << key << setw(20) << v << endl;
            }
        }
    }

    ~HashMap()
    {
        clear();
    }
};

#endif
// definition end **********************************************************************************

using namespace std;

void menu()
{
    cout << "************************************************************************************************" << endl;
    cout << "*                              Welcome to Lab7 - Hashing                              *" << endl;
    cout << "*                                 Student: Robert Tang                                             *" << endl;
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
    cout << "*  4) Dispaly hash tree                                                                        *" << endl;
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
