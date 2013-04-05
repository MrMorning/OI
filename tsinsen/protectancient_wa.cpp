#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 105;
const int kPMax = 12;
const int kInf = 0x3f3f3f3f;
int countBits(int s) {
    int res = 0;
    while ( s ) {
        res += s & 1;
        s >>= 1;
    }
    return res;
}
struct Point {
    int x, y;
    Point(){}
    Point(int xx, int yy):
        x(xx), y(yy){}
} stake[kNMax], relic[kPMax];
Point operator- (const Point &p1, const Point &p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}
ll cross(const Point &p1, const Point &p2) {
    return (ll)p1.x * p2.y - (ll)p1.y * p2.x;
}
struct Edge {
    int to, cost;
    Edge *next;
} edge[kNMax * kNMax * 2], *begin[kNMax];
int edgeCnt;
struct Data {
    int u, v, w;
} dat[kNMax*kNMax*2];
int dist[kNMax];
bool ban[kNMax], active[kPMax];
int cost[kNMax][kNMax];
int f[kNMax][kNMax];
int val[1<<kPMax], g[1<<kPMax];
int p, n, m;
int best[kPMax];
void addEdge(int u, int v, int cost) {
    Edge *e = edge + edgeCnt++;
    e->to = v, e->next = begin[u], e->cost = cost;
    begin[u] = e;
}
int dijkstra(int src, int sink) {
    memset(begin, 0, sizeof(begin));
    edgeCnt = 0;
    for ( int i = 1; i <= m; i ++ ) {
        if ( !ban[dat[i].u] && !ban[dat[i].v] ) {
            addEdge(dat[i].u, dat[i].v, dat[i].w);
            addEdge(dat[i].v, dat[i].u, dat[i].w);
        }
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;
    PQ.push(make_pair(0, src));
    while ( PQ.size() ) {
        pair<int, int> u = PQ.top(); PQ.pop();
        if ( u.first != dist[u.second] ) continue;
        if ( u.second == sink ) return u.first;
        for ( Edge *e = begin[u.second]; e; e = e->next ) {
            int y = e->to;
            if ( dist[y] > u.first + e->cost ) {
                dist[y] = u.first + e->cost;
                PQ.push(make_pair(dist[y], y));
            }
        }
    }
    return kInf;
}
int main() {
    //freopen("t.in", "r", stdin);
    scanf("%d%d%d", &p, &n, &m);
    for ( int i = 1; i <= p; i ++ )
        scanf("%d%d", &relic[i].x, &relic[i].y);
    for ( int i = 1; i <= n; i ++ )
        scanf("%d%d", &stake[i].x, &stake[i].y);
    for ( int i = 1; i <= m; i ++ ) 
        scanf("%d%d%d", &dat[i].u, &dat[i].v, &dat[i].w);
    for ( int i = 1; i <= n; i ++ )
        for ( int j = 1; j <= n; j ++ )
            if ( i != j ) {
                memset(ban, 0, sizeof(ban));
                for ( int k = 1; k <= n; k ++ )
                    ban[k] = cross(stake[k]-stake[i], stake[j]-stake[i]) > 0;
                cost[i][j] = dijkstra(i, j);
            }
    int upperlim = 1<<p;
    for ( int s = 1; s < upperlim; s ++ ) {
        memset(active, 0, sizeof(active));
        for ( int k = 1; k <= p; k ++ )
            if ( s & (1<<(k-1)) )
                active[k] = true;
        memset(f, 0x3f, sizeof(f));
        for ( int i = 1; i <= n; i ++ )
            for ( int j = 1; j <= n; j ++ )
                if ( i == j ) 
                    f[i][j] = 0;
                else {
                    bool fine = true;
                    for ( int k = 1; k <= p; k ++ )
                        if ( active[k] )
                            fine &= cross(relic[k]-stake[i], stake[j]-stake[i]) > 0;
                    if ( fine ) 
                        f[i][j] = cost[i][j];
                }
        int ans = kInf;
        for ( int k = 1; k <= n; k ++ ) {
            for ( int i = 1; i <= n; i ++ )
                if ( i != k )
                    ans = min(ans, f[i][k]+f[k][i]);
            for ( int i = 1; i <= n; i ++ )
                if ( f[i][k] != kInf )
                    for ( int j = 1; j <= n; j ++ ) {
                        f[i][j] = min(f[i][j], f[i][k]+f[k][j]);
                    }
        }
        val[s] = ans;
    }
    g[0] = 0;
    for ( int s = 1; s < upperlim; s ++ ) {
        g[s] = kInf;
        for ( int s1 = s; s1; s1 = s&(s1-1) )
            g[s] = min(g[s], g[s-s1]+val[s1]);
    }
    memset(best, 0x3f, sizeof(best));
    for ( int s = 1; s < upperlim; s ++ )
        best[countBits(s)] = min(best[countBits(s)], g[s]);
	for ( int i = p-1; i >= 1; i -- )
		best[i] = min(best[i], best[i+1]);
    for ( int i = 1; i <= p; i ++ )
        printf("%d\n", best[i]);
}
