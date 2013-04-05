#include <cstdio>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAXN 100001
typedef double Val_t;
Val_t f[MAXN], A[MAXN], B[MAXN], rate[MAXN];
int n;

void naked()
{
	for(int i = 1; i <= n; i ++)
	{
		f[i] = f[i - 1];
		for(int j = 1; j < i; j ++)
		{
			Val_t tmp = f[j] / (rate[j] * A[j] + B[j]);
			f[i] = MAX(f[i], tmp * rate[j] * A[i] + tmp * B[i]);
		}
	}
	printf("%.3lf\n", f[n]);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%lf", &n, &f[0]);
	for(int i = 1; i <= n; i ++)
		scanf("%lf%lf%lf", &A[i], &B[i], &rate[i]);
	naked();
}
