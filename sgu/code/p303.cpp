#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix 
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

namespace flow {
	const int inf = 0x3f3f3f3f;
	struct Edge { 
		int to, cap, id;
		Edge *inv, *next;
	} edge[12050], *begin[6050];
	int edgeCnt = 0;
	int dist[6050];
	bool vis[6050];

	Edge *makeEdge(int u, int v, int cap, int id) {
		Edge *e = edge + edgeCnt++;
		e->to = v, e->cap = cap, e->id = id, e->next = begin[u];
		return begin[u] = e;
	}

	void addEdge(int u, int v, int cap, int id) {
		Edge *e1 = makeEdge(u, v, cap, id),
			 *e2 = makeEdge(v, u, 0, id);
		e1->inv = e2, e2->inv = e1;
	}

	bool reLable(int src, int sink) {
		static int Q[6050];
		memset(dist, -1, sizeof(dist));
		int qt = 0;
		Q[qt++] = src;
		dist[src] = 0;
		for ( int qh = 0; qh < qt; qh ++ ) {
			int u = Q[qh];
			for ( Edge *e = begin[u]; e; e = e->next )
				if ( e->cap ) {
					int v = e->to;
					if ( dist[v] != -1 )
						continue;
					dist[v] = dist[u] + 1;
					Q[qt++] = v;
				}
		}
		return dist[sink] != -1;
	}

	int aug(int cur, int sink, int flow) {
		if ( cur == sink )
			return flow;
		Edge *e;
		int res = 0;
		for ( e = begin[cur]; e; e = e->next ) 
			if ( e->cap && dist[e->to] == dist[cur] + 1 ) {
				int tmp = aug(e->to, sink, min(flow, e->cap));
				e->cap -= tmp, e->inv->cap += tmp;
				flow -= tmp, res += tmp;
				if ( !flow )
					break;
			}
		if ( !e )
			dist[cur] = -1;
		return res;
	}

	int dinic(int src, int sink) {
		int res = 0;
		while ( reLable(src, sink) ) 
			res += aug(src, sink, inf);
		return res;
	}

	void dfs(int x) {
		vis[x] = true;
		for ( Edge *e = begin[x]; e; e = e->next )
			if ( e->cap && !vis[e->to])
				dfs(e->to);
	}

	int mincut(int *res, int &nRes, int src, int sink) {
		int ans = dinic(src, sink);
		dfs(src);
		for ( int i = 0; i < edgeCnt; i += 2 ) {
			Edge *e = edge + i;
			if ( vis[e->inv->to] && !vis[e->to] )
				res[nRes++] = e->id;
		}
		return ans;
	}
}

struct Point {
	ll x, y;
	Point(){}
	Point(ll _x, ll _y):
		x(_x), y(_y){}
	bool operator< (const Point &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	bool operator== (const Point &t) const {
		return x == t.x && y == t.y;
	}
	long double length() const {
		return sqrt(x * x + y * y);
	}
} pointArr[6050];
int nPointArr = 0;

int sgn(ll x) {
	if ( x == 0 ) return 0;
	if ( x > 0 ) return 1;
	return -1;
}

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

ll cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

bool isItc(const Point &p1, const Point &p2, const Point &q1, const Point &q2) {
	return sgn(cross(q1 - p1, p2 - p1)) * sgn(cross(p2 - p1, q2 - p1)) >= 0
		&& sgn(cross(p1 - q1, q2 - q1)) * sgn(cross(q2 - q1, p2 - q1)) >= 0;
}

struct Segment {
	Point p1, p2;
	int w;
} seg[3050];
int nSeg;

struct Edge {
	int to, id, blk;
	bool marked;
	Edge *inv, *next;
} edge[6050], *begin[6050], *edgeArr[6050];
int edgeCnt = 0, nEdgeArr = 0;
Edge *makeEdge(int u, int v, int id) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->id = id, e->next = begin[u];
	return begin[u] = e;
}
void addEdge(int u, int v, int id) {
	Edge *e1 = makeEdge(u, v, id),
		 *e2 = makeEdge(v, u, id);
	e1->inv = e2, e2->inv = e1;
}

long double getAgl(const Point &p1, const Point &p2) {
	return acos((p1.x * p2.x + p1.y * p2.y) / (p1.length() * p2.length()));
}

