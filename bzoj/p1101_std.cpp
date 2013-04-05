/**************************************************************
    Problem: 1101
    User: zxytim
    Language: C++
    Result: Accepted
    Time:5353 ms
    Memory:740 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
#include <cmath>
 
#define MAXN 50000
 
int n, a, b, k;
int p[MAXN + 1];
bool hash[MAXN + 1];
 
int flag[MAXN + 1];
 
class Num
{
    public:
        int v;
        bool flag;
};
 
Num num[MAXN + 1];
int cnt = 0;
void dfs(int now, int v, bool flag)
{
    cnt ++;
    num[cnt].v = v;
    num[cnt].flag = flag;
    for (int t; (t = v * p[now]) <= MAXN && (t > v) && now <= p[0]; now ++)
        dfs(now + 1, v * p[now], flag ^ 1);
}
 
bool cmp(const Num &a, const Num &b)
{
    return a.v < b.v;
}
 
int s[MAXN + 1];
int num_ngt[MAXN + 1];
void Init()
{
    for (int i = 2; i <= MAXN; i ++)
        if (!hash[i])
        {
            p[++ p[0]] = i;
            for (int j = i + i; j <= MAXN; j += i)
                hash[j] = true;
        }
    dfs(1, 1, 1);
    std::sort(num + 1, num + 1 + cnt, cmp);
    num[cnt + 1].v = MAXN + 1;
    for (int i = 1; i <= cnt; i ++)
    {
        s[i] = s[i - 1] + (num[i].flag ? 1 : -1);
        for (int j = num[i].v; j < num[i + 1].v; j ++)
            num_ngt[j] = s[i];
    }
}
 
void Solve()
{
    int n, a, b, k;
    scanf("%d", &n);
    while (n --)
    {
        scanf("%d%d%d", &a, &b, &k);
        int register ans = 0;
        a /= k, b /= k;
        if (a > b) k = a, a = b, b = k;
        int limit = std::min(int(sqrt(double(b))), a);
        for (k = 1; num[k].v <= limit; k ++)
        {
            if (num[k].flag)
                ans += (a / num[k].v) * (b / num[k].v);
            else
                ans -= (a / num[k].v) * (b / num[k].v);
        }
        for (int i = num[k].v; i <= a; i ++)
        {
            int register ta = a / i, tb = b / i, m = std::min(a / ta, b / tb);
            ans += (num_ngt[m] - num_ngt[i - 1]) * ta * tb;
            i = m;
        }
        printf("%d\n", ans);
    }
}
 
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
    Init();
    Solve();
    return 0;
}
