#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 0x3f3f3f3f;

int w[400][400], match[400];
int lx[400], ly[400];
bool visX[400], visY[400];
int n, d;
int a[400], ans[400];

bool find(int u)
{
	visX[u] = true;
	for(int v = 0; v < n; v ++)
		if(!visY[v])
		{
			int t = lx[u] + ly[v] - w[u][v];
			if(t == 0)
			{
				visY[v] = true;
				if(match[v] == -1 || find(match[v]))
				{
					match[v] = u;
					return true;
				}
			}
			else
				d = min(d, t);
		}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &a[i]);
		a[i] = a[i] * a[i];
	}

	for(int i = 0; i < n; i ++)
	{
		int k;
		scanf("%d", &k);
		while(k --)
		{
			int t;
			scanf("%d", &t);
			t = t - 1;
			w[i][t] = a[i];
		}
	}

	memset(match, -1, sizeof(match));	
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(w[i][j] > lx[i])
				lx[i] = w[i][j];
	for(int i = 0; i < n; i ++)
	{
		while(1)
		{
			memset(visX, 0, sizeof(visX));
			memset(visY, 0, sizeof(visY));
			d = oo;
			if(find(i))
				break;
			for(int j = 0; j < n; j ++)
			{
				if(visX[j])
					lx[j] -= d;
				if(visY[j])
					ly[j] += d;
			}
		}
	}

	memset(ans, -1, sizeof(ans));
	for(int i = 0; i < n; i ++)
		ans[match[i]] = i;
	for(int i = 0; i < n; i ++)
		if(w[i][ans[i]])
			printf("%d ", ans[i] + 1);
		else
			printf("0 ");
}
