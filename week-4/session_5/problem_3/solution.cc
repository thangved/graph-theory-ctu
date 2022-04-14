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

#include <stdio.h>

Graph read_graph_from_file(char *filepath)
{
    FILE *f = freopen(filepath, "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    Graph G;
    init_graph(&G, n);

    for (; m != 0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    fclose(f);
    return G;
}

int main()
{
    Graph G = read_graph_from_file((char *)"./dt.txt");
    for (int i = 1; i <= G.n; i++)
        printf("deg(%d) = %d\n", i, degree(&G, i));

    return 0;
}