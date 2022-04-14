#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100

typedef struct
{
    int elements[MAX_NODE];
    int front, rear;
} Queue;

void makenullqueue(Queue *pQ)
{
    pQ->front = 0;
    pQ->rear = -1;
}

int emptyqueue(Queue q)
{
    return q.rear < q.front;
}

void enqueue(Queue *pQ, int x)
{
    pQ->elements[++pQ->rear] = x;
}

int front(Queue q)
{
    return q.elements[q.front];
}

void dequeue(Queue *pQ)
{
    pQ->front++;
}

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
    pG->A[u][v] = 1;
    pG->m++;
}

int in_degree(const Graph *pG, int u)
{
    int id = 0;
    for (int v = 1; v <= pG->n; v++)
        id += pG->A[v][u];
    return id;
}
int out_degree(const Graph *pG, int u)
{
    int od = 0;
    for (int v = 1; v <= pG->n; v++)
        od += pG->A[u][v];
    return od;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void toposort(const Graph *pG, int rank[])
{
    Queue listqueue[MAX_NODE];
    makenullqueue(&listqueue[0]);
    int ind[MAX_NODE];
    for (int u = 1; u <= pG->n; u++)
    {
        ind[u] = in_degree(pG, u);
        if (ind[u])
            continue;
        enqueue(&listqueue[0], u);
    }
    int k = 0;
    while (!emptyqueue(listqueue[k]))
    {
        makenullqueue(&listqueue[k + 1]);
        while (!emptyqueue(listqueue[k]))
        {
            int u = front(listqueue[k]);
            dequeue(&listqueue[k]);
            rank[u] = k;
            for (int v = 1; v <= pG->n; v++)
            {
                if (v == u || !pG->A[u][v])
                    continue;
                ind[v]--;
                if (ind[v])
                    continue;
                enqueue(&listqueue[k + 1], v);
            }
        }
        k++;
    }
}

int maxarr(int *arr, int n)
{
    int m = 0;
    for (int i = 1; i <= n; i++)
        m = max(m, arr[i]);
    return m;
}

void projectmanagement(const Graph *pG, int d[])
{
    int rank[MAX_NODE];
    toposort(pG, rank);
    int t[MAX_NODE] = {};
    int T[MAX_NODE] = {};
    int mr = maxarr(rank, pG->n);
    for (int r = 0; r <= mr; r++)
        for (int v = 1; v <= pG->n; v++)
        {
            if (rank[v] != r)
                continue;

            for (int u = 1; u <= pG->n; u++)
            {
                if (!pG->A[u][v])
                    continue;
                t[v] = max(d[u] + t[u], t[v]);
            }
        }

    for (int u = 1; u <= pG->n; u++)
    {
        if (rank[u] != mr)
            continue;
        t[pG->n + 1] = max(d[u] + t[u], t[pG->n + 1]);
    }

    T[pG->n + 1] = t[pG->n + 1];
    printf("%d", T[pG->n + 1]);
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d", &n);
    init_graph(&G, n);
    int d[MAX_NODE];
    for (int u = 1; u <= n; u++)
        scanf("%d", d + u);
    scanf("%d", &m);

    for (; m > 0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    projectmanagement(&G, d);
    return 0;
}