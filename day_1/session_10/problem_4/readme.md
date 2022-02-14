# Problem 4

Cho cấu trúc dữ liệu đồ thị Graph được cài đặt bằng phương pháp "Ma trận kề" dùng để lưu trữ các đồ thị có hướng (có thể chứa đa cung và chứa khuyên).

```c
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;
```

Viết hàm int degree(Graph *pG, int u) để tính bậc của đỉnh theo mẫu (prototype):

```c
int degree(Graph *pG, int u) {
}
```

---

## Solution

```c
int outdegree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 1; i <= pG->n; i++)
        deg += pG->A[u][i];
    return deg;
}
```
