#include <stdio.h>

#define MAX_NODE 100
#define NO_EDGE -1

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
            pG->A[i][j] = NO_EDGE;
}

void add_edge(Graph *pG, int u, int v, int w)
{
    pG->A[u][v] = w;
    pG->A[v][u] = w;
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
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
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

int p[MAX_NODE];
int pi[MAX_NODE];
int d[MAX_NODE];

void initialarray(int *arr, int initialvalue)
{
    for (int i = 0; i < MAX_NODE; i++)
        *(arr + i) = initialvalue;
}
void initial()
{
    initialarray(p, 0);
    initialarray(pi, __INT_MAX__);
    initialarray(d, 0);
}

void findpath(Graph *pG, int s)
{
    pi[s] = 0;
    p[s] = -1;

    for (int i = 1; i < pG->n; i++)
    {
        int minindex = 0;
        for (int j = 1; j <= pG->n; j++)
            if (!d[j] && pi[minindex] > pi[j])
                minindex = j;

        d[minindex] = 1;

        for (int j = 1; j <= pG->n; j++)
        {
            if (pG->A[minindex][j] == NO_EDGE)
                continue;

            if (pi[minindex] + pG->A[minindex][j] < pi[j])
            {
                p[j] = minindex;
                pi[j] = pi[minindex] + pG->A[minindex][j];
            }
        }
    }
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    initial();

    findpath(&G, 1);

    for (int i = 1; i <= G.n; i++)
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);

    return 0;
}