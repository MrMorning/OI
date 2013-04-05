#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 10010
#define eps (1e-9)
#define INF 1000000000
#define sqr(x) ((x) * (x))
#define two(x) (1 << (x))
#define X first
#define Y second

typedef long long LL;

int n, ne;
int head[MAXN], k[MAXN], e[MAXN], ns[MAXN];
double A[MAXN], B[MAXN], C[MAXN];
pair<int, int> edge[MAXN * 2];
bool flag[MAXN];

void add_edge(int x, int y)
{
    ++ne;
    edge[ne] = make_pair(y, head[x]);
    head[x] = ne;
}

void init()
{
    ne = 0;
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    for (int i = 1; i <= n; ++i) scanf("%d%d", &k[i], &e[i]);
}

void dfs(int x, int mark)
{
    int pnt = head[x];
    double ee = e[x] / 100.0, kk = k[x] / 100.0, u = (1 - ee - kk) / ns[x];
    double v = 0;
    if (mark == 0) 
        ns[x] = (x != 1);
    else
    {
        A[x] = 1 - kk;
        B[x] = kk;
        C[x] = u * (x != 1);
    }
    while (pnt != -1)
    {
        int y = edge[pnt].X;
        if (!flag[y])
        {
            flag[y] = true;
            dfs(y, mark);
            if (mark == 1)
            {
                A[x] += u * A[y];
                B[x] += u * B[y];
                v += u * C[y];
            }
            else
                ++ns[x];
        }
        pnt = edge[pnt].Y;
    }
    if (mark == 1)
    {
        A[x] /= (1 - v);
        B[x] /= (1 - v);
        C[x] /= (1 - v);
    }
}

void work()
{
    memset(flag, 0, sizeof(flag));
    flag[1] = true;
    dfs(1, 0);
    memset(flag, 0, sizeof(flag));
    flag[1] = true;
    dfs(1, 1);
    if (fabs(1 - B[1]) < eps) puts("impossible");
    else printf("%.6lf\n", A[1] / (1 - B[1]) - 1);
}

int main()
{
	freopen("t.in", "r", stdin);
    int T, ca = 0;
    scanf("%d", &T);
    while (T--)
    {
        printf("Case %d: ", ++ca);
        init();
        work();
 //       for (int i = 1; i <= n; ++i) cout << A[i] << ' ' << B[i] << ' ' << C[i] << endl;
    }
    return 0;
}

