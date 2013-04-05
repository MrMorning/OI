#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define mi 0x7FFFFFFF

typedef struct { int to, length, next, prev, map; } graphnode;
graphnode graph[400010]; int grapmr;

int kappa;
int bal[100100], vari[100100], nown;
int center, minbal;

// 找重心！center就是这个函数的返回。
void calbal (int root, int pere)
{
    int p, tar;
    vari[root] = 1, bal[root] = 0;
    for (p = graph[root].next; p != -1; p = graph[p].next)
    {
        tar = graph[p].to;
        if (tar == pere) continue;
        calbal(tar, root);
        bal[root] = max(bal[root], vari[tar]);
        vari[root] += vari[tar];
    }
    bal[root] = max(bal[root], nown - vari[root]);
    if (bal[root] < minbal)
    {
        minbal = bal[root];
        center = root;
    }
    return;
}

int ans, dt[10010], dtmr, dist[10010];
void distdfs (int root, int pere)
{
    int p, tar;
    for (p = graph[root].next; p != -1; p = graph[p].next)
    {
        tar = graph[p].to;
        if (tar == pere) continue;
        dist[tar] = dist[root] + graph[p].length;
        dt[dtmr++] = dist[tar];
        distdfs(tar, root);
    } return;
}
int comp (const void *a, const void *b) { return *((int *)a) - *((int *)b); }
void calculate (int root)
{
    int p, l, r, tar, troot, tp;
    dtmr = 0;
    dist[root] = 0; dt[dtmr++] = 0;
    distdfs(root, -1);
    qsort(dt, dtmr, sizeof(int), comp);
    l = 0, r = dtmr - 1;
    while (l < r)
    {
        if (dt[l] + dt[r] <= kappa)
        {
            ans += (r - l);
            l++;
        }
        else r--;
    }
    for (p = graph[root].next; p != -1; p = graph[p].next)
    {
        dtmr = 0;
        tar = graph[p].to;
        dt[dtmr++] = dist[tar];
        distdfs(tar, root);
        qsort(dt, dtmr, sizeof(int), comp);
        l = 0, r = dtmr - 1;
        while (l < r)
        {
            if (dt[l] + dt[r] <= kappa)
            {
                ans -= (r - l);
                l++;
            }
            else r--;
        }
    }
    for (p = graph[root].next; p != -1; p = graph[p].next)
    {
        tp = graph[p].map;
        graph[graph[tp].prev].next = graph[tp].next;
        if (graph[tp].next != -1) graph[graph[tp].next].prev = graph[tp].prev;
        troot = graph[p].to;
        nown = vari[troot];
        minbal = mi;
        calbal(troot, -1);
        calculate(center);
    } return;
}

int main ()
{
	freopen("t.in", "r", stdin);
    int n, i, j, a, b, l, r1, p1, r2, p2;
    while (1)
    {
        scanf("%d %d", &n, &kappa);
        if (n == 0 && kappa == 0) break;
        grapmr = n;
        for (i = 0; i < n; i++)
            graph[i].next = -1;
        for (i = 0; i < n - 1; i++)
        {
            scanf("%d %d %d", &a, &b, &l);
            a--, b--;
            for (r1 = a; graph[r1].next != -1; r1 = graph[r1].next);
            p1 = grapmr++;
            graph[p1].to = b, graph[p1].length = l;
            graph[p1].next = -1, graph[p1].prev = r1;
            graph[r1].next = p1;
            for (r2 = b; graph[r2].next != -1; r2 = graph[r2].next);
            p2 = grapmr++;
            graph[p2].to = a, graph[p2].length = l;
            graph[p2].next = -1, graph[p2].prev = r2;
            graph[r2].next = p2;
            // 有了这个，两条边就能互相映射，删边的复杂度就是 O(1)了，呵呵。
            graph[p1].map = p2;
            graph[p2].map = p1;
        }
        ans = 0;
        nown = n; minbal = mi;
        calbal(0, -1);
        calculate(center);
        printf("%d\n", ans);
    }
    return 0;
}
