// A C / C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <iostream>
#include <stdio.h>
#include <limits.h>

// Number of vertices in the graph
#define V 5
using namespace std;

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool visted[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    cout << "find min from dist[]: " << endl;
    for (int v = 0; v < V; v++)
    {
        cout << v << " : " << dist[v] << endl;
        if (visted[v] != false)
        {
            cout << "\t" << v << " visted" << endl;
        }
        else if (!(dist[v] <= min))
        {
            cout << "\t" << dist[v] << " > " << min << endl;
        }
        else
        {
            min = dist[v], min_index = v;
        }
    }

    cout << "min_index: " << min_index << endl;
    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t\t %d\n", i, dist[i]);

   cout << "------------------------" << endl;
}

void display(int graph[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << graph[i][j] << "\t";
        }

        cout << endl;
    }
    cout << "------------------------" << endl;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
     int dist[V];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool visted[V]; // visted[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < V; i++)
     {
        dist[i] = INT_MAX;
        visted[i] = false;
     }
        

     // Distance of source vertex from itself is always 0
     dist[src] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < V; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, visted);
       cout << "row:" << count << ", minimum distance u: " << u << endl;
       

       // Mark the picked vertex as processed
       visted[u] = true;

       // show visted
       cout << "visted:" << endl;
       for (int i = 0; i < V; i++)
       {
           cout << i << ":" << visted[i] << endl;
       }

       // Update dist value of the adjacent vertices of the picked vertex.
       cout << endl;
       for (int v = 0; v < V; v++)
       {
            // Update dist[v] only if is not in visted, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            
            if (visted[v])
            {
                cout << v << " visted" << endl;
            }
            else if (dist[u] == INT_MAX )// not modified
            {
                cout << v << " modified" << endl;
            }
            else if (!graph[u][v])
            {
                cout << v << " value not set" << endl;
            }
            else if (!(dist[u] + graph[u][v] < dist[v]))
            {
                cout << v << ": " << dist[u] << "+" << graph[u][v] << " = " << (dist[u] + graph[u][v]) << " >= " << dist[v] << endl;
            }
            else
            {
                dist[v] = dist[u] + graph[u][v];
                cout << v << ": dist[" << v << "] = " << dist[u] << " + " << graph[u][v] << endl;
            }
                       
       }

       //display(graph);
       
       printSolution(dist, V);
       system("pause");

            
     }

     // print the constructed distance array
     printSolution(dist, V);
}


// driver program to test above function
int main()
{
   /* Let us create the example graph discussed above */
   //int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
   //                   {4, 0, 8, 0, 0, 0, 0, 11, 0},
   //                   {0, 8, 0, 7, 0, 4, 0, 0, 2},
   //                   {0, 0, 7, 0, 9, 14, 0, 0, 0},
   //                   {0, 0, 0, 9, 0, 10, 0, 0, 0},
   //                   {0, 0, 4, 14, 10, 0, 2, 0, 0},
   //                   {0, 0, 0, 0, 0, 2, 0, 1, 6},
   //                   {8, 11, 0, 0, 0, 0, 1, 0, 7},
   //                   {0, 0, 2, 0, 0, 0, 6, 7, 0}
   //                  };

    int graph[V][V] = { 
    { 0, 3, 0, 1, 0 },
    { 3, 0, 2, 5, 2 },
    { 0, 2, 0, 0, 5 },
    { 1, 2, 0, 0, 1 },
    { 0, 2, 5, 1, 0 },
    };

    dijkstra(graph, 0);

    system("pause");
    return 0;
}