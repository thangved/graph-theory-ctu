#include <stdio.h>

#define INFINITY __INT_MAX__
#define NO_EDGE INFINITY
#define MAX_NODE 100

typedef struct
{
    int n, m;
    int W[MAX_NODE][MAX_NODE];
} Graph;

Graph init_graph(int n)
{
    Graph G;
    G.n = n;
    G.m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G.W[i][j] = NO_EDGE;
    return G;
}

void add_edge(Graph *pG, int u, int v, int w)
{
    pG->W[u][v] = w;
    pG->W[v][u] = w;
    pG->m++;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G = init_graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    return 0;
}