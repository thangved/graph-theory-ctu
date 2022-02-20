#include <stdio.h>

#define MAX_NODE 100

typedef struct
{
    int n, m;
    int A[MAX_NODE][MAX_NODE];
} Graph;

typedef struct
{
    int data[MAX_NODE];
    int top;
} Stack;

void makenull(Stack *pS)
{
    pS->top = -1;
}

int empty(Stack s)
{
    return s.top == -1;
}

void push(int x, Stack *pS)
{
    pS->top++;
    pS->data[pS->top] = x;
}

int pop(Stack *pS)
{
    pS->top--;
    return pS->data[pS->top + 1];
}

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
int on_stack[MAX_NODE];
int num[MAX_NODE];
int min_num[MAX_NODE];
Stack stack;
int step;

void init_array(int *arr)
{
    for (int i = 0; i < MAX_NODE; i++)
        *(arr + i) = 0;
}
void initial()
{
    step = 1;
    makenull(&stack);
    init_array(marked);
    init_array(on_stack);
    init_array(num);
    init_array(min_num);
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void SCC(Graph *pG, int u)
{
    num[u] = step;
    min_num[u] = step;
    marked[u] = 1;
    on_stack[u] = 1;
    push(u, &stack);
    step++;

    for (int i = 1; i <= pG->n; i++)
    {
        if (!pG->A[u][i] || u == i)
            continue;
        if (on_stack[i])
        {
            min_num[u] = min(min_num[u], num[i]);
            continue;
        }
        if (marked[i])
            continue;
        SCC(pG, i);
        min_num[u] = min(min_num[i], min_num[u]);
    }

    if (num[u] == min_num[u])
        for (;;)
        {
            int top = pop(&stack);
            on_stack[top] = 0;
            if (top == u)
                return;
        }
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    initial();
    SCC(&G, 1);
    for (int i = 1; i <= G.n; i++)
        printf("%d %d\n", num[i], min_num[i]);
    return 0;
}