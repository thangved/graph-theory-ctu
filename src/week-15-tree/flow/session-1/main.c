#include <stdio.h>

#define MAX_NODE 100
#define INFINITE __INT_MAX__

typedef struct
{
    int front;
    int rear;
    int elements[MAX_NODE];
} Queue;

void makequeue(Queue *pQ)
{
    pQ->front = 0;
    pQ->rear = -1;
}

int emptyqueue(Queue q)
{
    return q.front > q.rear;
}

void enqueue(int x, Queue *pQ)
{
    pQ->rear++;
    pQ->elements[pQ->rear] = x;
}

void dequeue(Queue *pQ)
{
    pQ->front++;
}

int front(Queue q)
{
    return q.elements[q.front];
}

typedef struct
{
    int n, m;
    int C[MAX_NODE][MAX_NODE];
    int F[MAX_NODE][MAX_NODE];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            pG->C[i][j] = 0;
            pG->F[i][j] = 0;
        }
}

void add_edge(Graph *pG, int u, int v, int c)
{
    pG->C[u][v] = c;
    pG->m++;
}

void init_flow(Graph *pG)
{
    for (int i = 1; i <= pG->n; i++)
        for (int j = 1; j <= pG->n; j++)
            pG->F[i][j] = 0;
}

typedef int Dir;
#define NO_LABEL 0
#define PLUS 1
#define MINUS -1

typedef struct
{
    Dir dir;
    int p;
    int sigma;
} Label;

int min(int a, int b)
{
    return a < b ? a : b;
}
void FordFullkerson(Graph *pG, int source, int sink)
{
    Label labels[MAX_NODE];
    init_flow(pG);
    int maxflow = 0;
    Queue q;
    for (;;)
    {
        for (int u = 1; u <= pG->n; u++)
            labels[u].dir = NO_LABEL;
        makequeue(&q);
        enqueue(source, &q);
        Label l = {PLUS, 0, INFINITE};
        labels[source] = l;

        while (!emptyqueue(q))
        {
            int u = front(q);
            dequeue(&q);

            for (int v = 1; v <= pG->n; v++)
            {
                if (!pG->C[u][v] || labels[v].dir)
                    continue;

                int increase = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
                if (!increase)
                    continue;
                
                labels[v].dir = PLUS;
                labels[v].sigma = increase;
                labels[v].p = u;
                enqueue(v, &q);
            }

            for (int v = 1; v <= pG->n; v++)
            {
                if (!pG->C[v][u] || labels[v].dir)
                    continue;

                int decrease = min(labels[u].sigma, pG->C[v][u] - pG->F[v][u]);
                if (!decrease)
                    continue;
                
                labels[v].dir = MINUS;
                labels[v].sigma = decrease;
                labels[v].p = u;
                enqueue(v, &q);
            }
        }

        if (!labels[sink].dir)
            break;
        maxflow += labels[sink].sigma;
        int increase = labels[sink].sigma;
        makequeue(&q);
        enqueue(sink, &q);
        while(!emptyqueue(q))
        {
            int v = front(q);
            dequeue(&q);
            if (!labels[v].p)
                continue;
            enqueue(labels[v].p, &q);
            if (labels[v].dir == PLUS)
                pG->F[labels[v].p][v] += increase;
            if (labels[v].dir == MINUS)
                pG->F[labels[v].p][v] -= increase;
        }
    }

    printf("Max flow: %d\n", maxflow);
    printf("S: ");
    for (int u = 1; u <= pG->n; u++)
        if (labels[u].dir)
            printf("%d ", u);
    printf("\nT: ");
    for (int u = 1; u <= pG->n; u++)
        if (!labels[u].dir)
            printf("%d ", u);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G;
    init_graph(&G, n);

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add_edge(&G, u, v, c);
    }
    FordFullkerson(&G, 1, n);
    return 0;
}
