#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 21;
int w[N][N][N][N], s[N][N][N][N];
int n;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= n; k ++)
				for(int l = 1; l <= n; l ++)
					scanf("%d", &w[i][j][k][l]);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= n; k ++)
				for(int l = 1; l <= n; l ++)
					s[i][j][k][l] += s[i-1][j][k][l] + s[i][j-1][k][l] + s[i][j][k-1][l] + s[i][j][k][l-1]
						- (s[i-1][j-1][k][l] + s[i-1][j][k-1][l] + s[i-1][j][k][l-1] + s[i][j-1][k-1][l] + s[i][j-1][k][l-1] + s[i][j][k-1][l-1])
						+ (s[i-1][j-1][k-1][l] + s[i-1][j-1][k][l-1] + s[i-1][j][k-1][l-1] + s[i][j-1][k-1][l-1])
						- s[i-1][j-1][k-1][l-1] + w[i][j][k][l];
	int ans1=0, ans2=0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= n; k ++)
				for(int l = 1; l <= n; l ++)
					for(int a = 1; a <= min(i, min(j, min(k, l))); a ++)
					{
						int tmp = s[i][j][k][l] - (s[i-a][j][k][l] + s[i][j-a][k][l] + s[i][j][k-a][l] + s[i][j][k][l-a])
						+ (s[i-a][j-a][k][l] + s[i-a][j][k-a][l] + s[i-a][j][k][l-a] + s[i][j-a][k-a][l] + s[i][j-a][k][l-a] + s[i][j][k-a][l-a])
						- (s[i-a][j-a][k-a][l] + s[i-a][j-a][k][l-a] + s[i-a][j][k-a][l-a] + s[i][j-a][k-a][l-a])
						+ s[i-a][j-a][k-a][l-a];
						ans1 = max(ans1, tmp);
						ans2 = max(ans2, -tmp);
					}
	printf("%d\n%d\n", ans1, ans2);
}
