#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int a[1 << 20], b[1 << 20];

int aPlace[1 << 20], mp[1 << 20], N, M;

void scan() {
	scanf("%d%d", &N, &M);
	memset(mp, -1, sizeof(mp));

	for ( int i = 0; i < N; i ++ ) {
		scanf("%d", a + i);
		aPlace[a[i]] = 1;
	}
	for ( int i = 0; i  < M; i ++ ) {
		scanf("%d", b + i);
		mp[b[i]] = i;
	}
}

int valid(int mid, int l2, int l1) {
	if ( l1 == -1 || l2 == -1 ) return 0;
	if ( mid < l2 && mid < l1 && l2 < l1 ) return 0;
	if ( mid > l1 && mid < l2 ) return 0;
	if ( l1 < mid && l2 < l1 ) return 0;
	if ( mid == l2 ) return 0;
	return 1;
}

void solve() {
	int l = -1, r = 0;

	int mxans = 0;

	for ( int i = N; i < 3 * N; i ++ )
		a[i] = a[i % N];

	while ( l < N - 1 ) {
		l ++;
		if ( mp[a[l]] != -1 ) mxans = max(mxans, 1);
		if ( mp[a[l + 1]] == -1 || mp[a[l]] == -1 ) continue;
		r = max(r, l + 2);

		while ( valid(mp[a[l]], mp[a[r]], mp[a[r - 1]]) )
			r ++;
		mxans = max(mxans, r - l);
	}
	printf("%d\n", min(mxans, N));
}

int main() {
	freopen("t.in", "r", stdin);
	scan();
	solve();
}
