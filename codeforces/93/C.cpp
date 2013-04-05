#include <cstdio>
int f[2][2010], g[2][2010];
char str[2010][2010];
int N;
int ans;
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++)
		scanf("%s", str[i] + 1);
	for(int k = N - 1; k > 0; k --)
		for(int x = 1; x <= N - k; x ++){
			int t = str[x][x + k] - '0';
			if((t + f[0][x] + g[0][x + k]) & 1){
				ans ++;
				f[0][x] ++;
				g[0][x + k] ++;
			}
		}
	for(int k = N - 1; k > 0; k --)
		for(int y = 1; y <= N - k; y ++){
			int t = str[y + k][y] - '0';
			if((t + f[1][y + k] + g[1][y]) & 1){
				ans ++;
				f[1][y + k] ++;
				g[1][y] ++;
			}
		}
	for(int i = 1; i <= N; i ++){
		int t = str[i][i] - '0';
		if((t + f[0][i] + f[1][i] + g[0][i] + g[1][i]) & 1)
			ans ++;
	}
	printf("%d\n", ans);
}
