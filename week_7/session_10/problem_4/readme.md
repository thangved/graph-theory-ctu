# Week 7 - Session 10 - Problem 4

Viết chương trình đọc vào một đơn đồ thị vô hướng và kiểm tra xem nó có chứa chu trình hay không. Nếu đồ thị có chu trình, in ra các đỉnh có trong chu trình.

## Đầu vào (Input)

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

## Đầu ra (Output)

- Nếu đồ thị có chu trình, in ra các đỉnh có trong chu trình trên cùng 1 dòng, cách nhau 1 khoảng trắng. Đỉnh đầu và đỉnh cuối của chu trình giống nhau.
- Nếu đồ thị không chứa chu trình, in ra -1
- Nếu đồ thị có nhiều chu trình, chỉ cần in ra 1 chu trình bất kỳ.
- Xem thêm ví dụ bên dưới.

Trong ví dụ đầu tiên, ta tìm thấy chu trình 1 -> 3 -> 2 -> 1, vì thế chương trình phải in ra:

```sh
1 3 2 1
```

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
    pG->A[v][u]++;
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

#define WHITE 0
#define GRAY 1
#define BLACK 2

int parent[MAX_NODE];
int marked[MAX_NODE];
int last_circle;
int first_circle;
int has_circle;

void DFS(Graph *pG, int u, int p)
{
    marked[u] = GRAY;
    parent[u] = p;
    for (int i = 1; i <= pG->n; i++)
        if (pG->A[u][i] && u != i)
        {
            if (has_circle)
                return;
            if (i == p)
                continue;
            if (marked[i] == WHITE)
            {
                DFS(pG, i, u);
                continue;
            }
            has_circle = 1;
            last_circle = u;
            first_circle = i;
            return;
        }

    marked[u] = BLACK;
}

void print_circle()
{
    Stack s;
    makenull(&s);
    int p = last_circle;
    while (p != -1)
    {
        push(p, &s);
        if (p == first_circle)
            break;
        p = parent[p];
    }
    while (!empty(s))
    {
        printf("%d ", pop(&s));
    }
    printf("%d\n", first_circle);
}

void initial(int n)
{
    for (int i = 1; i <= n; i++)
        parent[i] = 0;

    for (int i = 1; i <= n; i++)
        marked[i] = WHITE;
    has_circle = 0;
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    initial(G.n);

    for (int i = 1; i <= G.n && !has_circle; i++)
    {
        initial(G.n);
        DFS(&G, i, -1);
        if (has_circle)
            print_circle();
    }
    if (!has_circle)
        printf("%d\n", -1);

    return 0;
}
```
