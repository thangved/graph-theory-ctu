#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct
{
    int u, v, w;
    bool active;
    int root_u, root_v;
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

void printedges(const Graph &G, bool character = false)
{
    const string divider = "+-------------------------------------------------------+\n";
    cout << divider;
    cout << "| #\tu\tv\tw\troot_u\troot_v\tadd\t|" << endl;
    cout << divider;
    int i = 1;
    for (auto edge = G.edges.begin(); edge != G.edges.end(); edge++)
    {
        cout << "| " << i++ << "\t";
        if (character)
            cout << (char)(edge->u + 'A' - 1) << "\t" << (char)(edge->v + 'A' - 1);
        if (!character)
            cout << edge->u << "\t" << edge->v;
        cout << "\t" << edge->w << "\t";
        if (character)
            cout << (char)(edge->root_u + 'A' - 1) << "\t" << (char)(edge->root_v + 'A' - 1);
        if (!character)
            cout << edge->root_u << "\t" << edge->root_v;

        cout << "\t" << (edge->active ? "x" : "no") << "\t|" << endl;
        cout << divider;
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

void printdivider(int n)
{
    cout << "+-";
    for (int i = 0; i < n; i++)
        cout << "---------";
    cout << "-+" << endl;
}

void printparents(const int parents[], int n)
{
    printdivider(n);
    cout << "| \t";
    for (int i = 1; i <= n; i++)
        cout << i << "\t";
    cout << " |\n";
    printdivider(n);
    cout << "| \t";
    for (int i = 1; i <= n; i++)
        cout << parents[i] << "\t";
    cout << " |\n";
    printdivider(n);
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
        edge->root_u = ru;
        edge->root_v = rv;
        if (ru == rv)
            continue;
        addedge(T, edge->u, edge->v, edge->w);
        parents[rv] = parents[ru];
        edge->active = true;
    }

    printedges(G, true);
    printparents(parents, G.n);
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
