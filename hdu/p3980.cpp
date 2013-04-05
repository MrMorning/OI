#include <cstdio>
#include <cstring>

int memo[1111];
bool done[1111]; 
bool vis[1111][2222];
int n,m;
int dp(int x){
	if(x < m)
		return 0;
	if(done[x])
		return memo[x];
	done[x] = true;
	for(int k = 0; k <= x - m; k ++)
		vis[x][dp(k) ^ dp(x - k - m)] = true;
	for(int k = 0; ; k ++)
		if(!vis[x][k]){
			memo[x] = k;
			break;
		}
	return memo[x];
}

int main(){
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for(int t = 1; t <= TST; t ++){
		printf("Case #%d: ", t);
		scanf("%d%d", &n, &m);
		if(n < m){
			printf("abcdxyzk\n");
			continue;
		}
		n -= m;
		memset(done, 0, sizeof(done));
		memset(vis, 0, sizeof(vis));
		if(dp(n) == 0)
			printf("aekdycoin\n");
		else
			printf("abcdxyzk\n");
	}
}
