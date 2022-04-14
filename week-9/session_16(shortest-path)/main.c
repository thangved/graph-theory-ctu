#include <stdio.h>

#define MAX_NODE 100
#define INFINITY __INT_MAX__
#define NO_EDGE INFINITY

typedef struct
{
    int n, m;
    int W[MAX_NODE][MAX_NODE];
} Graph;

void initgraph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->W[i][j] = NO_EDGE;
}

void addedge(Graph *pG, int u, int v, int w)
{
    pG->W[u][v] = w;
    pG->m++;
}

void findpath(const Graph *pG, int s)
{
    int marked[MAX_NODE] = {};
    int p[MAX_NODE] = {};
    int pi[MAX_NODE];
    for (int i = 0; i < MAX_NODE; i++)
        pi[i] = INFINITY;

    pi[s] = 0;
    p[s] = -1;
    for (int i = 1; i < pG->n; i++)
    {
        int mid = 0;
        for (int j = 1; j <= pG->n; j++)
        {
            if (marked[j])
                continue;
            if (pi[mid] > pi[j])
                mid = j;
        }
        marked[mid] = 1;

        for (int v = 1; v <= pG->n; v++)
        {
            if (pG->W[mid][v] == NO_EDGE)
                continue;
            if (pG->W[mid][v] + pi[mid] > pi[v])
                continue;
            pi[v] = pG->W[mid][v] + pi[mid];
            p[v] = mid;
        }
    }

    for (int i = 1; i <= pG->n; i++)
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
}

int main()
{
    // freopen("./graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    Graph G;
    initgraph(&G, n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(&G, u, v, w);
    }
    findpath(&G, 1);
    return 0;
}