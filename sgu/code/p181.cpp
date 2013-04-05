#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long ll;
int alpha, beta, gamma, M, k, f[1010];
int hash[1010];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d%d", &f[0], &alpha, &beta, &gamma, &M, &k);
	if(k == 0)
	{
		printf("%d\n", f[0]);
		return 0;
	}
	memset(hash, -1, sizeof(hash));
	f[0] %= M;
	hash[f[0]] = 0;
	int st = -1, len = -1;
	for(int i = 1; i <= M; i ++)
	{
		f[i] = ((ll)alpha * f[i - 1] * f[i - 1] + beta * f[i - 1] + gamma) % M;
		if(hash[f[i]] != -1)
		{
			st = hash[f[i]];
			len = i - hash[f[i]];
			break;
		}
		else
			hash[f[i]] = i;
	}
	assert(st != -1);
	if(k > st)
		k = (k - st) % len + st;
	printf("%d\n", f[k]);
}
