#include <cstdio>
const int N_MAX = 100010;
const int inf = 0x3f3f3f3f;
int a[N_MAX], b[N_MAX];
int n, res;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for (int s = 0, upper = 1 << n; s < upper; s ++) {
		int m = 0;
		for (int i = 1; i <= n; i ++)
			if (s & (1 << (i - 1)))
				b[++ m] = a[i];
		int ans = 0;
		for (int i = 1; i <= m; i ++)
			if (b[i] == i)
				ans ++;
		if (ans > res)
			res = ans;
	}
	printf("%d\n", res);
}
