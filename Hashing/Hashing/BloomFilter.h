#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#ifndef _BLOOMFILTER
#define _BLOOMFILTER

// definition begin **********************************************************************************
template <class K>
class BloomFilter
{
private:
    bool *table; // bucket array
    int n = 69903;
    int k = 3; // number of hash functions
    const int m = n * k;

    int num; // number of entries
public:
    BloomFilter() // constructor
    {
        table = new bool[m];

        for (int i = 0; i < m; i++)
        {
            table[i] = 0;
        }
    }

    ~BloomFilter()
    {
        clear();
    }

    void menu()
    {
        cout << "************************************************************************************************" << endl;
        cout << "*                         Welcome to Group Project                                      *" << endl;
        cout << "*                                 Student: Robert Tang                                             *" << endl;
        cout << "*                  Group: Soham Pardeshi, Ben Fong, Samantha Seymour                           *" << endl;
        cout << "*                                                                                              *" << endl;
        cout << "* This program will demonstrate:                                                               *" << endl;
        cout << "*  + Bloom Fileter                                                                             *" << endl;
        cout << "*                                                                                              *" << endl;
        cout << "* Choices:                                                                                     *" << endl;
        cout << "*  0) Back to main menu                                                                        *" << endl;
        cout << "*  1) Import Data                                                                              *" << endl;
        cout << "*  2) Dispaly filter                                                                           *" << endl;
        cout << "*  3) Find a word                                                                              *" << endl;
        cout << "*  4) Test all                                                                                 *" << endl;
        cout << "*  5) Get current size                                                                         *" << endl;
        cout << "************************************************************************************************" << endl;

        //cout << ceil((m / n) * log(2)) << endl;
    }

    void main()
    {
        string file = "words.txt";
        bool exit = false;
        int input;

        do
        {
            system("cls");
            menu(); // Show welcome message
            cout << "Please enter your choice [0-5]:";
            cin >> input;

            if (input == 1)
            {
                importDataFile(file);
                system("pause");
            }
            else if (input == 2)
            {
                display();
                system("pause");
            }
            else if (input == 3)
            {
                bool cont = true;
                string key;
                cin.ignore(INT_MAX, '\n');

                do
                {
                    cout << "Please enter a word in lowercase [Enter x to exit]: ";
                    getline(cin, key);
                    key = trim(key);

                    if (key != "x")
                    {
                        if (contains(key))
                        {
                            cout << "Found" << endl;
                        }
                        else
                        {
                            cout << "Not found" << endl;
                        }
                    }
                    else
                    {
                        cont = false;
                    }
                } while (cont);
                system("pause");
            }
            else if (input == 4)
            {
                testAll("words2.txt");
                system("pause");
            }
            else if (input == 5)
            {
                cout << "Current size: " << size() << endl;
                system("pause");
            }
            else
            {
                exit = true;
            }
        } while (exit != true);
    }

    void add(K key) // insert
    {
        unsigned int hash1 = hashFunc1(key);
        unsigned int hash2 = hashFunc2(key);
        unsigned int hash3 = hashFunc3(key);

        //cout << "hash: "
        //    << setw(20) << hash1
        //    << setw(20) << hash2
        //    << setw(20) << hash3
        //    << endl; system("pause");

        table[hash1] = 1;
        table[hash2] = 1;
        table[hash3] = 1;
    }

    bool contains(K key) // find entry with key k
    {
        unsigned int hash1 = hashFunc1(key);
        unsigned int hash2 = hashFunc2(key);
        unsigned int hash3 = hashFunc3(key);

        //cout << "hash: " << hash1 << hash2 << hash3 << endl; system("pause");
        if (table[hash1] == 1 && table[hash2] == 1 && table[hash3] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int hashFunc(K &k) // hash function
    {
        int sum = 0;
        int len = k.length();
        int val;

        for (int i = 0; i < len; i++)
        {
            val = k[i];
            sum += (val + 3) * 7;
            //cout << k[i] << " = " << val << " * 7" << endl;
        }

        //cout << sum << endl;
        //system("pause");
        //return sum;

        return (sum % m);
    }

    int hashFunc1(string k)
    {
        unsigned int seed = 7;
        unsigned int hash = 131;
        unsigned int i = 0;
        unsigned int len = k.length();
        const char *str = k.c_str();

        for (i = 0; i < len; str++, i++)
        {

            hash = (hash * seed) + (*str);
            seed *= 7;

            //cout << "*str: " << *str << " hash:" << hash << endl; system("pause");
        }

        //cout << hash << " % " << m << " = " << (hash % m) << endl; system("pause");
        return hash % m;
    }

    int hashFunc2(string k) // hash function
    {
        unsigned int b = 378551;
        unsigned int a = 63689;
        unsigned int hash = 0;
        unsigned int i = 0;
        unsigned int len = k.length();
        const char *str = k.c_str();

        for (i = 0; i < len; str++, i++)
        {
            hash = hash * a + (*str);
            a = a * b;
        }

        return hash % m;
    }

    int hashFunc3(K &str)
    {
        unsigned int len = str.length();
        unsigned int hash = 5381;
        unsigned int i = 0;

        for (i = 0; i < len; i++)
        {
            hash = ((hash << 5) + hash) + (str[i]);
        }

        return hash % m;
    }

    void display() // Print hash table
    {
        int used = 0;

        for (int i = 0; i < m; i++)
        {
            cout << "| " << i << " | " << table[i] << endl;

            if (table[i] == 1)
            {
                used++;
            }
        }

        cout << used << " of " << m << " used. " << endl;
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
        for (int i = 0; i < m; i++)
        {
        }
    }

    int string2ascii(string str)
    {
        int sum = 0;
        for (unsigned int i = 0; i < str.size(); i++)
        {
            sum += str[i];
        }

        return sum;
    }

    string trim(string str)
    {
        size_t p = str.find_first_not_of(" \t");

        str.erase(0, p);

        p = str.find_last_not_of(" \t");

        if (string::npos != p)
        {
            str.erase(p + 1);
        }

        return str;
    }

    string *csv2arr(string line)
    {
        char delimiter = ',';
        const int SIZE = 2;
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

    void importDataFile(string file)
    {
        fstream datafile;
        string line; // *item;
        int TITLE_INDEX = 0, VALUE_INDEX = 1;
        int progress = 0;

        datafile.open(file);
        if (datafile.fail())
        {
            cout << "Error: couldn't open the data file '" << file << "'." << endl;
            system("pause");
            exit(0);
        }
        else
        {
            num = 0;
            cout << setprecision(2) << fixed;

            while (getline(datafile, line))
            {
                //item = csv2arr(line); // parse csv string to array
                //v = atof(item[1].c_str());
                // typeid(v).name()
                add(line);
                //cout << item[0] << "\t" << v << endl;
                num++;

                if (num % (n / 100) == 0)
                {
                    progress++;
                    cout << "\r" << progress << "% - " << num; //system("pause");
                }
            }

            cout << "\r " << num << " words imported." << endl; //system("pause");
        }
    }

    void testAll(string file)
    {
        fstream datafile;
        string line; // , *item;
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
            if (size() < 1)
            {
                cout << "Please import data file first." << endl;
                return;
            }

            int errorNum = 0, row = 0;
            string result;
            while (getline(datafile, line))
            {
                if (this->contains(line))
                {
                    result = "found";
                }
                else
                {
                    result = "not found";
                    errorNum++;
                    //system("pause");
                }

                row++;

                cout << setw(30) << left << line << setw(20) << result << endl;
            }

            cout << "Total errors: " << errorNum << " of " << row << endl;
        }
    }
};
#endif