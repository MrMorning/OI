#include <cstdio>
#include <cstring>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef long long crdnt_t;
#define CRDNT_FMT "%lld"
const int N_MAX = 1000001;
int n, c[3], sum[N_MAX];
crdnt_t f[N_MAX];
void init()
{
	scanf("%d", &n);
	scanf("%d%d%d", &c[0], &c[1], &c[2]);
	for(int i = 1, w; i <= n; i ++)
	{
		scanf("%d", &w);
		sum[i] = sum[i - 1] + w;
	}
}
inline crdnt_t calc_f(int x)
{
	return (crdnt_t)c[0] * x * x + c[1] * x + c[2];
}
void bruce()
{
	memset(f, -0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < i; j ++)
			f[i] = MAX(f[i], f[j] + calc_f(sum[i] - sum[j]));
	printf(CRDNT_FMT "\n", f[n]);
}
int main()
{
	freopen("t.in", "r", stdin);
	init();
	bruce();
}
