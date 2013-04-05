#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    maxN    = 400000 + 10;
int            N;
int            tot;
int            w        [maxN];
int            pre        [maxN];
int            other    [maxN];
int            last    [maxN];
int            topo    [maxN];
int            deep    [maxN];
int            f        [maxN];
int            g        [maxN];
int            delta    [maxN];
bool        flag    [maxN];
int            ans        [maxN];

void Init()
{
    int        p, q;
    char     str        [20];
    scanf("%d", &N);
    for(int i = 1; i < N; ++ i) {
        scanf("%d%d", &p, &q);
        pre[2 * i] = last[p]; last[p] = 2 * i; other[2 * i] = q;
        pre[2 * i + 1] = last[q]; last[q] = 2 * i + 1; other[2 * i + 1] = p;
        gets(str);
        w[2 * i] = w[2 * i + 1] = (str[1] == 'p');
    }
    
    int     top(1), bom(0);
    topo[1] = 1;
    flag[1] = 1;
    while (top > bom) {
        for(int tmp = last[topo[++ bom]]; tmp; tmp = pre[tmp])
            if (! flag[other[tmp]]) {
                topo[++ top] = other[tmp];
                flag[other[tmp]] = 1;
            }
    }
    //for(int i = 1; i <= N; ++ i) printf("%d ", topo[i]);
}

void Solve()
{    
    int        from, to;
    deep[1] = 0; flag[1] = 0;
    for(int i = 2; i <= N; ++ i) {
        flag[from = topo[i]] = 0;
        for(int tmp = last[from]; tmp; tmp = pre[tmp])
            if (! flag[to = other[tmp]]) {
                deep[from] = deep[to] + 1;
                f[from] = f[to] + w[tmp];
            }
    }
    
    for(int i = N; i >= 1; -- i) {
        flag[from = topo[i]] = 1;
        g[from] = (deep[from] + 1) / 2 - f[from];
        for(int tmp = last[from]; tmp; tmp = pre[tmp])
            if (flag[to = other[tmp]])
                g[from] = max(g[from], g[to]);
    }
    
    delta[1] = 0;
    flag[1] = 0;
    for(int i = 2; i <= N; ++ i) {
        flag[from = topo[i]] = 0;
        for(int tmp = last[from]; tmp; tmp = pre[tmp])
            if (! flag[to = other[tmp]]) {
                delta[from] = delta[to];
                if (! w[tmp] && g[from] - delta[from] > 0) {
                    ans[++ tot] = tmp / 2;
                    delta[from] ++;
                }
            }
    }
    /*for(int i = 1; i <= N; ++ i) printf("%d ", g[i]);
    puts("");*/
    printf("%d\n", tot);
	return;
    for(int i = 1; i <= tot; ++ i) printf("%d ", ans[i]);
    //system("pause");
}

int main()
{
	freopen("t.in", "r", stdin);
    Init();
    Solve();

    return 0;
}
