#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int kMaxN = 100000, kMaxM = 100000;
const int kMaxC = 320, kMaxS = 320;
int n, m, p;
struct Point {
    int x, y;
    Point() {}
    Point(int x_, int y_) : x(x_), y(y_) {}
    bool operator < (const Point &t) const {
        return ((long long)y * t.x - (long long)t.y * x < 0);
    }
    bool operator == (const Point &t) const {
        return ((long long)y * t.x - (long long)t.y * x == 0);
    }
} pnt[kMaxN + kMaxM], cmd[kMaxM];
int val[kMaxM];
int out;
int c, s;
int rec[kMaxC + 1], *pre = rec + 1;
struct Block {
    int val[kMaxS];
    int q[kMaxS], qt;
    int len, h, ans;
    void refresh(int xs) {
        out -= ans;
        ans = 0;
        h = *max_element(val, val + len);
        qt = 0;
        for (int i = 0; i < len; ++ i) {
            if (val[i] == 0) continue;
            if (!qt) q[qt ++] = val[i];
            else if (val[i] > q[qt - 1]) q[qt ++] = val[i];
        }   
        for (int i = 0; i < qt; ++ i) if (q[i] > pre[xs - 1]) ++ ans;
        out += ans;
    }
} blk[kMaxC];
int main() {
    //freopen("t.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) pnt[p ++] = Point(i, 0);
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", &cmd[i].x, &cmd[i].y);
        pnt[p ++] = cmd[i];
    }
    sort(pnt, pnt + p);
    p = unique(pnt, pnt + p) - pnt;
    for (int i = 0; i < m; ++ i) {
        val[i] = lower_bound(pnt, pnt + p, cmd[i]) - pnt;
        cmd[i].x --;
    }   
    
    s = (int)(sqrt(n)) + 1;
    c = (n - 1) / s + 1;
    for (int i = 0; i < n; ++ i) blk[i / s].val[blk[i / s].len ++] = 0;
    pre[-1] = -1;
    for (int i = 0; i < c; ++ i) pre[i] = max(pre[i - 1], blk[i].h);
    
    for (int i = 0; i < m; ++ i) {
        int x = cmd[i].x, y = val[i];
        int xs = x / s, xp = x % s;
        blk[xs].val[xp] = y;
        blk[xs].refresh(xs);
        pre[xs] = max(pre[xs - 1], blk[xs].h);
        for (int j = xs + 1; j < c; ++ j) {
            out -= blk[j].ans;
            blk[j].ans = (blk[j].q + blk[j].qt) - upper_bound(blk[j].q, blk[j].q + blk[j].qt, pre[j - 1]);
            out += blk[j].ans;
            pre[j] = max(pre[j - 1], blk[j].h);
        }
        printf("%d\n", out);
    }
    return 0;
}

