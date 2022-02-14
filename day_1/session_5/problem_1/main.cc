#define MAX_EDGES 100

typedef struct
{
    int u, v;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_EDGES];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    Edge edge = {u, v};
    pG->edges[pG->m] = edge;
    pG->m++;
}

int degree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 0; i < pG->m; i++)
    {
        deg += pG->edges[i].u == u;
        deg += pG->edges[i].v == u;
    }
    return deg;
}