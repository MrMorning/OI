#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;
const int kNMax = 100010;
const int kAMax = 4*kNMax;
const int kSMax = 2*kNMax;
const int kMMax = 2*kAMax;
const double kEps = 1e-8;

inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

namespace solve1 {
	struct Point {
		int x, y;
		Point(){}
		Point(int xx, int yy):
			x(xx), y(yy){}
	};

	Point operator- (const Point &p1, const Point &p2) {
		return Point(p1.x-p2.x, p1.y-p2.y);
	}

	int cross(const Point &p1, const Point &p2) {
		return p1.x*p2.y - p1.y*p2.x;
	}
	int dot(const Point &p1, const Point &p2) {
		return p1.x*p2.x + p1.y*p2.y;
	}

	double calcAgl(const Point &p) {
		assert(!(p.x==0&&p.y==0));
		return atan2(p.y,p.x);
	}

	bool cmpDb(double a, double b) {
		return sgn(a-b) < 0;
	}

	struct Segment {
		Point p1, p2;
		bool del;
	} wolf[kNMax], sheep[kNMax];

	double agl[kAMax];
	int nAgl;
	int nWolf, nSheep;

	void main(vector<pair<int, int> > &res1, vector<pair<int, int> > &res2, int &nPart) {
		scanf("%d%d", &nWolf, &nSheep);
		if ( nWolf <= 1 && nSheep == 0 ) {
			printf("%d\n", nWolf);
			exit(0);
		}
		for ( int i = 1; i <= nWolf; i ++ ) {
			scanf("%d%d%d%d", &wolf[i].p1.x, &wolf[i].p1.y,
					&wolf[i].p2.x, &wolf[i].p2.y);
			if ( cross(wolf[i].p1-Point(0,0),wolf[i].p2-Point(0,0)) == 0
			  && dot(wolf[i].p1-Point(0,0),wolf[i].p2-Point(0,0)) <= 0 ) {
				wolf[i].del = true;
			} else {
				if ( cross(wolf[i].p1, wolf[i].p2) < 0 )
					swap(wolf[i].p1, wolf[i].p2);
				agl[nAgl++] = calcAgl(wolf[i].p1);
				agl[nAgl++] = calcAgl(wolf[i].p2);
			}
		}
		for ( int i = 1; i <= nSheep; i ++ ) {
			scanf("%d%d%d%d", &sheep[i].p1.x, &sheep[i].p1.y,
					&sheep[i].p2.x, &sheep[i].p2.y);
			if ( cross(sheep[i].p1-Point(0,0), sheep[i].p2-Point(0,0)) == 0
					&& dot(sheep[i].p1-Point(0,0),sheep[i].p2-Point(0,0)) <= 0 ) {
				puts("No solution");
				exit(0);
			}
			if ( cross(sheep[i].p1, sheep[i].p2) < 0 )
				swap(sheep[i].p1, sheep[i].p2);
			agl[nAgl++] = calcAgl(sheep[i].p1);
			agl[nAgl++] = calcAgl(sheep[i].p2);
		}
		sort(agl, agl+nAgl);
		nAgl = unique(agl, agl+nAgl)-agl;

		for ( int i = 1; i <= nWolf; i ++ ) 
			if ( !wolf[i].del ) {
				int lb = lower_bound(agl, agl+nAgl, calcAgl(wolf[i].p1), cmpDb)-agl,
					rb = lower_bound(agl, agl+nAgl, calcAgl(wolf[i].p2), cmpDb)-agl;
				res1.pb(mp(2*lb, 2*rb));
			}
		for ( int i = 1; i <= nSheep; i ++ ) {
			int lb = lower_bound(agl, agl+nAgl, calcAgl(sheep[i].p1), cmpDb)-agl,
				rb = lower_bound(agl, agl+nAgl, calcAgl(sheep[i].p2), cmpDb)-agl;
			res2.pb(mp(2*lb, 2*rb));
		}
		nPart = nAgl * 2;
	}
};

namespace solve2 {

	struct Array {
		int ele[kMMax];
		int& operator[] (int i) {
			return ele[i+1];
		}
	};

	struct DisjointSet {
		Array p;
		int find(int x) {
			static int stk[kMMax];
			int cur = x, top = 0;
			while ( p[cur] != cur ) {
				stk[top++] = cur;
				cur = p[cur];
			}
			while ( top ) 
				p[stk[--top]] = cur;
		   	return cur; 
		}
		void merge(int i, int j) {
			i = find(i), j = find(j);
			p[i] = j;
		}
	} ds;

	struct Segment {
		int l, r, pos;
		Segment(){}
		Segment(int ll, int rr):
			l(ll), r(rr){}
	} seg1[kSMax], seg2[kSMax];
	int n1, n2;
	int log2[kSMax];
	int st[20][kSMax];
	int f[20][kSMax];

