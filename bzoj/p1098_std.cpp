#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
 
const int MAXN = 100000;
const int MAXM = 2000000;
 
struct Edge {
 
    int to;
    Edge *next;
 
} edges[MAXM * 2 + 1], *head[MAXN + 1];
 
struct Node {
 
    bool mark;
    Node *prev, *next;
 
} nodes[MAXN];
 
int N, M, ecnt;
 
void add_edge(int st, int ed) {
 
    edges[++ecnt].next = head[st];
    head[st] = edges + ecnt;
    edges[ecnt].to = ed;
}
 
void add_pair(int st, int ed) {
 
    add_edge(st, ed);
    add_edge(ed, st);
}
 
void pre_work() {
 
    int st, ed;
 
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; i++)
    {
        scanf("%d %d", &st, &ed);
        add_pair(st, ed);
    }
 
    Node *p = nodes, *ptr = nodes + 1;
    for (int i = 1; i <= N; i++, ptr++)
    {
        (p -> next = ptr) -> prev = p;
        p = ptr;
    }
    (p -> next = nodes) -> prev = p;
}
 
bool cmp_int(int a, int b) {
 
    return a < b;
}
 
void work() {
 
    static int que[MAXN + 1];
    static int ans[MAXN + 1], acnt = 0;
 
    while (nodes -> next != nodes)
    {
        Node *h = nodes -> next;
        h -> prev -> next = h -> next;
        h -> next -> prev = h -> prev;
        que[0] = h - nodes;
 
        int l, r;
        for (l = 0, r = 1; l != r; l++)
        {
            int u = que[l];
            for (Edge *ptr = head[u]; ptr; ptr = ptr -> next)
                nodes[ptr -> to].mark = 1;
 
            for (Node *ptr = nodes -> next; ptr != nodes; ptr = ptr -> next)
                if (ptr -> mark) ptr -> mark = 0;
                else
                {
                    que[r++] = ptr - nodes;
                    ptr -> prev -> next = ptr -> next;
                    ptr -> next -> prev = ptr -> prev;
                }
        }
        ans[++acnt] = r;
    }
 
    std::sort(ans + 1, ans + acnt + 1, cmp_int);
    printf("%d\n", acnt);
    for (int i = 1; i <= acnt; i++) printf("%d ", ans[i]);
    printf("\n");
}
 
int main() {
	freopen("t.in", "r", stdin);
    pre_work();
    work();
 
    return 0;
}
