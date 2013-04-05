#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
 
#define __FUNCTION_DEFINED__
 
using namespace std;
 
#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
    do{ \
        if (pt >= pend) \
        { \
            pt = buf; \
            fread(buf, 1, BUFSIZE, stdin); \
        } \
    } while(0) 
 
#define scan(t) \
{ \
    t = 0; \
    read(); \
    bool nega = false; \
    while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
    if ((*pt) == '-') {nega = true, pt ++; read();} \
    while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
    if (nega) t = -t; \
}
 
#define scan_str(s) \
{ \
    int p = 0; \
    read(); \
    while ((*pt) == ' ' || (*pt) == '\n' || (*pt) == '\r') {pt ++; read();} \
    while (!((*pt) == ' ' || (*pt) == '\n' || (*pt) == '\r')) {s[p ++] = (*(pt ++)); read();} \
}
 
 
#define INFINITE 0x3f3f3f3f
#define MAXN 30000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
 
int father[MAXN + 1];
int n;
class Node
{
    public:
        int lt, rt, fa, v, sum, maxv;
};
Node node[MAXN + 1];
int Count = 0;
int begin[MAXN + 1], next[MAXN * 2 + 1], end[MAXN * 2 + 1];
void AddEdge(int a, int b)
{
    Count ++;
    next[Count] = begin[a];
    begin[a] = Count;
    end[Count] = b;
}
 
void Init()
{
    scan(n);
    for (int i = 1, a, b; i <= n - 1; i ++)
    {
        scan(a); scan(b);
        AddEdge(a, b);
        AddEdge(b, a);
    }
    for (int i = 1, v; i <= n; i ++)
    {
        scan(v);
        node[i].v = v;
    }
    node[0].v = node[0].maxv = -INFINITE;
    node[0].sum = 0;
}
 
 
#ifdef __FUNCTION_DEFINED__
#define Renew(_y_) \
{ \
    int __lc__ = node[_y_].lt, __rc__ = node[_y_].rt; \
    node[_y_].sum = node[__lc__].sum + node[__rc__].sum + node[_y_].v; \
    node[_y_].maxv = MAX(node[__lc__].maxv, node[__rc__].maxv); \
    node[_y_].maxv = MAX(node[_y_].maxv, node[_y_].v); \
}
 
#define RightRotate(_x_)  \
do { \
    int _lc_ = node[_x_].lt, _fa_ = node[_x_].fa;  \
    node[_x_].lt = node[_lc_].rt; node[node[_x_].lt].fa = _x_;  \
    node[_lc_].rt = _x_; node[_x_].fa = _lc_; \
    node[_lc_].fa =_fa_; \
    (_x_ == node[_fa_].lt ? node[_fa_].lt : node[_fa_].rt) = _lc_; \
    Renew(_x_); \
    Renew(_lc_); \
} while (0)
 
#define LeftRotate(_x_) \
do { \
    int _rc_ = node[_x_].rt, _fa_ = node[_x_].fa; \
    node[_x_].rt = node[_rc_].lt; node[node[_x_].rt].fa = _x_; \
    node[_rc_].lt = _x_; node[_x_].fa = _rc_; \
    node[_rc_].fa = _fa_; \
    (_x_ == node[_fa_].lt ? node[_fa_].lt : node[_fa_].rt) = _rc_; \
    Renew(_x_); \
    Renew(_rc_); \
} while (0)
 
#define splay(_u_) \
{ \
    int register __u__ = _u_, __fa__, __Fa__; \
    while ((__fa__ = node[__u__].fa)) \
    { \
        if (!(__Fa__ = node[__fa__].fa)) \
        { \
            if (__u__ == node[__fa__].lt) \
                RightRotate(__fa__); \
            else \
                LeftRotate(__fa__); \
        } \
        else \
        { \
            if (__u__ == node[__fa__].lt) \
            { \
                if (__fa__ == node[__Fa__].lt) \
                { \
                    RightRotate(__Fa__); \
                    RightRotate(__fa__); \
                } \
                else \
                { \
                    RightRotate(__fa__); \
                    LeftRotate(__Fa__); \
                } \
            } \
            else \
            { \
                if (__fa__ == node[__Fa__].rt) \
                { \
                    LeftRotate(__Fa__); \
                    LeftRotate(__fa__); \
                } \
                else \
                { \
                    LeftRotate(__fa__); \
                    RightRotate(__Fa__); \
                } \
            } \
        } \
    } \
}
 
#else
 
void Renew(int x) 
{ 
    int lc = node[x].lt, rc = node[x].rt; 
    node[x].sum = node[lc].sum + node[rc].sum + node[x].v; 
    node[x].maxv = MAX(node[lc].maxv, node[rc].maxv); 
    node[x].maxv = MAX(node[x].maxv, node[x].v); 
}
void RightRotate(int x)
{
    int lc = node[x].lt, fa = node[x].fa;
    node[x].lt = node[lc].rt; node[node[x].lt].fa = x;
    node[lc].rt = x; node[x].fa = lc;
    node[lc].fa = fa;
    (x == node[fa].lt ? node[fa].lt : node[fa].rt) = lc;
    Renew(x);
    Renew(lc);
}
 
