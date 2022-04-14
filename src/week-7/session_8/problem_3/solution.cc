#include <stdio.h>

#define MAX_NODE 100

typedef struct
{
    int n, m;
    int A[MAX_NODE][MAX_NODE];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v]++;
    pG->A[v][u]++;
    pG->m++;
}

Graph read_graph_from_keyboard()
{
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
    return G;
}

Graph read_graph_from_file(char *filepath)
{
    FILE *f = freopen(filepath, "r", stdin);
    Graph G = read_graph_from_keyboard();
    fclose(f);
    return G;
}

int marked[MAX_NODE];

int count_connected_node(Graph *pG, int x)
{
    if (marked[x])
        return 0;
    int count = 0;
    marked[x] = 1;
    count++;
    for (int i = 1; i <= pG->n; i++)
        if (pG->A[x][i])
            count += count_connected_node(pG, i);
    return count;
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    // Initial values
    for (int i = 1; i <= G.n; i++)
        marked[i] = 0;
    int u;
    scanf("%d", &u);

    printf("%d\n", count_connected_node(&G, u));
    return 0;
}