bool compare(Edge *src, Edge *e1, Edge *e2) {
	Point p1 = pointArr[src->to], p2 = pointArr[src->inv->to],
		  p3 = pointArr[e1->to], p4 = pointArr[e2->to];
	int s1 = sgn(cross(p1 - p2, p3 - p1)),
		s2 = sgn(cross(p1 - p2, p4 - p1));
	if ( s1 != s2 )
		return s1 < s2;
	assert(s1 != 0);
	if ( s1 > 0 )
		return getAgl(p1 - p2, p3 - p1) < getAgl(p1 - p2, p4 - p1);
	else
		return getAgl(p1 - p2, p3 - p1) > getAgl(p1 - p2, p4 - p1);
}

void dfs(Edge *cur, int des, int blkId) {
	edgeArr[nEdgeArr++] = cur;
	cur->marked = true;
	cur->blk = blkId;
	if ( cur->to == des ) 
		return;
	Edge *best = NULL;
	for ( Edge *e = begin[cur->to]; e; e = e->next ) 
		if ( e != cur->inv ) {
			if ( best == NULL || compare(cur, e, best) )
				best = e;
		}
	assert(best != NULL && !best->marked);
	dfs(best, des, blkId);
}
int nBlk;
int out[3050], nOut;
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &nSeg);
	for ( int i = 0; i < nSeg; i ++ ) {
		ll x1, y1, x2, y2;
	   	int w;
		scanf(LL_FMT LL_FMT LL_FMT LL_FMT "%d", &x1, &y1, &x2, &y2, &w);
		seg[i].p1 = Point(x1, y1), seg[i].p2 = Point(x2, y2);
		seg[i].w = w;
		pointArr[nPointArr++] = Point(x1, y1);
		pointArr[nPointArr++] = Point(x2, y2);
	}
	Point src, des;
	scanf(LL_FMT LL_FMT, &src.x, &src.y);
	scanf(LL_FMT LL_FMT, &des.x, &des.y);
	int belSrc, belDes;

	sort(pointArr, pointArr + nPointArr);
	nPointArr = unique(pointArr, pointArr + nPointArr) - pointArr;
	for ( int i = 0; i < nSeg; i ++ ) {
		int u = lower_bound(pointArr, pointArr + nPointArr, seg[i].p1) - pointArr;
		int v = lower_bound(pointArr, pointArr + nPointArr, seg[i].p2) - pointArr;
		addEdge(u, v, i);
	}

	int antiCnt = 0;
	for ( int i = 0; i < edgeCnt; i ++ ) 
		if ( !(edge + i)->marked ) {
			nEdgeArr = 0;
			dfs(edge + i, (edge + i)->inv->to, nBlk++);
			ll area = 0;
			for ( int j = 0; j < nEdgeArr; j ++ ) {
				Point p1 = pointArr[edgeArr[j]->inv->to],
					  p2 = pointArr[edgeArr[j]->to];
				area += cross(p1, p2);
			}
			if ( area > 0 ) {
				antiCnt ++;
				continue; 
			}
			int cntSrc = 0, cntDes = 0;
			for ( int j = 0; j < nEdgeArr; j ++ ) {
				Edge *e = edgeArr[j];
				Point p1 = pointArr[e->inv->to],
					  p2 = pointArr[e->to];
				if ( p1.x > p2.x )
					swap(p1, p2);
				if ( p1.x < src.x && src.x <= p2.x )
					cntSrc += isItc(src, Point(src.x, 20000), p1, p2);
				if ( p1.x < des.x && des.x <= p2.x )
					cntDes += isItc(des, Point(des.x, 20000), p1, p2);
			}
			if ( cntSrc & 1 )
				belSrc = nBlk - 1;
			if ( cntDes & 1 )
				belDes = nBlk - 1;
		}
	assert(antiCnt == 1);
	assert(belSrc != belDes);
	for ( int i = 0; i < edgeCnt; i ++ ) {
		Edge *e = edge + i;
		flow::addEdge(e->blk, e->inv->blk, seg[e->id].w, e->id);
	}
	int ans = flow::mincut(out, nOut, belSrc, belDes);
	printf("%d\n", ans);
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("%d ", out[i] + 1);
}
