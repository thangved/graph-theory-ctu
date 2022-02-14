#include <stdio.h>

#define MAX_M 100

typedef struct
{
    int n, m;
    int A[MAX_M][MAX_M];
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
    pG->m++;
}

Graph read_graph_from_keyboard()
{
    int n;
    scanf("%d", &n);

    Graph G;
    init_graph(&G, n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int edges;
            scanf("%d", &edges);
            for (int k = 0; k < edges; k++)
                add_edge(&G, i, j);
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

void print_adjacent(Graph *pG, int u)
{
    for (int i = 1; i <= pG->n; i++)
        for (int j = 0; j < pG->A[u][i]; j++)
            printf("%d ", i);
    printf("0\n");
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();
    for (int i = 1; i <= G.n; i++)
        print_adjacent(&G, i);
    return 0;
}