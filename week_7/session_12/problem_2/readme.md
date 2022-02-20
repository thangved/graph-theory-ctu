# Week 7 - Session 12 - Problem 2

David là huấn luyện viên của một đội bóng gồm N thành viên. David muốn chia đội bóng thành hai nhóm. Để tăng tính đa dạng của các thành viên trong nhóm, David quyết định không xếp hai thành viên đã từng thi đấu với nhau vào chung một nhóm. Bạn hãy lập trình giúp David phân chia đội bóng.

## Đầu vào (Input)

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên N và M, tương ứng là số thành viên và số cặp thành viên đã từng thi đấu với nhau.
- M dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng 2 thành viên u và v đã từng thi đấu chung với nhau.

## Đầu ra (Output)

- Nếu phân chia được, hãy in ra các thành viên của mỗi nhóm. Nhóm của thành viên 1 sẽ được in trước, nhóm còn lại in ra sau. Các thành viên trong nhóm được in ra theo thứ tự tăng dần và in trên 1 dòng. Hai thành viên cách nhau 1 khoảng trắng.
- Nếu không thể phân chia, in ra IMPOSSIBLE

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

void foreach (int array[], int length, void(callback(int element, int index)))
{
    for (int i = 0; i < length; i++)
        callback(array[i], i);
    printf("\n");
}

void print_blue(int element, int index)
{
    if (index)
        if (element == BLUE)
            printf("%d ", index);
}

void print_red(int element, int index)
{
    if (index)
        if (element == RED)
            printf("%d ", index);
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    initial(G);
    DFS(&G, 1, BLUE);
    if (conflict)
        printf("IMPOSSIBLE");
    else
    {
        foreach (marked, G.n + 1, print_blue);
        foreach (marked, G.n + 1, print_red);
    }
    return 0;
}
```
