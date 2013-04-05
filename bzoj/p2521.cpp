#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int V_MAX = 510, E_MAX = 810; 
const int inf = 0x3f3f3f3f;
int src, sink, upper;
struct Memo {
	int u, v, w;
} memo[E_MAX];
struct Edge{
    int to, cap;
    Edge *next, *inv;
} edge[E_MAX << 2], *begin[V_MAX];
 
int edge_cnt;
int dist[V_MAX];
Edge *make_edge(int u, int v, int w) {
    Edge *e = edge + edge_cnt++;
    e->to = v, e->next = begin[u], e->cap = w;
    return begin[u] = e;
}
 
void add_edge(int u, int v, int w) {
    Edge *e1 = make_edge(u, v, w),
         *e2 = make_edge(v, u, 0);
    e1->inv = e2, e2->inv = e1;
}
 
bool pre_lable() {
    static int Q[V_MAX];
    memset(dist, -1, sizeof(dist));
    int qh = 0, qt = 0;
    Q[qt ++] = src;
    dist[src] = 0;
    while ( qh < qt ){
        int u = Q[qh ++];
        for ( Edge *e = begin[u]; e; e= e->next )
            if ( e->cap ){
                int v = e->to;
                if ( dist[v] == -1 ){
                    dist[v] = dist[u] + 1;
                    Q[qt ++] = v;
                }
            }
    }
    return dist[sink] != -1;
}
 
int find_aug(int u, int flow) {
    if ( u == sink )
        return flow;
    Edge *e;
    int res = 0;
    for ( e = begin[u]; e; e = e->next )
        if ( e->cap ) {
            int v = e->to;
            if ( dist[v] != dist[u] + 1 )
                continue;
            int tmp = find_aug(v, min(e->cap, flow));
            e->cap -= tmp;
            e->inv->cap += tmp;
            res += tmp;
            flow -= tmp;
            if ( !flow )
                break;
        }
    if ( !e )
		dist[u] = -1;
    return res;
}
 
int dinic() {
    int res = 0;
    while ( pre_lable() )
        res += find_aug(src, inf);
    return res;
}
 
int n, m, id;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &n, &m, &id);
	for ( int i = 0; i < m; i ++ ) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		if ( i == id - 1 ) {
			src = u, sink = v, upper = w + 1;
		}
		memo[i].u = u, memo[i].v = v, memo[i].w = w;
	}	
	for ( int i = 0; i < m; i ++ ) 
		if ( i != id - 1 ) {
			int u = memo[i].u, v = memo[i].v, w = memo[i].w;
			if  ( upper > w ) {
				add_edge(u, v, upper - w);
				add_edge(v, u, upper - w);
			}
		}
	printf("%d\n", dinic());
}
