#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;
 
const int V_MAX = 50010;
const int E_MAX = 500010;
 
template<typename T>
struct MonoQueue {
    pair<int, T> ele[V_MAX];
    int qh, qt;
    void clear() {
        qh = qt = 0;
    }
    T get_max() {
        return ele[qh].second;
    }
    int size() {
        return qt - qh;
    }
    void refresh(int t) {
        while ( qh < qt && ele[qh].first < t )
            qh ++;
    }
    void push(int i, const T &t) {
        while ( qh < qt && ele[qt - 1].second <= t )
            qt --;
        ele[qt ++] = make_pair(i, t);
    }
};
 
struct Edge {
    int to;
    Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX], *stk[V_MAX];
 
int n_vtx;
int top;
 
int dfn[V_MAX], low[V_MAX];
int f[V_MAX];
int seq[V_MAX], seq_cnt;
MonoQueue<int> MQ;
int ans = 0;
 
Edge *make_edge(int u, int v) {
    static int edge_cnt = 0;
    Edge *e = edge + edge_cnt ++;
    e->to = v, e->next = begin[u];
    return begin[u] = e;
}
 
void add_edge(int u, int v) {
    Edge *e1 = make_edge(u, v),
         *e2 = make_edge(v, u);
    e1->inv = e2, e2->inv = e1;
}
 
void work() {
    //fprintf(stderr, "Found a cycle rooted at %d...\n", seq[0]);
    //for ( int i = 0; i < seq_cnt; i ++ ) 
    //  fprintf(stderr, "%d ", seq[i]);
    //fprintf(stderr, "\n");
    MQ.clear();
    int res = 0;
    for ( int i = 0; i < seq_cnt; i ++ ) {
        MQ.refresh(i - seq_cnt / 2);
        if ( MQ.size() ) 
            res = max(res, MQ.get_max() + f[seq[i]] + i);
        MQ.push(i, f[seq[i]] - i);
    }
    static int g[V_MAX];
    for ( int i = 0; i < seq_cnt; i ++ ) {
        g[i] = max(i ? g[i - 1] : 0, f[seq[i]] + i);
        if ( i - (seq_cnt + 1) / 2 >= 0 )
            res = max(res, g[i - (seq_cnt + 1) / 2] + seq_cnt + f[seq[i]] - i);
    }
    ans = max(ans, res);
 
    for ( int i = 1; i < seq_cnt; i ++ )
        f[seq[0]] = max(f[seq[0]], f[seq[i]] + min(i, seq_cnt - i));
}
 
void dfs(int x, Edge *p) {
    //fprintf(stderr, "Trailing at Node %d...\n", x);
    static int time_stamp = 0;
    dfn[x] = low[x] = time_stamp ++;
    for ( Edge *e = begin[x]; e; e = e->next ) {
        if ( e->inv == p )
            continue;
        int y = e->to;
        if ( dfn[y] == -1 ) {
            stk[top ++] = e;
            dfs(y, e);
            low[x] = min(low[x], low[y]);
 
            if ( dfn[x] <= low[y] ) {
                assert(top);
                if ( stk[top - 1] == e ) {
                    //e is a bridge
                    ans = max(ans, f[x] + f[y] + 1);
                    f[x] = max(f[x], f[y] + 1);
                    top --;
                } else {
                    //a cycle
                    seq_cnt = 0;
                    while ( 1 ) {
                        seq[seq_cnt ++] = stk[top - 1]->to;
                        top --;
                        if ( stk[top] == e )
                            break;
                    }
                    work();
                }
            }
        } else if ( dfn[y] < dfn[x] ) {
            stk[top ++] = e;
            low[x] = min(low[x], dfn[y]);
        }
    }
}
 
int main() {
    int n_path;
    scanf("%d%d", &n_vtx, &n_path);
    while ( n_path -- ) {
        static int v[V_MAX];
        int l;
        scanf("%d", &l);
        for ( int i = 0; i < l; i ++ ) {
            scanf("%d", &v[i]);
            v[i] --;
        }
        for ( int i = 1; i < l; i ++ )
            add_edge(v[i - 1], v[i]);
    }
    memset(dfn, -1, sizeof(dfn));
    for ( int i = 0; i < n_vtx; i ++ )
        if ( dfn[i] == -1 )
            dfs(i, NULL);
    printf("%d\n", ans);
}
