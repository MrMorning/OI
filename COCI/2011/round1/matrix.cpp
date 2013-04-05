#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int a[444][444], f[444][444], g[444][444];
int N;
int main(){
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++)
		for(int j = 1; j <= N; j ++){
			scanf("%d", &a[i][j]);
			f[i][j] = f[i - 1][j - 1] + a[i][j];
			g[i][j] = g[i - 1][j + 1] + a[i][j];
		}
	int ans =-INF;
	for(int x = 1; x <= N; x ++)
		for(int y = 1; y <= N; y ++)
			for(int l = 1; l <= min(x, y); l ++){
				int p = f[x][y] - f[x - l][y - l],
					q = g[x][y - l + 1] - g[x - l][y + 1];
				ans = max(ans, p - q);
			}
	printf("%d\n", ans);
}
