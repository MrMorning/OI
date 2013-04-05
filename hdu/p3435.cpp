#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 1010;
const int oo = 0x3f3f3f3f;

bool visX[V_MAX], visY[V_MAX];
int lx[V_MAX], ly[V_MAX];
int match[V_MAX], slack[V_MAX];
int cost[V_MAX][V_MAX];
int nv, ne;

bool aug(int x){
	visX[x] = true;
	for(int i = 1; i <= nv; i ++)
		if(!visY[i]){
			int t = lx[x] + ly[i] - cost[x][i];
			if(t == 0){
				visY[i] = true;
				if(match[i] == -1 || aug(match[i])){
					match[i] = x;
					return true;
				}
			}
			else
				slack[i] = min(slack[i], t);
		}
	return false;
}

void solve(){
	static bool vis[V_MAX];
	memset(vis, 0, sizeof(vis));
	scanf("%d%d", &nv, &ne);
	for(int i = 1; i <= nv; i ++)
		for(int j = 1; j <= nv; j ++)
			cost[i][j] = -oo;
	for(int i = 1; i <= ne; i ++){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		vis[a] = vis[b] = true;
		cost[a][b] = cost[b][a] = max(cost[a][b], -c);
	}
	for(int i = 1; i <= nv; i ++)
		if(!vis[i]){
			printf("NO\n");
			return;
		}

	memset(match, -1, sizeof(match));
	memset(ly, 0, sizeof(ly));
	for(int i = 1; i <= nv; i ++)
		lx[i] = -oo;
	for(int i = 1; i <= nv; i ++)
		for(int j = 1; j <= nv; j ++)
			lx[i] = max(lx[i], cost[i][j]);

	for(int i = 1; i <= nv; i ++){
		for(int j = 1; j <= nv; j ++)
			slack[j] = oo;
		while(1){
			memset(visX, 0, sizeof(visX));
			memset(visY, 0, sizeof(visY));
			if(aug(i))
				break;
			int delta = oo;
			for(int j = 1; j <= nv; j ++)
				if(!visY[j])
					delta = min(delta, slack[j]);
			for(int j = 1; j <= nv; j ++){
				if(visX[j])
					lx[j] -= delta;
				if(visY[j])
					ly[j] += delta;
				else
					slack[j] -= delta;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= nv; i ++)
		ans += lx[i] + ly[i];
	printf("%d\n", -ans);
}

int main(){
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for(int i = 1; i <= TST; i ++){
		printf("Case %d: ", i);
		solve();
	}
}
