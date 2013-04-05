#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long double val_t;
const val_t kEps = 1e-10;
const val_t kInf = 1e100;
const int kNMax = 100010;
const int BLKSZ = 400;
inline int sgn(val_t x) {
    if ( fabs(x) < kEps ) return 0;
    return x > 0 ? 1 : -1;
}
inline bool isGreater(val_t x, val_t y) {
    return sgn(x-y) > 0;
}
val_t val[kNMax];
int n, m, nBlk;
struct Block {
    val_t seq[BLKSZ];
    int seqL;
} blk[kNMax / BLKSZ + 10];
int findBlk(int i) {
    return (i-1)/BLKSZ;
}
void refresh(int t) {
    int st = t*BLKSZ+1;
    blk[t].seqL = 0;
    val_t bound = 0;
    for ( int i = 0; i < BLKSZ; i ++ )
        if ( isGreater(val[st+i], bound) ) {
            bound = val[st+i];
            blk[t].seq[blk[t].seqL++] = val[st+i];
        }
}
int main() {
//  freopen("t.in", "r", stdin);
//  freopen("A.out", "w", stdout);
//  freopen("t.out", "w", stdout);
    scanf("%d%d", &n, &m);
    nBlk = n / BLKSZ + 1;
    for ( int oprt = 0; oprt < m; oprt++ ) {
        int x, y;
        scanf("%d%d", &x, &y);
        val[x] = (val_t)y / x;
        refresh(findBlk(x));
        val_t bound = 0;
        int ans = 0;
        for ( int i = 0; i < nBlk; i ++ ) {
            int lb = -1, rb = blk[i].seqL-1;
            for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 ) {
                if ( isGreater(blk[i].seq[mid], bound) )
                    rb = mid;
                else
                    lb = mid;
            }
            if ( rb >= 0 && isGreater(blk[i].seq[rb], bound) ) {
                ans += blk[i].seqL-rb;
                bound = blk[i].seq[blk[i].seqL-1];
            }
        }
        printf("%d\n", ans);
    }
//  fprintf(stderr, "%d\n", clock());
}
