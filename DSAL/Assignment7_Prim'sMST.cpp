#include <iostream>
using namespace std;

class Graph
{
    int **q;
    int int_max = 999;
    int vertices;

public:
    Graph(int v)
    {
        vertices = v;
        q = new int *[vertices];

        for (int i = 0; i < vertices; i++)
        {
            q[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
            {
                q[i][j] = 0;
            }
        }
    }

    void link(int, int, int);
    void display();
    void primMST();
    int minKey(int key[], bool mstSet[]);
    void printMST(int parent[]);
};

void Graph::primMST()
{
    int parent[vertices]; // to store constructed MST
    int key[vertices];    // key values used to pick minimum weight edge in cut
    bool mstSet[vertices];
    int total_cost = 0; // to represent set of vertices not yet included in MST

    for (int i = 0; i < vertices; i++)
    {
        key[i] = int_max;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < vertices; v++)
        {
            if (q[u][v] != 0 && mstSet[v] == false && q[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = q[u][v];
            }
        }
    }
    printMST(parent);
    cout << "\n"
         << "Total cost of MST: ";
    for (int i = 1; i < vertices; i++)
    {
        total_cost += q[i][parent[i]];
    }
    cout << total_cost << endl;
}

void Graph::link(int a, int b, int weight)
{
    q[a][b] = weight;
    q[b][a] = weight;
}

void Graph::display()
{
    for (int j = 0; j < vertices; j++)
    {
        if (j != vertices - 1)
        {
            if (j == 0)
                cout << "  " << j;
            else
                cout << " " << j;
        }
        else
        {
            cout << " " << j << endl;
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        cout << i << " ";
        for (int j = 0; j < vertices; j++)
        {
            if (j != vertices - 1)
            {
                cout << q[i][j] << " ";
            }
            else
            {
                cout << q[i][j] << endl;
            }
        }
    }
}

int Graph::minKey(int key[], bool mstSet[])
{
    int min = int_max;
    int min_index;
    for (int v = 0; v < vertices; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void Graph::printMST(int parent[])
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < vertices; i++)
    {
        cout << parent[i] << " - " << i << " \t" << q[i][parent[i]] << " \n";
    }
}

int main()
{
    int numVertices;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    Graph g(numVertices);

    int choice;
    int a, b, weight;
    while (true)
    {
        cout << "\n1. Link vertices";
        cout << "\n2. Display the graph";
        cout << "\n3. Find Minimum Spanning Tree (MST)";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter the vertices to link: ";
            cin >> a >> b;
            cout << "Enter the weight: ";
            cin >> weight;
            g.link(a, b, weight);
            cout << "Vertices linked successfully!";
            break;
        case 2:
            cout << "\nGraph:" << endl;
            g.display();
            break;
        case 3:
            cout << "\nMinimum Spanning Tree (MST):" << endl;
            g.primMST();
            break;
        case 4:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}