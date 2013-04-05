#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long val_t;
struct Point
{
    int x, y;
    Point(int _x, int _y):
        x(_x), y(_y){}
};

inline Point operator- (const Point &p1, const Point &p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

val_t f[1 << 16][25];
int log2[1 << 16];
int ord[16], ordCnt;
int corres[25];
int type[5][5];
int n, m;
int done[1 << 16][25];
int g[1 << 16][25];

inline int dot(const Point &p1, const Point &p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

inline int cross(const Point &p1, const Point &p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

inline bool reachable(int s, int u, int v)
{
    if(done[s][u] & (1 << v))
        return g[s][u] & (1 << v);
    done[s][u] |= 1 << v;
    Point p1 = Point(u / m, u % m),
          p2 = Point(v / m, v % m);
    for(int i = min(p1.x, p2.x); i <= max(p1.x, p2.x); i ++)
        for(int j = min(p1.y, p2.y); j <= max(p1.y, p2.y); j ++)
        {
            if((i == p1.x && j == p1.y) || (i == p2.x && j == p2.y))
                continue;
            Point pt = Point(i, j);
            if(dot(pt - p1, p2 - p1) > 0 && cross(pt - p1, p2 - p1) == 0)
                if((type[i][j] == 0 && (s & (1 << corres[i * m + j])) == 0) || type[i][j] == 1)
                    return false;
        }
    g[s][u] |= 1 << v;
    return true;
}

val_t solve()
{
    ordCnt = 0;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
        {
            cin >> type[i][j];
            if(type[i][j] == 0)
            {
                ord[ordCnt ++] = i * m + j;
                corres[i * m + j] = ordCnt - 1;
            }
        }
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(done, 0, sizeof(done));
    int upperlim = 1 << ordCnt;
    for(int i = 0; i < ordCnt; i ++)
        f[1 << i][ord[i]] = 1;
    for(int s = 0; s < upperlim; s ++)
        for(int i = 0; i < n * m; i ++)
            if(f[s][i])
            {
                int tmp = ~s & (upperlim - 1);
                while(tmp)
                {
                    int pos = tmp & (~tmp + 1);
                    int v = log2[pos];
                    if(reachable(s, i, ord[v]))
                        f[s + pos][ord[v]] += f[s][i];
                    tmp -= pos;
                }
            }
    val_t res = 0;
    for(int i = 0; i < ordCnt; i ++)
        res += f[upperlim - 1][ord[i]];
    return res;
}
int main()
{
    freopen("t.in", "r", stdin);
    ios::sync_with_stdio(false);
    for(int i = 0; i < 16; i ++)
        log2[1 << i] = i;
    while(cin >> n >> m)
        cout << solve() << '\n';
}
