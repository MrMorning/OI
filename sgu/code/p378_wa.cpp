#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <complex>
#include <iostream>
#include <algorithm>
using namespace std;

#define pb push_back 
#define mp make_pair 
typedef pair< int, pair<int,int> > PII;

const int maxn = 600;

int n, m;
int S, L;
int flow[maxn][maxn], boat[maxn][maxn], reach[maxn][maxn];
int dir[5][2]={0,0, -1,0, 1,0, 0, 1, 0,-1};

void update(double & res, double x)
{
	if(res > x)res = x;
}
void show()
{
	cout<<"peter's least time"<<endl;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			cout<<reach[i][j]<<"\t";
		}
		cout<<endl;
	}
	
	cout<<"boat's least time"<<endl;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			cout<<boat[i][j]<<"\t";
		}
		cout<<endl;
	}
}
void get_peter(int x, int y)
{
	priority_queue < PII > que;
	
	reach[x][y] = 0;
	que.push( mp(-reach[x][y], mp( x, y) ) );
	//show();
	while(!que.empty())
	{
		PII node = que.top();
		que.pop();
		
		int x = node.second.first;
		int y = node.second.second;
		if(x==0 || y==0 || x==n-1 || y == m-1)continue;
		
		for(int i = 4; i >= 0; i--)
		{
			int now = flow[x][y];
			int nx = dir[now][0] + dir[i][0] + x;
			int ny = dir[now][1] + dir[i][1] + y;
			int val;
			
			if(nx == x + 2 || nx == x - 2)
			{
				nx = ( x + nx ) / 2;
				val = 2;
			}
			else
			if(ny == y + 2 || ny == y - 2)
			{
				ny = ( y + ny ) / 2;
				val = 2;
			}
			else
				val = 4;

			if(nx==0 || ny==0 || nx==n-1 || ny==m-1)val /= 2;
			
			//cout<<x<<" "<<y<<" "<<nx<<" "<<ny<<" "<<val<<endl;
			if(reach[nx][ny] != -1 && reach[nx][ny] <= val + reach[x][y])continue;
			reach[nx][ny] = val + reach[x][y];
			
			que.push(mp(-reach[nx][ny], mp(nx, ny)) );
		}
	}
}

void get_boat(int x, int y)
{
	queue < pair<int,int> > que;
	
	que.push( mp(x,y) );
	boat[x][y] = 0;
	
	while(!que.empty())
	{
		pair<int,int> node = que.front();
		que.pop();
		
		int x = node.first;
		int y = node.second;
		if(x==0 || y==0 || x==n-1 || y == m-1)continue;
		
		int now = flow[x][y];
		int nx = dir[now][0] + x;
		int ny = dir[now][1] + y;
		
		if(boat[nx][ny] != -1)
		{
			S = boat[nx][ny];
			L = boat[x][y] + 1 -boat[nx][ny];
			return;
		}
		
		boat[nx][ny] = 1 + boat[x][y];
		
		que.push(mp(nx, ny));
	}
}


double handle(double ta, double tb, double va, double vb)
{
	if(ta < tb)
		return handle(tb, ta, vb, va);
	else
	{
		if( tb + 1 / vb < ta )return 1e100;

		double leave  = 1 - (ta - tb) * vb;
		
		return ta + leave / (va + vb);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d",&n, &m);
	
	memset(flow, 0, sizeof(flow));
	memset(boat, -1, sizeof(boat));
	memset(reach, -1, sizeof(reach));
	
	char buf[maxn];
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf);
		for(int j = 1; j <= m; j++)
		{
			flow[i][j] = buf[j-1] - '0';
		}
	}
		
	n += 2;
	m += 2;
	
	int x, y;
	
	
	
	scanf("%d %d",&x, &y);
	get_peter(y, x);
	
	S = -1; L = -1;
	scanf("%d %d",&x, &y);
	get_boat(y , x);
	
	//show();
	
	double res = 1e100;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		{
			if(reach[i][j] < 0)continue;
			
			if(i==0 || j==0 || i==n-1 || j==m-1)
			{
				update( res , reach[i][j] / 4.0 );
			}
			else
			{
				if(boat[i][j]==-1)continue;
				if( S==-1 || boat[i][j] < S )
				{
					if(boat[i][j] > reach[i][j] / 4.0)
						update( res , boat[i][j]);	
				}
				else
				{
					int x = max(0, (int)ceil( (reach[i][j] / 4.0 - boat[i][j]) / L ) );
					
					update( res , boat[i][j] + L * x);	
				}
			}
		}

	for(int i = 1; i < n - 1; i++)
		for(int j = 1; j < m - 1; j++)
	{
		int a = flow[i][j];
		if(a == 0)continue;
		int x  = dir[a][0] + i, y = dir[a][1] + j;
		int b = flow[x][y];
		if( !(b == 0 || dir[a][0] == -dir[b][0] && dir[a][1] == -dir[b][1]) )continue;
		double bt = boat[i][j];
		double pt = reach[x][y] / 4.0;
		
		if(bt < -0.5 || pt < -0.05)continue;

		double va = 1;
		double vb = ( b==0 ? 1 : 2);
		
		if(S==-1 || bt < S)
			update(res, handle(bt, pt, va, vb) );
		else
		{
			int cnt = max(0, (int)ceil( (pt - bt) / L ) );
			for(int k = max(0, cnt - 3); k < cnt + 3; k++)
				update(res, handle(bt + L*k, pt, va, vb) );
		}
	}

	if(res > 1e70)
		printf("SOS\n");
	else
		printf("%.2lf\n",res);
}		

