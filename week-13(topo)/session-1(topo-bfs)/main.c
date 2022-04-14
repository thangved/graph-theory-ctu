#include <stdio.h>

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

void toposort(const Graph *pG)
{
    Queue q;
    makenullqueue(&q);
    int ind[MAX_NODE];
    for (int u = 1; u <= pG->n; u++)
    {
        ind[u] = in_degree(pG, u);
        if (ind[u])
            continue;
        enqueue(&q, u);
    }

    while (!emptyqueue(q))
    {
        int u = front(q);
        dequeue(&q);
        printf("%d\n", u);
        for (int v = 1; v <= pG->n; v++)
        {
            if (v == u || !pG->A[u][v])
                continue;
            ind[v]--;
            if (ind[v])
                continue;
            enqueue(&q, v);
        }
    }
}

int main()
{
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    toposort(&G);
    return 0;
}