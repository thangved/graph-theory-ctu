#include <stdio.h>

#define MAX_NODE 1000
typedef struct
{
    int u, v; // đỉnh đầu v, đỉnh cuối v
    int w;    // trọng số w
} Edge;

typedef struct
{
    int n, m;             // n: đỉnh, m: cung
    Edge edges[MAX_NODE]; // các cung của đồ thị
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w)
{
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

void BellmanFord(const Graph *pG, int s, int t)
{
    int pi[MAX_NODE];
    for (int i = 0; i < MAX_NODE; i++)
        pi[i] = __INT_MAX__;

    pi[s] = 0;

    for (int i = 1; i < pG->n; i++)
    {
        for (int j = 0; j < pG->m; j++)
        {
            int u = pG->edges[j].u;
            int v = pG->edges[j].v;
            int w = pG->edges[j].w;

            if (pi[u] == __INT_MAX__)
                continue;

            if (pi[u] + w >= pi[v])
                continue;

            pi[v] = pi[u] + w;
        }
    }
    pi[t] != __INT_MAX__ ? printf("%d", pi[t]) : puts("?");
}

int busy[MAX_NODE];

int main()
{
    Graph G;
    int n, m;
    // FILE *f = freopen("./graph.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (int i = 1; i <= n; i++)
    {
        int b;
        scanf("%d", &b);
        busy[i] = b;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d", &u, &v);
        w = (busy[v] - busy[u]) * (busy[v] - busy[u]) * (busy[v] - busy[u]);
        add_edge(&G, u, v, w);
    }

    int s, t;
    scanf("%d%d", &s, &t);

    BellmanFord(&G, s, t);
    return 0;
}