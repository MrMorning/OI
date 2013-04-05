#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
const ll inf = 0x3f3f3f3f3f3f3f3fLL;
const int TOWN_MAX = 2010, AIR_MAX = 2010;
const int FLIGHT_MAX = 200010;

struct DisjointSet {
	int p[TOWN_MAX];
	void init(int n) {
		for ( int i = 0; i < n; i ++ )
			p[i] = i;
	}
	int find(int x) {
		return p[x] == x ? x : p[x] = find(p[x]);
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		assert(x != y);
		p[x] = y;
	}
} dset;
struct Flight {
	int a, b, c, p;
} fli[FLIGHT_MAX];

int edArr[FLIGHT_MAX], nEdArr;
int treeEd[TOWN_MAX], nTreeEd;
vector<int> air[AIR_MAX];
int nTown, nAir, nFli;

bool cmpWeight(int i, int j) {
	return fli[i].p < fli[j].p;
}
int main() {
	scanf("%d%d%d", &nTown, &nAir, &nFli);
	for ( int i = 0; i < nFli; i ++ ) {
		int a, b, c, p;
		scanf("%d%d%d%d", &a, &b, &c, &p);
		a --, b --, c --;
		air[c].push_back(i);
		fli[i].a = a, fli[i].b = b, fli[i].c = c, fli[i].p = p;
		edArr[nEdArr++] = i;
	}
	sort(edArr, edArr + nEdArr, cmpWeight);
	dset.init(nTown);
	for ( int i = 0; i < nEdArr; i ++ ) {
		int t = edArr[i];
		int a = fli[t].a, b = fli[t].b;
		if ( dset.find(a) != dset.find(b) ) {
			treeEd[nTreeEd++] = t;
			dset.merge(a, b);
		}
	}
	static vector<int> out;
	ll ans = inf;
   	int best = -1;
	for ( int i = 0; i < nAir; i ++ ) {
		dset.init(nTown);
		foreach(it, air[i]) {
			int a = fli[*it].a, b = fli[*it].b;
			if ( dset.find(a) != dset.find(b) )
				dset.merge(a, b);
		}
		ll fee = 0;
		static vector<int> trace;
		trace.clear();
		for ( int j = 0; j < nTreeEd; j ++ ) {
			int k = treeEd[j];
			Flight tmp = fli[k];
			if ( dset.find(tmp.a) != dset.find(tmp.b) ) {
				dset.merge(tmp.a, tmp.b);
				fee += tmp.p;
				trace.push_back(k);
			}
		}
		if ( fee < ans ) {
			best = i;
			ans = fee;
			out = trace;
		}
	}
	printf(LL_FMT " %d %d\n", ans, best + 1, (int)out.size());
	foreach(it, out)
		printf("%d\n", (*it) + 1);
}
