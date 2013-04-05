#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
using namespace std;
const int kInf = 0x3f3f3f3f;
const int kVtxMax = 3010;
const int kSegMax = kVtxMax * 10;
const int kDisMax = 1010;
bool vis[kSegMax][2];
vector<int> adj[kVtxMax];
int sgn(int x) {
	if ( x == 0 ) return 0;
	return x > 0 ? 1 : -1;
}
struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	double mod() {
		return sqrt(x*x+y*y);
	}
} p[kVtxMax];
Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x-p2.x, p1.y-p2.y);
}
int cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}
int dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}
struct Segment {
	int p, q, v1, v2;
	int comp[2];
	int getDir(int x) {
		return x == q;
	}
} seg[kSegMax];
bool better(int s, int t1, int t2, int x) { 
	Point v0 = p[x]-p[seg[s].p+seg[s].q-x],
		  v1 = p[seg[t1].p+seg[t1].q-x]-p[x],
		  v2 = p[seg[t2].p+seg[t2].q-x]-p[x];
	int flag1 = sgn(cross(v0, v1)), flag2 = sgn(cross(v0, v2));
	if ( flag1 != flag2 ) 
		return flag1 < flag2;
	double dt1 = dot(v0, v1), dt2 = dot(v0, v2);
	double agl1 = acos(dt1/v0.mod()/v1.mod()),
		   agl2 = acos(dt2/v0.mod()/v2.mod());
	if ( flag1 == -1 )
		return agl1 > agl2;
	else
		return agl1 < agl2;
}
void dfs(int x, int s, int comp) {
	int dir = seg[s].getDir(x);
	vis[s][dir] = true;
	seg[s].comp[dir] = comp;
	int best = -1;
	foreach(it, adj[x]) {
		if ( *it != s ) {
			if ( best == -1 || better(s, *it, best, x) )
				best = *it;
		}
	}
	//  fprintf(stderr, "%d\n", best);
	if ( best == -1 || vis[best][!seg[best].getDir(x)] ) 
		return;
	dfs(seg[best].p+seg[best].q-x, best, comp);
}
struct Data {
	int u, v, key;
	bool operator< (const Data &T) const {
		return key < T.key;
	}
} dat[kDisMax];
int parent[kDisMax];
int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}
void merge(int x, int y) {
	x = find(x), y = find(y);
	parent[x] = y;
}

pair<int, int> minIn[kVtxMax];
vector<pair<int, int> > adj2[kVtxMax];
int toward[kVtxMax];
int tag[kVtxMax];
bool okay[kVtxMax];

int directedMST(int nv, int rt) {
	static int vis[kVtxMax];
	for ( int i = 1; i <= nv; i ++ )
		okay[i] = true;
	int res = 0;
	while ( 1 ) {
		for ( int i = 1; i <= nv; i ++ )
			if ( okay[i] )
				minIn[i] = mp(-1, kInf+1);
		for ( int i = 1; i <= nv; i ++ )
			if ( okay[i] )
				foreach(it, adj2[i]) {
					if ( it->second < minIn[it->first].second )
						minIn[it->first] = make_pair(i, it->second);
				}
		memset(toward, -1, sizeof(toward));
		for ( int i = 1; i <= nv; i ++ )
			if ( i != rt && okay[i] ) {
				assert(minIn[i].first != -1);
				toward[i] = minIn[i].first;
			}
		memset(vis, -1, sizeof(vis));
		bool changed = false;
		for ( int i = 1; i <= nv; i ++ )
			if ( okay[i] && i != rt && vis[i] == -1 ) {
				static int tmp[kVtxMax];
				bool found = false;

				int nTmp = 0;
				int cur = i;
				while ( 1 ) {
					vis[cur] = i;
					if ( toward[cur] == -1 ) {
						assert(cur == rt);
						break;
					} else if ( vis[toward[cur]] == i ) {
						found = true;
						int st = cur;
						tmp[++nTmp] = st;
						st = toward[st];
						while ( st != cur ) {
							tmp[++nTmp] = st;
							st = toward[st];
						}
						break;
					} else if ( vis[toward[cur]] != -1 )
						break;
					cur = toward[cur];
				}

				if ( found ) {
					int v = ++nv;
					okay[v] = true;
					static int stamp = 0;
					stamp ++;
					for ( int j = 1; j <= nTmp; j ++ ) {
						int u = tmp[j];
					//	fprintf(stderr, "cycle %d has %d\n", stamp, u);
						res += minIn[u].second;
						tag[u] = stamp;
						okay[u] = false;
						foreach(it, adj2[u])
							adj2[v].pb(*it);
					}

					for ( int j = 1; j < nv; j ++ )
						if ( okay[j] && tag[j] != stamp ) {
							int sz = adj2[j].size();
							for ( int k = 0; k < sz; k ++ ) 
								if ( tag[adj2[j][k].first] == stamp ) {
									adj2[j][k].second -= minIn[adj2[j][k].first].second;
									adj2[j][k].first = v;
								}
						}
					changed = true;
					break;
				}
			}
		if ( !changed ) {
			for ( int i = 1; i <= nv; i ++ )
				if ( okay[i] && i != rt )
					res += minIn[i].second;
			break;
		}
	}
	return res;
}

