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

int p[MAX_NODE];
int pi[MAX_NODE];

void initialarray(int *arr, int initialvalue)
{
    for (int i = 0; i < MAX_NODE; i++)
        *(arr + i) = initialvalue;
}
void initial()
{
    initialarray(p, 0);
    initialarray(pi, __INT_MAX__);
}

int BellmanFord(const Graph *pG, int s)
{
    initial();
    pi[s] = 0;
    p[s] = -1;

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
            p[v] = u;
        }
    }

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

            return 1;
        }
    }

    return 0;
}

void printpath(int s, int t)
{
    int path[MAX_NODE];
    int len = 0;
    while (t != s)
    {
        path[len] = t;
        t = p[t];
        len++;
    }
    path[len] = s;
    for (; len != 0; len--)
        printf("%d -> ", path[len]);
    printf("%d", path[len]);
}

int main()
{
    Graph G;
    int n, m;
    // FILE *f = freopen("./graph.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int s, t;
    scanf("%d%d", &s, &t);

    BellmanFord(&G, s);
    printpath(s, t);
    return 0;
}