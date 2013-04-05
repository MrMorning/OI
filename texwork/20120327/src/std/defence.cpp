#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 1024;
int n, r, g, b, t;
long long f[kMaxN + 1][kMaxN + 1], ans;

int main() {
	freopen("defence.in", "r", stdin);
	freopen("defence.out", "w", stdout);
	scanf("%d%d%d%d%d", &n, &r, &g, &b, &t);
	ans = (long long)n * t * r;
	memset(f, -0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j <= i; ++ j)
			if (f[i][j] >= 0) {
				f[i + 1][j + 1] = max(f[i + 1][j + 1], f[i][j] + (long long)(t + b * j) * g * (i - j));
				f[i + 1][j] = max(f[i + 1][j], f[i][j] + (long long)(t + b * j) * g * (i - j));
			}
		for (int j = 0; j <= i + 1; ++ j)
			if (f[i + 1][j] >= 0) ans = max(ans, f[i + 1][j] + (long long)(t + b * j) * (n - i - 1) * ((long long)r + g * (i + 1 - j)));
	}
	cout << ans;
	return 0;
}


