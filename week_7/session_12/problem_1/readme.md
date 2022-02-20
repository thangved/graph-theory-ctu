# Week 7 - Session 12 - Problem 1

Viết chương trình đọc vào một đồ thị vô hướng và kiểm tra xem nó có phải là đồ thị phân đôi không.

## Đầu vào (Input)

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung của đồ thị.
- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v, cách nhau 1 khoảng trắng, mô tả cung (u, v).

## Đầu ra (Output)

- Nếu đồ thị là đồ thị phân đôi, in ra YES, ngược lại in ra NO.

## Solution

```c
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

#define NO_COLOR -1
#define BLUE 0
#define RED 1

int marked[MAX_NODE];
int conflict;

void DFS(Graph *pG, int u, int color)
{
    marked[u] = color;

    for (int i = 1; i <= pG->n; i++)
    {
        if (u == i || !pG->A[u][i])
            continue;
        if (marked[i] == NO_COLOR)
        {
            DFS(pG, i, !color);
        }
        if (marked[i] == color)
        {
            conflict = 1;
            return;
        }
    }
}

void initial(Graph G)
{
    for (int i = 1; i <= G.n; i++)
        marked[i] = NO_COLOR;
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    for (int i = 1; i <= G.n; i++)
    {
        initial(G);
        DFS(&G, i, BLUE);
    }
    printf("%s", conflict ? "NO" : "YES");
    return 0;
}
```
