#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=110;
int    N, K, T;
struct  Node
{
	int  t,  p, s;
}node[maxn];
int    dp[maxn][maxn];
bool reach[maxn][maxn];
int  cmp(Node a, Node b)
{
	return a.t < b.t;
}
void  init( )
{
	for (int i=1; i<=N; i++)   scanf("%d", &node[i].t);
	for (int i=1; i<=N; i++)   scanf("%d", &node[i].p);
	for (int i=1; i<=N; i++)   scanf("%d", &node[i].s);
	sort(&node[1], &node[N+1], cmp);
}
int    solve( )
{
	int  ans=0;
	memset(dp, 0, sizeof(dp));
	memset(reach, false, sizeof(reach));
	reach[0][0] = true;
	for (int i=1; i<=N; i++)
	{
		for (int j=0; j<=K; j++) //门的状数总共有K+1种
		{
			for (int  status = 0; status<=K; status++)
			{
				//满足的条件为T(i)-T(i-1) >= abs(j-status)
				if ( node[i].t - node[i-1].t >= abs( j - status) && reach[i-1][status] == true)
				{
					if (j==node[i].s)
						dp[i][j] = max( dp[i-1][status]+node[i].p, dp[i][j] );
					else
						dp[i][j] = max(  dp[i-1][status], dp[i][j] );
					reach[i][j] = true;
					if (dp[i][j] > ans) ans=dp[i][j];
				}
			}
		}
	}
	return ans;
}

int   main( )
{
	freopen("t.in", "r", stdin);
	while (cin>>N>>K>>T)
	{
		init( );
		printf("%d\n", solve( ));
	}
	return 0;
}

