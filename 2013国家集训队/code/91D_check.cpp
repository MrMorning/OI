#include <cstdio>
#include <cassert>
const int kNMax = 100010;
int a[kNMax];
int n;
int main() {
	FILE *fdat = fopen("t.in", "r"),
		 *fout = fopen("t.out", "r");
	fscanf(fdat, "%d", &n);
	for ( int i = 1; i <= n; i ++ )
		fscanf(fdat, "%d", &a[i]);
	int ans;
	fscanf(fout, "%d", &ans);
	while ( ans -- ) {
		static int t1[kNMax], t2[kNMax], mem[kNMax];
		int m;
		fscanf(fout, "%d", &m);
		for ( int i = 0; i < m; i ++ ) {
			fscanf(fout, "%d", &t1[i]);
			mem[t1[i]] = a[t1[i]];
		}
		for ( int i = 0; i < m; i ++ ) {
			fscanf(fout, "%d", &t2[i]);
			a[t2[i]] = mem[t1[i]];
		}
	}
	for ( int i = 1; i <= n; i ++ )
		assert(a[i] == i);
}
