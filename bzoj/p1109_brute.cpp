#include <cstdio>
const int N_MAX = 100010;
const int inf = 0x3f3f3f3f;
int a[N_MAX], f[N_MAX];
int n;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i ++) 
		if (a[i] - i <= 0){
			f[i] = 1;
			for (int j = 1; j < i; j ++)
				if (a[j] - j <= 0)
					if (a[i] - a[j] <= i - j)
						if (a[i] > a[j] && f[j] + 1 > f[i])
							f[i] = f[j] + 1;
		}
	int res = 0;
	for (int i = 1; i <= n; i ++)
		if (f[i] > res)
			res = f[i];
	printf("%d\n", res);
}
