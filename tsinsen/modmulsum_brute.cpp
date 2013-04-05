#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll kMod = 19940417;

int plus(int a, int b) {
	return (a + b)%kMod;
}

int minus(int a, int b) {
	return (a - b + kMod) % kMod;
}

int mul(int a, int b) {
	return (ll)a * b % kMod;
}

int main() {
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	int res = 0;
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ )
			if ( i != j )
				res = plus(res, mul(n%i,m%j));
	printf("%d\n", res);
}