	bool cmpRL(const Segment &A, const Segment &B) {
		return A.r < B.r || (A.r == B.r && A.l > B.l);
	}

	bool cmpEq(const Segment &A, const Segment &B) {
		return A.r == B.r && A.l >= B.l;
	}

	int getGreater(int i, int j) {
		return seg1[i].l > seg1[j].l ? i : j;
	}

	void initST(int n) {
		for ( int i = 0; (1<<i) <= n; i ++ )
			log2[1<<i] = i;
		for ( int i = 2; i <= n; i ++ )
			if ( !log2[i] ) log2[i] = log2[i-1];

		for ( int i = 0; i < n; i ++ ) 
			st[0][i] = i;
		for ( int k = 1; (1<<k) <= n; k ++ ) {
			for ( int i = 0; i < n; i ++ ) {
				st[k][i] = st[k-1][i];
				int p = i+(1<<(k-1));
				if ( p < n )
					st[k][i] = getGreater(st[k][i], st[k-1][p]);
			}
		}
	}

	int rmq(int l, int r) {
		int k = log2[r-l+1];
		return getGreater(st[k][l], st[k][r-(1<<k)+1]);
	}

	int findNext(int p) {
		int lb = p+1 -1, rb = n1-1;
		while ( lb < rb-1 ) {
			int mid = (lb + rb) / 2;
			if ( seg1[rmq(p+1,mid)].l > seg1[p].r )
				rb = mid;
			else 
				lb = mid;
		}
		if ( seg1[rb].l > seg1[p].r ) 
			return rb;
		else return -1;
	}

	void main(const vector<pair<int, int> > &_seg1, const vector<pair<int, int> > &_seg2, int m) {
		n1 = _seg1.size(), n2 = _seg2.size();
		int len = n1;
		int cnt1 = 0, cnt2 = 0;
		for ( int i = 0; i < n1; i ++ ) {
			seg1[i].l = _seg1[i].first, seg1[i].r = _seg1[i].second;
			if ( seg1[i].r >= seg1[i].l ) {
				seg1[n1+i] = Segment(seg1[i].l+m, seg1[i].r+m);
				cnt1++;
			} else 
				seg1[i].r += m;
		}
		n1 += cnt1;
		for ( int i = 0; i < n2; i ++ ) {
			seg2[i].l = _seg2[i].first, seg2[i].r = _seg2[i].second;
			if ( seg2[i].r >= seg2[i].l ) {
				seg2[n2+i] = Segment(seg2[i].l+m, seg2[i].r+m);
				cnt2++;
			} else 
				seg2[i].r += m;
		}
		n2 += cnt2;

		for ( int i = 0; i <= 2*m; i ++ )
			ds.p[i] = i;
		for ( int i = 0; i < n2; i ++ ) {
			for ( int j = seg2[i].r; j >= seg2[i].l; j -- ) {
				if ( ds.find(j) != j ) 
					j = ds.find(j);
				if ( j < seg2[i].l ) break;
				ds.merge(j, j-1);
			}
		}

		for ( int i = 0; i < n1; i ++ ) {
			if ( ds.find(seg1[i].r) < seg1[i].l ) {
				puts("No solution");
				exit(0);
			}
			seg1[i].r = ds.find(seg1[i].r);
		}
		sort(seg1, seg1+n1, cmpRL);
		for ( int i = 0; i < n1; i ++ )
			seg1[i].pos = i;

		n1 = unique(seg1, seg1+n1, cmpEq) - seg1;
		initST(n1);
		for ( int i = 0; i < n1; i ++ )
			f[0][i] = findNext(i);
		int lim = 0;
		for ( int k = 1; (1<<k) <= n1; lim = k, k ++ )
			for ( int i = 0; i < n1; i ++ )
				f[k][i] = f[k-1][i]==-1?-1:f[k-1][f[k-1][i]];

		int ans = n1;
		for ( int src = 0; seg1[n1-1].pos-seg1[src].pos >= len-1; src ++ ) {
			int acc = 0, cur = src;
			for ( int k = lim; k >= 0; k -- )
				if ( f[k][cur] != -1 && seg1[f[k][cur]].pos-seg1[src].pos+1 <= len ) {
					acc += 1<<k;
					cur = f[k][cur];
				}
			ans = min(ans, acc+1);
		}
		printf("%d\n", ans);
	}
};

int main() {
	freopen("t.in", "r", stdin);
	int nPart;
	vector<pair<int, int> > res1, res2;
	solve1::main(res1, res2, nPart);
	solve2::main(res1, res2, nPart);
}
