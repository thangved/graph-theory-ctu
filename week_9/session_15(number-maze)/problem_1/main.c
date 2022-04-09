#include <stdio.h>

#define INFINITY __INT_MAX__
#define NO_EDGE INFINITY
#define MAX_NODE 100

typedef struct
{
    int n, m;
    int W[MAX_NODE][MAX_NODE];
} Graph;

/**
 * @brief Init Graph
 *
 * @param pG Pointer to Graph
 * @param n Num Node of Graph
 */
void initgraph(Graph *pG, int n)
{
    pG->m = 0;
    pG->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->W[i][j] = NO_EDGE;
}

/**
 * @brief Add Edge to Graph
 *
 * @param pG Pointer to Graph
 * @param u Start of Edge
 * @param v End of Edge
 * @param w Weight of Edge
 */
void addedge(Graph *pG, int u, int v, int w)
{
    pG->W[u][v] = w;
    pG->W[v][u] = w;
    pG->m++;
}

void FloydWarshall(const Graph *pG)
{
    int pi[MAX_NODE][MAX_NODE];
    int next[MAX_NODE][MAX_NODE];
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
        {
            pi[u][v] = INFINITY;
            next[u][v] = -1;
        }

    for (int u = 1; u <= pG->n; u++)
        pi[u][u] = 0;

    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            if (pG->W[u][v] != NO_EDGE)
            {
                pi[u][v] = pG->W[u][v];
                next[u][v] = v;
            }

    for (int k = 1; k <= pG->n; k++)
        for (int u = 1; u <= pG->n; u++)
            for (int v = 1; v <= pG->n; v++)
                if (pi[u][k] + pi[k][v] < pi[u][v])
                {
                    if (pi[u][k] == INFINITY || pi[k][v] == INFINITY)
                        continue;
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
    printf("%d", pi[1][pG->n] != INFINITY ? pi[1][pG->n] : -1);
}

int main()
{
    Graph G;
    // freopen("./graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    initgraph(&G, n * m);
    for (int i = 1; i <= n * m; i++)
    {
        int w;
        scanf("%d", &w);
        addedge(&G, i - m, i, w);
        addedge(&G, i + m, i, w);
        if (i % m)
            addedge(&G, i + 1, i, w);
        if ((i - 1) % m)
            addedge(&G, i - 1, i, w);
    }
    FloydWarshall(&G);
    return 0;
}