#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int N, M, J, p[22];
int f[22][11];
int main(){
	scanf("%d%d%d", &N, &M, &J);
	for(int i = 1; i <= J; i ++)
		scanf("%d", &p[i]);
	memset(f, 0x3f, sizeof(f));
	f[0][1] = 0;
	for(int i = 1; i <= J; i ++)
		for(int j = 1; j + M - 1 <= N; j ++)
			if(j <= p[i] && p[i] <= j + M - 1){
				for(int k = 1; k + M - 1 <= N; k ++)
					if(f[i - 1][k] != INF)
						f[i][j] = min(f[i][j], f[i - 1][k] + abs(k - j));
			}
	int ans = INF;
	for(int i = 1; i + M - 1 <= N; i ++)
		ans = min(ans, f[J][i]);
	printf("%d\n", ans);
}
