#include <cstdio>
#include <cassert>
#include <cstring>
const int kNMax = 150010;
int parent[kNMax], father[kNMax];
int realval[kNMax], val[kNMax];
int nv, nc;
bool vis[kNMax];
int find(int i) {
	return parent[i]==i?i:parent[i]=find(parent[i]);
}
void merge(int u, int v) {
	u = find(u), v = find(v);
	assert(u != v);
	realval[v] += realval[u];
	parent[u] = v;
}
void reverse(int u) {
	u = find(u);
	int next = find(father[u]);
	while ( next ) {
		int t = u;
		u = next;
		next = find(father[u]);
		father[u] = t;
	}
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nv, &nc);
	for ( int i = 1; i <= nv; i ++ ) {
		scanf("%d", &val[i]);
		realval[i] = val[i];
		parent[i] = i;
		father[i] = 0;
	}
	for ( int qur = 0; qur < nc; qur ++ ) {
		int p, a, b;
		scanf("%d%d%d", &p, &a, &b);
		if ( p == 1 ) {
			a = find(a), b = find(b);
			int u = a, v = b;
			if ( a != b ) {
				memset(vis, 0, sizeof(bool)*(nv+1));
				vis[a] = true;
				while ( find(father[a]) ) {
					a = find(father[a]);
					vis[a] = true; 
				}
				int q = -1;
				if ( vis[b] ) {
					q = b;
				} else {
					vis[b] = true;
					while ( find(father[b]) ) {
						b = find(father[b]);
						if ( vis[b] ) {
							q = b;
							break;
						}
					}
				}
				if ( q == -1 ) {
					reverse(v);
					father[v] = u;
				} else {
					for ( int i = u; i != q; i = find(father[i]) )
						merge(i, father[i]);
					for ( int i = v; i != q; i = find(father[i]) )
						merge(i, father[i]);
				}
			} 
		}
		else if ( p == 2 ) {
			realval[find(a)] += b-val[a];
			val[a] = b;
		}
		else {
			a = find(a), b = find(b);
			int u = a, v = b;
			if ( u == v ) {
				printf("%d\n", realval[u]);
				continue;
			}
			memset(vis, 0, sizeof(bool)*(nv+1));
			vis[a] = true;
			while ( find(father[a]) ) {
				a = find(father[a]);
				vis[a] = true; 
			}
			int q = -1;
			if ( vis[b] ) {
				q = b;
			} else {
				vis[b] = true;
				while ( find(father[b]) ) {
					b = find(father[b]);
					if ( vis[b] ) {
						q = b;
						break;
					}
				}
			}
			if ( q == -1 )
				puts("-1");
			else {
				int ans = realval[q];
				for ( int i = u; i != q; i = find(father[i]) )
					ans += realval[i];
				for ( int i = v; i != q; i = find(father[i]) )
					ans += realval[i];
				printf("%d\n", ans);
			}
		}
	}
}

