#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;

const int kNMax = 705;
const int kDigMax = 30;
const int BASE = 1000000;

struct BigInt {
	int dig[kDigMax];
	int len;
	BigInt(){}
	BigInt(int x) {
		len = 0;
		while ( x ) {
			dig[len++] = x % BASE;
			x /= BASE;
		}
	}
	void print() {
		if ( len == 0 ) printf("0");
		else {
			printf("%d", dig[len-1]);
			for ( int i = len-2; i >= 0; i -- )
				printf("%06d", dig[i]);
		}
		printf("\n");
	}
	bool operator< (const BigInt &T) const {
		if ( len != T.len ) 
			return len < T.len;
		for ( int i = len-1; i >= 0; i -- )
			if ( dig[i] != T.dig[i] ) return dig[i] < T.dig[i];
		return false;
	}
};

BigInt operator*(const BigInt &A, const BigInt B) {
	static BigInt C;
	static ll dig[kDigMax];
	C.len = A.len + B.len;
	memset(dig, 0, sizeof(dig));
	for ( int i = 0; i < A.len; i ++ )
		for ( int j = 0; j < B.len; j ++ )
			dig[i+j] += (ll)A.dig[i] * B.dig[j];
	for ( int i = 0; i < C.len; i ++ ) {
		dig[i+1] += dig[i] / BASE;
		dig[i] %= BASE;
	}
	while ( C.len && dig[C.len-1] == 0 ) C.len--;
	for ( int i = 0; i < C.len; i ++ )
		C.dig[i] = (int)dig[i];
	return C;
}


BigInt f[kNMax], g[kNMax], h[kNMax], w[kNMax];
vector<int> adj[kNMax];
int nv;

void work(int x, int pa) {
	foreach(it, adj[x]) 
		if ( (*it) != pa ) 
			work(*it, x);
	int sz = (int)adj[x].size() - 1 + (pa == -1);
	g[0] = 1;
	for ( int i = 1; i <= sz; i++ )
		g[i] = 0;
	h[x] = 1;
	foreach(it, adj[x]) 
		if ( (*it) != pa ) {
			BigInt acc = 1;
			foreach(it2, adj[x])
				if ( (*it2) != pa && (*it2) != (*it) )
					acc = acc * f[*it2];
			f[x] = max(f[x], acc * w[*it]);
			h[x] = h[x] * f[*it];
			for ( int j = sz; j >= 0; j -- ) {
				g[j] = g[j]*f[*it];
				if ( j >= 1 ) 
					g[j] = max(g[j], g[j-1]*h[*it]);
			}
		}
	for ( int j = 0; j <= sz; j ++ ) {
		f[x] = max(f[x], g[j]*(j+1));
		w[x] = max(w[x], g[j]*(j+2));
	}
}

int main() {
	scanf("%d", &nv);
	for ( int i = 0; i < nv-1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].pb(b); adj[b].pb(a);
	}
	work(1, -1);
	f[1].print();
}
