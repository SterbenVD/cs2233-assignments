#include <bits/stdc++.h>
using namespace std;

// Class for Disjoint Sets
class DSets
{
public:
    int *parent, *rank;

    // Constructor for Disjoint Sets
    DSets(int psize)
    {
        parent = new int[psize + 1];
        rank = new int[psize + 1];
        for (int i = 0; i <= psize; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Finds parent of the set
    int root(int val)
    {
        while (val != parent[val])
            val = parent[val];
        return val;
    }

    // Merges two sets
    void merge(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
    }
};
// Class for Graph
class Graph
{
public:
    int nodes, edges;
    vector<pair<int, pair<int, int>>> vec_edge;

    // Constructor for Graph
    Graph(int pnodes)
    {
        nodes = pnodes;
        edges = 0;
    }

    // Prints all edges of the graph
    void display()
    {
        cout << "Edges:\n";
        for (int i = 0; i < edges; i++)
        {
            int x1 = vec_edge[i].second.first;
            int x2 = vec_edge[i].second.second;
            int weight = vec_edge[i].first;
            cout << x1 << "," << x2 << ". Weight: " << weight << "\n";
        }
    }

    // Inserts a edge into the graph
    void insert(int x1, int x2, int weight)
    {
        if (x1 > x2)
        {
            x1 += x2;
            x2 = x1 - x2;
            x1 -= x2;
        }
        vec_edge.push_back(make_pair(weight, make_pair(x1, x2)));
        edges++;
    }

    // Constructs Minimum Spanning Tree
    Graph *MST()
    {
        sort(vec_edge.begin(), vec_edge.end());
        Graph *ans = new Graph(nodes);
        DSets *kruskal = new DSets(nodes);
        int sum = 0;
        for (int i = 0; i < edges; i++)
        {
            if (ans->edges == nodes - 1)
                break;
            int x1 = vec_edge[i].second.first;
            int x2 = vec_edge[i].second.second;
            int weight = vec_edge[i].first;
            if (kruskal->root(x1) != kruskal->root(x2))
            {
                kruskal->merge(x1, x2);
                ans->insert(x1, x2, weight);
                sum += weight;
            }
        }
        cout << "Total sum of Weight: " << sum << "\n";
        return ans;
    }
};

// Interactive Program to ease debugging all operations.
int main()
{
    int nodes, edges;
    cout << "Enter number of nodes:";
    cin >> nodes;
    Graph *Fac = new Graph(nodes);
    cout << "Enter number of edges:";
    cin >> edges;
    cout << "Enter the node number as 1 to " << nodes << " while entering the edges\n";
    for (int i = 0; i < edges; i++)
    {
        int x1, x2, weight;
        cout << i + 1 << ") Enter the vec_edge and the weight: ";
        cin >> x1 >> x2 >> weight;
        Fac->insert(x1, x2, weight);
    }
    Graph *MST = Fac->MST();
    MST->display();
}