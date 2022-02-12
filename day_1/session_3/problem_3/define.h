#define MAX_M 100
typedef struct
{
    int u, v;
} Edge;
typedef struct
{
    int n, m;
    Edge edges[MAX_M];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}