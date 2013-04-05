#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 55;
int n, m;
int f[N_MAX][N_MAX];
bool on[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < n - 1; i ++) {
		int u, v;
		scanf("%d%d", &u, &v);
		f[u][v] = f[v][u] = 1;
	}
	for (int k = 1; k <= n; k ++)
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	scanf("%d", &m);
	while (m --) {
		static char cmd[4];
		scanf("%s", cmd);
		if (cmd[0] == 'G') {
			int res = -1;
			for (int i = 1; i <= n; i ++)
				for (int j = 1; j <= n; j ++)
					if (!on[i] && !on[j])
						res = max(res, f[i][j]);
			printf("%d\n", res);
		}
		else {
			int x;
			scanf("%d", &x);
			on[x] ^= 1;
		}
	}
}
