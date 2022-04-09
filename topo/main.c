#include <stdio.h>
#define MAX_N 100
#define MAX_Length 100
typedef int Element;
int rank[MAX_N];
typedef struct
{
    int A[MAX_N][MAX_N];
    int n;
} Graph;
typedef struct
{
    Element data[MAX_Length];
    int size;
} List;
void make_null_list(List *L)
{
    L->size = 0;
}
void push_back(List *L, Element x)
{
    L->data[L->size] = x;
    L->size++;
}
Element element_at(List *L, int i)
{
    return L->data[i - 1];
}
int size(List *L)
{
    return L->size;
}
typedef struct
{
    int data[MAX_N];
    int front, rear;
} Queue;
void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}
void push(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}
int top(Queue *Q)
{
    return Q->data[Q->front];
}
void pop(Queue *Q)
{
    Q->front++;
}
int empty(Queue *Q)
{
    return Q->front > Q->rear;
}
void init_graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}
void add_edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
}
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}
int degree(Graph *G, int x)
{
    int deg_u = 0;
    for (int i = 1; i <= G->n; i++)
        deg_u += G->A[i][x];
    return deg_u;
}
List neighbors(Graph *G, int x)
{
    int y;
    List list;
    make_null_list(&list);
    for (y = 1; y <= G->n; y++)
        if (adjacent(G, x, y))
            push_back(&list, y);
    return list;
}
List topo_sort(Graph *G)
{
    int d[MAX_N];
    Queue Q;
    make_null_queue(&Q);
    for (int u = 1; u <= G->n; u++)
    {
        d[u] = degree(G, u);
        if (!d[u])
            push(&Q, u);
    }

    List L;
    make_null_list(&L);
    while (!empty(&Q))
    {
        int u = top(&Q);
        pop(&Q);
        push_back(&L, u);
        for (int v = 1; v <= G->n; v++)
        {
            if (!G->A[u][v])
                continue;
            d[v]--;
            if (!d[v])
                push(&Q, v);
        }
    }

    return L;
}
int main()
{
    FILE *f = fopen("./graph.txt", "r");
    Graph G;
    int n, m, u, v;
    fscanf(f, "%d%d", &n, &m);
    init_graph(&G, n);
    for (int i = 1; i <= m; i++)
    {
        fscanf(f, "%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    fclose(f);
    List L = topo_sort(&G);
    for (int i = 0; i < L.size; i++)
        printf("%d ", L.data[i]);
    return 0;
}
