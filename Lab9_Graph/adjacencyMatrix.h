#include <iostream>

using namespace std;

template <class T>
class AdjacencyMatrix
{
private:
    int dist[N];        // distance
    bool visted[N];     // visted
    int prevVertex[N];  // previous vertex
    int (*matrix)[N];
    string (*name);
    const char delimiter = '|';

public:
    AdjacencyMatrix(string(*n), int (*m)[N] ) : name(n)
    {
        matrix = m;
        name = n;

        //for (int i = 0; i < N; i++)
        //{
        //    for (int j = 0; j < N; j++)
        //    {
        //        cout << matrix[i][j] << "\t";
        //    }
        //    cout << endl;
        //}

        /*for (int i = 0; i < N; i++)
        {
            cout << i << ": " << name[i] << endl;
        }*/


        //display();
        //system("pause");
    }

    ~AdjacencyMatrix()
    {
    }

    void shortestPath(int matrix[N][N], int src)
    {
        // init
        for (int i = 0; i < N; i++)
        {
            dist[i] = INT_MAX;
            visted[i] = false;
            prevVertex[i] = NULL;
        }

        // set distance of origin to origin as zero
        dist[src] = 0;

        for (int count = 0; count < N - 1; count++)
        {
            // find min index
            int min_index, min = INT_MAX;
            for (int v = 0; v < N; v++)
            {
                if (visted[v] == false && dist[v] <= min)
                {
                    min = dist[v], min_index = v;
                }
            }

            // set as visted
            visted[min_index] = true;


            // traversal min index's elements
            for (int v = 0; v < N; v++)
            {
                if (!visted[v]                                              // is not visted
                    && matrix[min_index][v]                                 // > 0
                    && dist[min_index] != INT_MAX                           // is not infinite
                    && dist[min_index] + matrix[min_index][v] < dist[v]     // less than current dist
                )
                {
                    dist[v] = dist[min_index] + matrix[min_index][v]; // update dist

                    prevVertex[v] = min_index;
                }
            }

        }

    }

    void print()
    {
        cout << setw(10) << left << "#"
             << setw(20) << "Destination"
             << setw(20) << "Shortest Distance"
             //<< setw(20) << "Parent"
             << setw(80) << "Shortest Path"
             << endl<< endl;

        for (int i = 0; i < N; i++)
        {
            cout << setw(10) << left << i+1
                 << setw(20) << name[i]
                 << setw(20) << dist[i]
                 //<< setw(20) << name[prevVertex[i]]
                 << setw(80) << paths(prevVertex[i], name[i] )
                 << endl;
        }
    }

    string paths(int index , string path = "")
    {
        //cout << "find :" << index << endl;

        path = name[index] + " > " + path; // name string D-4

        if (index>0)
        {

            //cout << ">> " << prevVertex[index] << endl;

            path = paths(prevVertex[index], path);
        }

        return path;
    }
};