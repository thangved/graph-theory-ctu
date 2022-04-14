# Week 7 - Session 11 - Problem 2

Thuyền trưởng Haddock (truyện Tintin) là một người luôn say xỉn. Vì thế đôi khi Tintin không biết ông ta đang say hay tỉnh. Một ngày nọ, Tintin hỏi ông ta về cách uống. Haddock nói như thế này: Có nhiều loại thức uống (soda, wine, water, …), tuy nhiên Haddock lại tuân theo quy tắc “để uống một loại thức uống nào đó cần phải uống tất cả các loại thức uống tiên quyết của nó”. Ví dụ: để uống rượu (wine), Haddock cần phải uống soda và nước (water) trước. Vì thế muốn say cũng không phải dễ!

Cho danh sách các thức uống và các thức uống tiên quyết của nó. Hãy xét xem Haddock có thể nào say không ? Để làm cho Haddock say, ông ta phải uống hết tất cả các thức uống.

## Ví dụ 1

```sh
soda wine
water wine
```

Thức uống tiên quyết được cho dưới dạng a b, có nghĩa là để uống b bạn phải uống a trước. Trong ví dụ trên để uống wine, Haddock phải uống soda và water trước. Soda và water không có thức uống tiên quyết nên Haddock sẽ SAY.

## Ví dụ 2

```sh
soda wine
water wine
wine water
```

Để uống wine, cần uống water. Tuy nhiên để uống water lại cần wine. Vì thế Haddock không thể uống hết được các thức uống nên ông ta KHÔNG SAY.

Để đơn giản ta có thể giả sử các thức uống được mã hoá thành các số nguyên từ 1, 2, … và dữ liệu đầu vào được cho có dạng như sau (ví dụ 1):

```sh
3 2
1 2
3 2
```

Có loại thức uống (soda: 1, wine: 2 và water: 3) và có 2 điều kiện tiên quyết

1 -> 2 và 3 -> 2.

Với ví dụ 2, ta có dữ liệu:

```sh
3 3
1 2
3 2
2 3
```

Viết chương trình đọc dữ liệu các thức uống và kiểm tra xem Haddock có thể say không. Nếu có in ra “YES”, ngược lại in ra “NO”.

## Đầu vào (Input)

Dữ liệu đầu vào được nhập từ bàn phím (stdin) với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số thức uống và số điều kiện tiên quyết
- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng thức uống u là tiên quyết của thức uống v

## Đầu ra (Output)

- Nếu Haddock có thể say in ra YES, ngược lại in ra NO.

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
            if (marked[i] == BLACK)
                continue;
            if (marked[i] == WHITE)
            {
                DFS(pG, i, u);
                if (has_circle)
                    return;
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
            printf("NO\n");
    }
    if (!has_circle)
        printf("YES\n");

    return 0;
}
```