void LeftRotate(int x)
{
    int rc = node[x].rt, fa = node[x].fa;
    node[x].rt = node[rc].lt; node[node[x].rt].fa = x;
    node[rc].lt = x; node[x].fa = rc;
    node[rc].fa = fa;
    (x == node[fa].lt ? node[fa].lt : node[fa].rt) = rc;
    Renew(x);
    Renew(rc);
}
 
void splay(int u)
{
    int register fa, Fa;
    while ((fa = node[u].fa))
    {
        if (!(Fa = node[fa].fa))
        {
            if (u == node[fa].lt)
                RightRotate(fa);
            else
                LeftRotate(fa);
        }
        else
        {
            if (u == node[fa].lt)
            {
                if (fa == node[Fa].lt)
                {
                    RightRotate(Fa);
                    RightRotate(fa);
                }
                else
                {
                    RightRotate(fa);
                    LeftRotate(Fa);
                }
            }
            else
            {
                if(fa == node[Fa].rt)
                {
                    LeftRotate(Fa);
                    LeftRotate(fa);
                }
                else
                {
                    LeftRotate(fa);
                    RightRotate(Fa);
                }
            }
        }
    }
}
 
#endif
void split(int u)
{
    splay(u);
    int rc = node[u].rt;
    node[u].sum = node[u].v + node[node[u].lt].sum;
    node[u].maxv = MAX(node[u].v, node[node[u].lt].maxv);
    node[u].rt = 0;
    node[rc].fa = 0;
}
 
int get_head(int u)
{
    while (node[u].fa)
        u = node[u].fa;
    while (node[u].lt)
        u = node[u].lt;
    splay(u);
    return u;
}
 
void concatenate(int u, int v) // let v be the right son of u
{
    assert(!node[u].rt);
    assert(!node[v].lt);
    node[u].rt = v, node[v].fa = u;
    node[u].sum += node[v].sum;
    node[u].maxv = MAX(node[u].maxv, node[v].maxv);
}
 
int expose(int u, bool flag = true)
{
    if (flag)
        split(u);
    int ret = u;
    while (true)
    {
        u = get_head(u);
        if (!father[u])
            return ret;
        ret = father[u];
        split(ret);
        concatenate(ret, u);
    }
}
 
void Change(int u, int t)
{
    expose(u, false);
    splay(u);
    //assert(node[u].rt == 0);
    node[u].v = t;
    int lc = node[u].lt, rc = node[u].rt;
    node[u].maxv = MAX(node[rc].maxv, node[lc].maxv);
    node[u].maxv = MAX(node[u].maxv, node[u].v);
    node[u].sum = node[u].v + node[lc].sum + node[rc].sum;
}
 
int QueryMax(int u, int v)
{
    if (u == v)
        return node[u].v;
    expose(u);
    int lca = expose(v);
    splay(lca);
    int ret = MAX(node[lca].v, node[node[lca].rt].maxv);
    expose(u);
    splay(lca);
    ret = MAX(ret, node[node[lca].rt].maxv);
    return ret;
}
 
int QuerySum(int u, int v)
{
    if (u == v)
        return node[u].v;
    expose(u);
    int lca = expose(v);
    splay(lca);
    int ret = node[lca].v + node[node[lca].rt].sum;
    expose(u);
    splay(lca);
    ret += node[node[lca].rt].sum;
    return ret;
}
 
int q[MAXN + 1];
 
char ans[200000 * 10];
int pos;
void AddNum(int v)
{
    static char buffer[100] = {0};
    int cnt = 0;
    if (v < 0)
        ans[pos ++] = '-', v = -v;
    while (v)
        buffer[cnt ++] = v % 10 + '0', v /= 10;
    if (cnt == 0)
        ans[pos ++] = '0';
    else
        while (cnt)
            ans[pos ++] = buffer[--cnt];
    ans[pos ++] = '\n';
}
 
void Solve()
{
    q[1] = 1;
    for (int head = 0, tail = 1; head != tail; )
        for (int t = q[++ head], now = begin[t], ch; now; now = next[now])
            if ((ch = end[now]) != father[t])
                father[ch] = t, q[++ tail] = ch;
    int q;
    scan(q);
    char cmd[10];
    int a, b;
    while (q --)
    {
        scan_str(cmd);
        scan(a); scan(b);
        if (cmd[0] == 'C') // CHANGE
            Change(a, b);
        else if (cmd[1] == 'M') // QMAX
        {
            //printf("%d\n", QueryMax(a, b));
            AddNum(QueryMax(a, b));
        }
        else // QSUM
        {
            //printf("%d\n", QuerySum(a, b));
            AddNum(QuerySum(a, b));
        }
    }
    ans[--pos] = 0;
    puts(ans);
}
 
int main()
{
freopen("t.in", "r", stdin);
    Init();
    Solve();
    return 0;
}
