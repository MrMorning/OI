#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
typedef long double val_t;

int num[32];
int M, N;
val_t X, res;
void dfs(int i, int left) {
	if ( i == M ) {
		num[M] = left;
		val_t tmp = 1;
		for ( int j = 1; j <= M; j ++ )
			tmp *= cos(X * num[j]);
		res += tmp;
		return;
	}
	for ( int x = 0; x <= left; x ++ ) {
		num[i] = x;
		dfs(i + 1, left - x);
	}
}

void solve() {
	scanf("%d%d", &M, &N);
	cin >> X;
	X /= N;
	res = 0;
	dfs(1, N);
	cout << res << '\n';
}

int main() {
	freopen("parcos.in", "r", stdin);
//	freopen("parcos.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
