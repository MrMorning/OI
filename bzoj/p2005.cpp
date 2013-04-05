#include <iostream>
#include <cstdio>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
typedef long long bignum_t;
using namespace std;
bignum_t f[100001], ans;
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	for(int i = MIN(n, m); i >= 1; i --)
	{
		f[i] = (bignum_t)(n / i) * (m / i);
		for(int j = 2; j * i <= MIN(n, m); j ++)
			f[i] -= f[j * i];
		ans += f[i] * i;
	}
	cout << ans * 2 - (bignum_t)n * m << endl;
}