void debug() {
#define ADD(x, y, z) adj2[x].pb(mp(y,z))
	ADD(1,2,10);
	ADD(2,3,1);
	ADD(3,4,1);
	ADD(4,2,1);
	ADD(2,5,1);
	ADD(3,5,5);
	ADD(3,8,4);
	ADD(3,6,4);
	ADD(8,4,4);
	ADD(4,6,5);
	ADD(4,7,5);
	fprintf(stderr, "%d\n", directedMST(8,1));
}

int main() {
	freopen("t.in", "r", stdin);

//	debug();
//	return 0;

	int np, ns;
	scanf("%d%d", &np, &ns);
	for ( int i = 1; i <= np; i ++ )
		scanf("%d%d", &p[i].x, &p[i].y);
	bool allSame = true;
	for ( int i = 1; i <= ns; i ++ ) {
		int p, q, v1, v2;
		scanf("%d%d%d%d", &p, &q, &v1, &v2);
		allSame &= v1 == v2;
		if ( v1 == 0 )
			v1 = kInf;
		if ( v2 == 0 )
			v2 = kInf;
		seg[i].v1 = v1, seg[i].v2 = v2;
		seg[i].p = p, seg[i].q = q;
		adj[p].pb(i);
		adj[q].pb(i);
	}
	int nComp = 0;
	for ( int i = 1; i <= ns; i ++ ) {
		if ( !vis[i][1] )
			dfs(seg[i].q, i, ++nComp);
		if ( !vis[i][0] )
			dfs(seg[i].p, i, ++nComp);
	}
	if ( allSame ) {
		for ( int i = 1; i <= ns; i ++ ) {
			dat[i].u = seg[i].comp[0];
			dat[i].v = seg[i].comp[1];
			dat[i].key = min(seg[i].v1, seg[i].v2);
		}
		sort(dat+1, dat+1+ns);
		for ( int i = 1; i <= nComp; i ++ )
			parent[i] = i;
		int ans = 0;
		for ( int i = 1; i <= ns; i ++ ) {
			if ( find(dat[i].u) == find(dat[i].v) )
				continue;
			merge(dat[i].u, dat[i].v);
			ans += dat[i].key;
		}
		printf("%d\n", ans);
	} else {
		for ( int i = 1; i <= ns; i ++ ) {
			int x = seg[i].comp[0],
				y = seg[i].comp[1];
			if ( seg[i].v1 != kInf ) {
				//		fprintf(stderr, "%d->%d:%d\n", x, y, seg[i].v1);
				adj2[x].push_back(mp(y, seg[i].v1));
			}
			if ( seg[i].v2 != kInf ) {
				//		fprintf(stderr, "%d->%d:%d\n", y, x, seg[i].v2);
				adj2[y].push_back(mp(x, seg[i].v2));
			}
		}
		for ( int i = 1; i <= nComp; i ++ )
			adj2[nComp+1].push_back(mp(i, kInf));
		printf("%d\n", (directedMST(nComp+1, nComp+1)-kInf));
	}
}

