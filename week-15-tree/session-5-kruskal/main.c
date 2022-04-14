#include <stdio.h>

#define MAX_NODE 100
#define MAX_EDGE 100

typedef struct
{
    int u, v, w;
} Edge;
typedef struct
{
    int n, m, w;
    Edge edges[MAX_EDGE];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    pG->w = 0;
}

void add_edge(Graph *pG, int u, int v, int w)
{
    Edge e = {u, v, w};
    if (u > v)
    {
        e.u = v;
        e.v = u;
    }
    pG->edges[pG->m++] = e;
    pG->w += w;
}

void init_root(int parents[], int n)
{
    for (int u = 1; u <= n; u++)
        parents[u] = u;
}

int find_root(const int parents[], int u)
{
    while (u != parents[u])
        u = parents[u];
    return u;
}

void update_root(int parents[], int u, int v)
{
    parents[find_root(parents, v)] = find_root(parents, u);
}

void swap_edge(Edge *a, Edge *b)
{
    const Edge temp = *a;
    *a = *b;
    *b = temp;
}

void sort_edge(Graph *pG)
{
    for (int i = 0; i < pG->m - 1; i++)
    {
        int mid = i;
        for (int j = i + 1; j < pG->m; j++)
            if (pG->edges[j].w < pG->edges[mid].w)
                mid = j;
        swap_edge(&pG->edges[i], &pG->edges[mid]);
    }
}

void print_edges(const Graph *pG)
{
    for (int i = 0; i < pG->m; i++)
        printf("%d %d %d\n", pG->edges[i].u, pG->edges[i].v, pG->edges[i].w);
}

void kruskal(Graph *pG)
{
    sort_edge(pG);
    Graph T;
    init_graph(&T, pG->n);
    int parents[MAX_NODE];
    init_root(parents, pG->n);

    for (int i = 0; i <= pG->m && T.m != T.n - 1; i++)
    {
        int u = pG->edges[i].u;
        int v = pG->edges[i].v;
        int w = pG->edges[i].w;
        if (find_root(parents, u) == find_root(parents, v))
            continue;
        add_edge(&T, u, v, w);
        update_root(parents, u, v);
    }
    printf("%d\n", T.w);
    print_edges(&T);
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    kruskal(&G);
    return 0;
}