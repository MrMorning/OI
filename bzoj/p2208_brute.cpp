#include <cstdio>
#include <cstring>
typedef long long ll;
const int N_MAX = 2000;
bool vis[N_MAX];
bool e[N_MAX][N_MAX];
int N;
char str[N_MAX + 5];

void dfs(int x){
	vis[x] = true;
	for(int y = 0; y < N; y ++)
		if(e[x][y] && !vis[y])
			dfs(y);
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 0; i < N; i ++){
		scanf("%s", str);
		for(int j = 0; j < N; j ++)
			e[i][j] = str[j] - '0';
	}
	int res = 0;
	for(int i = 0; i < N; i ++){
		memset(vis, 0, sizeof(vis));
		dfs(i);
		for(int j = 0; j < N; j ++)
			if(vis[j])
				res ++;
	}
	printf("%d\n", res);
}
