#include <cstdio>
#include <map>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int kNMax = 100010;
const int kInf = 0x3f3f3f3f;

typedef pair<int, int> key_t;
struct myCmp {
	bool operator() (const key_t &T1, const key_t &T2) const {
		return T1.first < T2.first || (T1.first == T2.first && T1.second > T2.second);
	}	
};
typedef pair<int, int> val_t;
typedef map<key_t, val_t, myCmp> map_t;
typedef map_t::iterator itr_t;

struct Stuff {
	int v, c, l, r, id;
	bool operator< (const Stuff &T) const {
		return (c + l + r < T.c + T.l + T.r)
			|| (c+l+r == T.c+T.l+T.r && id < T.id);
	}
} p[kNMax];

map_t mp;

itr_t search(int i) {
	itr_t res = mp.lower_bound(make_pair(i, kInf));
	if ( res->first.first != i ) return mp.end();
	return res;
}

int ans = 0;
int out[kNMax], nOut;

void solve(Stuff p[], int n) {
	mp.clear();
	mp.insert(make_pair(make_pair(0, -1), make_pair(0, -1)));
	int target = p[0].l + p[0].r + p[0].c;
	for ( int i = 0; i < n; i ++ ) {
		itr_t it = search(p[i].l);
		if ( it != mp.end() ) {
			itr_t it2 = search(p[i].l + p[i].c);
			if ( it2 == mp.end() || it2->second.first < it->second.first + p[i].v ) 
				mp[make_pair(p[i].l+p[i].c, i)] = make_pair(it->second.first + p[i].v, it->first.second);
		}
	}

	itr_t des = search(target);
	if ( des != mp.end() && des->second.first > ans ) {
		ans = des->second.first;
		itr_t cur = des;
		nOut = 0;
		while ( cur->first.second != -1 ) {
			out[nOut++] = p[cur->first.second].id;
			cur = mp.lower_bound(make_pair(cur->first.first - p[cur->first.second].c, cur->second.second));
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d%d%d", &p[i].v, &p[i].c, &p[i].l, &p[i].r);	
		p[i].id = i;
	}
	sort(p, p + n);
	for ( int i = 0; i < n; i ++ ) {
		int st = i;
		while ( i+1 < n && p[i+1].c+p[i+1].l+p[i+1].r == p[i].c+p[i].l+p[i].r )
			i ++;
		solve(p + st, i-st+1);
	}
	sort(out, out + nOut);
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ )
		printf("%d ", out[i] + 1);
}
