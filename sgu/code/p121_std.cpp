#include<iostream>
#include<vector>
#include<stdio.h>
#include<string.h> 
using namespace std;

const int N = 105;

int g[N][N] , vis[N][N] ,n;
vector<int>adj[N];

void dfs( int idx ,int pre ) {
	int i , j;
	pre ^= 1;
	for( i = 0; i < adj[idx].size(); i++) {
		int now = adj[idx][i];
		if( vis[idx][now] || vis[now][idx] ) continue;
		g[idx][now] = g[now][idx] = pre;
		vis[idx][now] = vis[now][idx] = 1;
		dfs( now,pre );
		pre ^= 1;
	}
}

void printAns() {
	int i , j;
	for( i = 1; i <= n;i++ ) {
		for( j = 0 ; j < adj[i].size();j++ )
			printf("%d ",g[i][adj[i][j]]+1);
		puts("0");
	}
}

int check() {
	memset(vis,0,sizeof(vis));
	int i , j;
	for( i = 1; i <= n;i++ )
		if( adj[i].size() > 1 ) {
			for( j = 0 ; j < adj[i].size();j++ )
				vis[i][ g[i][adj[i][j]] ] = 1;
			if( vis[i][0] == 0 || vis[i][1] == 0 ) return 0; 
		} 
	return 1;
}

int main() {
	freopen("t.in", "r", stdin);
	int   i , j;
	while( scanf("%d",&n) != EOF ) {
		for( i = 1; i <= n;i++ )
			adj[i].clear();
		memset(g,0,sizeof(g));
		memset(vis,0,sizeof(vis));

		for( i = 1 ; i <= n;i++ ) {
			int tmp;
			while( scanf("%d",&tmp) , tmp ) 
				adj[i].push_back(tmp); 
		}
		for( i = 1; i <= n;i++ )
			if( adj[i].size()%2 == 1 )
				dfs(i , 0);
		for( i = 1; i <= n;i++ )
			dfs(i , 0 );
		if( check() )  puts("1")/*printAns()*/;
		else puts("No solution");
	}
	return 0;
}
