#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int kNMax = 100010;
const int kLogMax = 20;
const int kMod = 1000000009;

struct Info {
	int f0, f1;
	int e;
	Info(int _e = 1): e(_e){
		f0 = f1 = 0;
	}
};

Info operator+ (const Info &L, const Info &R) {
	Info T;
	T.f0 = T.f1 = L.f1 + R.f1;
	if ( L.e == 1 )
		T.f1 = max(T.f1, L.f0 + R.f1 + 1);
	if ( R.e == 1 )
		T.f1 = max(T.f1, R.f0 + L.f1 + 1);
	return T;
}

struct Node {
	int l, r, p;
	Node *ch[2];
	Info info;
	void upd() {
		info = (ch[0]?ch[0]->info:Info(0))+(ch[1]?ch[1]->info:Info(0));
	}
} node[kNMax * 4], *root;
int dis[kNMax], nDis;
int freePos = 0;
int log2[kNMax];
int st[kLogMax][kNMax];
int x[kNMax], y[kNMax];

int findMax(int l, int r) {
	int k = log2[r-l+1];
	int p = r-(1<<k)+1;
	if ( y[st[k][l]] > y[st[k][p]] )
		return st[k][l];
	return st[k][p];
}

Node *build(int l, int r) {
	if ( l > r ) return NULL;
	Node *t = node + freePos++;
	t->l = l, t->r = r, t->p = x[findMax(l, r)];
	if ( l == r )
		t->info = Info(1);
	else {
		t->ch[0] = build(l, t->p-1);
		t->ch[1] = build(t->p+1, r);
		t->upd();
	}
	return t;
}

Info ask(Node *cur, int l, int r) {
	if ( l > cur->r || r < cur->l ) return Info(0);
	if ( l <= cur->l && cur->r <= r ) 
		return cur->info;
	if ( l <= cur->p && cur->p <= r )
		return (cur->ch[0]?ask(cur->ch[0], l, r):Info(0))
			+ (cur->ch[1]?ask(cur->ch[1], l, r):Info(0));
	else if ( r < cur->p ) return ask(cur->ch[0], l, r);
	else return ask(cur->ch[1], l, r);
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m, k, a, b, c, d;
	scanf("%d%d", &n, &k);
	for ( int i = 1; i <= k; i ++ )
		scanf("%d%d", &x[i], &y[i]);
	scanf("%d%d%d%d", &a, &b, &c, &d);
	for ( int i = k+1; i <= n; i ++ ) { 
		x[i] = ((ll)a*x[i-1]+b)%kMod;
		y[i] = ((ll)c*y[i-1]+d)%kMod;
	}
	for ( int i = 1; i <= n; i ++ )
		dis[nDis++] = x[i];
	sort(dis, dis+nDis);
	nDis = unique(dis, dis+nDis)-dis;

	for ( int i = 1; (1 << i) <= n; i ++ )
		log2[1<<i] = i;
	for ( int i = 2; i <= n; i ++ )
		if ( !log2[i] )
			log2[i] = log2[i-1];
	for ( int i = 1; i <= n; i ++ ) {
		x[i] = lower_bound(dis, dis+nDis, x[i])-dis;
		st[0][x[i]] = i;
	}
	for ( int k = 1; k < kLogMax; k ++ )
		for ( int i = 0; i < nDis; i ++ ) {
			st[k][i] = st[k-1][i];
			int p = i+(1<<(k-1));
			if ( p < nDis && y[st[k-1][p]] > y[st[k][i]] )
				st[k][i] = st[k-1][p];
		}
	root = build(0, nDis-1);
	scanf("%d", &m);
	while ( m -- ) {
		int l, r;
		scanf("%d%d", &l, &r);
		l = lower_bound(dis, dis+nDis, l)-dis;
		r = upper_bound(dis, dis+nDis, r)-dis-1;
		if ( l > r ) {
			printf("0\n");
			continue;
		}
		Info info = ask(root, l, r);
		printf("%d\n", max(info.f0, info.f1));
	}
}
