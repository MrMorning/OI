#include <cstdlib>
#include <cstdio>
int n, seed;
long long m;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%lld%d", &n, &m, &seed);
	srand(seed);
	printf("%d %lld\n", n, m);
	for(int i = 1; i <= n; i ++)
		printf("%d ", rand() % (m + 1));
}
