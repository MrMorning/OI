#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <ctime>
#define ADJUST(x) (((x)%kMod+kMod)%kMod)
using namespace std;
typedef long long ll;
const int kMod = 19940417;
const int kNMax = 50010;
ll seq[kNMax];
int bino[kNMax+1][22];
inline void add(int &a, int b) {
    a += b;
	if ( a >= kMod ) a -= kMod;
}
inline int plus(int a, int b) {
    add(a, b);
    return a;
}
inline int mul(int a, int b) {
    return (ll)a * b % kMod;
}
inline int minus(int a, int b) {
    a -= b;
    if ( a < 0 ) a += kMod;
    return a;
}
struct Node {
    int l, r, f[22];
    ll inc;
    int rev;
    void reverse();
    void increase(ll);
} node[kNMax*4];
void merge(int h[], int f[], int g[]) {
    static int res[22];
    for ( int j = 0; j <= 20; j ++ ) {
        res[j] = 0;
        for ( int k = 0; k <= j; k ++ )
            add(res[j], mul(f[j-k], g[k]));
    }
    memcpy(h, res, sizeof(res));
}
void update(int i) {
    merge(node[i].f, node[i*2].f, node[i*2+1].f);
}
void Node::reverse() {
    rev *= -1;
    inc *= -1;
    for ( int i = 0; i <= 20; i ++ )
        f[i] = i&1?minus(0,f[i]):f[i];
}
void Node::increase(ll c) {
    inc += c;
    static int g[22], powC[22];
    memcpy(g, f, sizeof(f));
    memset(f, 0, sizeof(f));
    powC[0] = 1;
    for ( int i = 1; i <= 20; i ++ )
        powC[i] = mul(powC[i-1], ADJUST(c));
    int sz = r-l+1;
    for ( int j = 0; j <= min(sz,20); j ++ ) {
        f[j] = 0;
        for ( int k = 0; k <= j; k ++ )
            add(f[j], mul(g[k], mul(powC[j-k], bino[sz-k][j-k])));
    }
}
void pushDown(int i) {
    if ( node[i].rev == -1 ) {
        node[i*2].reverse();
        node[i*2+1].reverse();
    }
    if ( node[i].inc ) {
        node[i*2].increase(node[i].inc);
        node[i*2+1].increase(node[i].inc);
    }
    node[i].rev = 1;
    node[i].inc = 0;
}
void build(int i, int l, int r) {
    node[i].l = l, node[i].r = r;
    node[i].inc = 0, node[i].rev = 1;
    if ( l == r ) {
        node[i].f[0] = 1; node[i].f[1] = ADJUST(seq[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(i*2, l, mid);
    build(i*2+1, mid+1, r);
    update(i);
}
void increase(int i, int l, int r, ll inc) {
    if ( node[i].l > r || node[i].r < l ) return;
    if ( l <= node[i].l && node[i].r <= r ) {
        node[i].increase(inc);
        return;
    }
    pushDown(i);
    increase(i*2,l,r,inc);
    increase(i*2+1,l,r,inc);
    update(i);
}
void reverse(int i, int l, int r) {
    if ( node[i].l > r || node[i].r < l ) return;
    if ( l <= node[i].l && node[i].r <= r ) {
        node[i].reverse();
        return;
    }
    pushDown(i);
    reverse(i*2,l,r);
    reverse(i*2+1,l,r);
    update(i);
}
void ask(int i, int l, int r, int res[]) {
    memset(res, 0, sizeof(int)*22);
    if ( node[i].l > r || node[i].r < l ) {
        res[0] = 1;
        return;
    }
    if ( l <= node[i].l && node[i].r <= r ) {
        memcpy(res, node[i].f, sizeof(node[i].f));
        return;
    }
    pushDown(i);
    int resl[22], resr[22];
    ask(i*2,l,r,resl);
    ask(i*2+1,l,r,resr);
    merge(res, resl, resr);
    update(i);
}
int main() {
    //freopen("t.in", "r", stdin);
    //freopen("t.out", "w", stdout);
    bino[0][0] = 1;
    for ( int i = 1; i <= kNMax; i ++ ) {
        bino[i][0] = 1;
        for ( int j = 1; j <= 20; j ++ )
            bino[i][j] = plus(bino[i-1][j], bino[i-1][j-1]);
    }
    int n, q;
    scanf("%d%d", &n, &q);
    for ( int i = 1; i <= n; i ++ ) {
        int x;
        scanf("%d", &x);
        seq[i] = x; 
    }
    build(1, 1, n);
    for ( int qur = 0; qur < q; qur ++ ) {
        char cmd[4];
        scanf("%s", cmd);
        if ( cmd[0] == 'Q' ) {
            int a, b, c;
            int res[22];
            scanf("%d%d%d", &a, &b, &c);
            ask(1, a, b, res);
            printf("%d\n", res[c]);
        } else if (cmd[0] == 'R' ) {
            int a, b;
            scanf("%d%d", &a, &b);
            reverse(1, a, b);
        } else {
            assert(cmd[0] == 'I');
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            increase(1, a, b, c);
        }   
    }
    //fprintf(stderr, "%d\n", clock());
}
