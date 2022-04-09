#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct
{
    int u, v, w;
    bool active;
} Edge;

typedef struct
{
    int n, m;
    vector<Edge> edges;
} Graph;

void initgraph(Graph &G, int n)
{
    G.n = n;
    G.m = 0;
}

void addedge(Graph &G, int u, int v, int w)
{
    Edge e = {u, v, w, false};
    G.edges.push_back(e);
    G.m = G.edges.size();
}

void popedge(Graph &G)
{
    G.edges.pop_back();
    G.m = G.edges.size();
}

void printedges(const Graph &G)
{
    cout << "#\tu\tv\tw\tadd" << endl;
    int i = 1;
    for (auto edge = G.edges.begin(); edge != G.edges.end(); edge++)
    {
        cout << i++ << "\t";
        cout << edge->u << "\t" << edge->v << "\t" << edge->w << "\t" << (edge->active ? "x" : "no") << endl;
    }
}

bool compare(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}

int findroot(int parents[], int u)
{
    while (u != parents[u])
        u = parents[u];

    return u;
}

void kruskal(Graph &G)
{
    int parents[100];

    sort(G.edges.begin(), G.edges.end(), compare);
    Graph T;
    initgraph(T, G.n);
    for (int i = 1; i <= T.n; i++)
        parents[i] = i;

    for (auto edge = G.edges.begin(); edge != G.edges.end(); edge++)
    {
        int ru = findroot(parents, edge->u);
        int rv = findroot(parents, edge->v);
        if (ru == rv)
            continue;
        addedge(T, edge->u, edge->v, edge->w);
        parents[rv] = parents[ru];
        edge->active = true;
    }

    printedges(G);
}
int main()
{
    ifstream f = ifstream("./g2.txt");
    int n;
    f >> n;
    Graph G;
    initgraph(G, n);
    int u, v, w;
    while (f >> u >> v >> w)
        addedge(G, u, v, w);
    kruskal(G);
    f.close();

    return 0;
}
