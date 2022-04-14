#include <stdio.h>

#define MAX_NODE 100
#define INFINITY __INT_MAX__
#define NO_EDGE __INT_MAX__

typedef struct
{
    int n, m;
    int A[MAX_NODE][MAX_NODE];
} Graph;

void initgraph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->A[i][j] = NO_EDGE;
}

void addedge(Graph *pG, int u, int v, int w)
{
    pG->A[u][v] = w;
    pG->A[v][u] = w;
    pG->m++;
}

void findpath(const Graph *pG)
{
    int pi[MAX_NODE];
    int cnt[MAX_NODE] = {};
    int marked[MAX_NODE] = {};

    for (int i = 0; i <= pG->n; i++)
        pi[i] = INFINITY;

    pi[1] = 0;
    cnt[1] = 1;

    for (int i = 1; i < pG->n; i++)
    {
        int u = 0;
        for (int j = 1; j <= pG->n; j++)
            if ((pi[u] > pi[j]) && !marked[j])
                u = j;

        marked[u] = 1;
        for (int v = 1; v <= pG->n; v++)
        {
            if (v == u)
                continue;
            if (pG->A[u][v] == INFINITY)
                continue;
            if (pi[u] + pG->A[u][v] > pi[v])
                continue;
            if (pi[u] + pG->A[u][v] == pi[v])
            {
                cnt[v] += cnt[u];
                continue;
            }
            pi[v] = pi[u] + pG->A[u][v];
            cnt[v] = cnt[u];
        }
    }
    printf("%d %d", pi[pG->n] != INFINITY ? pi[pG->n] : -1, cnt[pG->n]);
}

int main()
{
    Graph G;
    int n, m, u, v, w, e;
    scanf("%d%d", &n, &m);
    initgraph(&G, n);

    for (e = 0; e < m; e++)
    {
        scanf("%d%d%d", &u, &v, &w);
        addedge(&G, u, v, w);
    }
    findpath(&G);
    return 0;
}