#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long ll;
int alpha, beta, gamma, M, k, f[100010];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d%d", &f[0], &alpha, &beta, &gamma, &M, &k);
	f[0] %= M;
	for(int i = 1; i <= k; i ++)
		f[i] = ((ll)alpha * f[i - 1] * f[i - 1] + beta * f[i - 1] + gamma) % M;
	printf("%d\n", f[k]);
}
