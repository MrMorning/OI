# include <cstdio>
# include <cmath>
# include <cstring>

using namespace std;

typedef long long int64;

struct jew{int a,b,w;}res[200];
int64 f[35][3000], ans;
int lim, n, m;
int top, next[200], linke[200], point[200];

void link(int x, int y)
{
	++top; next[top] = linke[x]; linke[x] = top; point[top] = y;
}
void origin()
{
	top = 0;
	memset(f,0,sizeof(f));
	memset(linke, 0, sizeof(linke));
	memset(next, 0, sizeof(next));
	memset(point, 0, sizeof(point));	
}
inline int min(int x, int y){return x<y?x:y;};
inline int64 max(int64 x, int64 y){return x>y?x:y;};

int main()
{
	int ht, i, j, k, ke;
	freopen("t.in", "r", stdin);
	for (;;)
	{
		scanf("%d%d", &n, &m);
		if (n==-1) break;
		ans = 0;
		origin();
		for (i = 1; i <= n; i++)
		{
			res[i].a=res[i].b=0;
			scanf("%d%d", &ht ,&res[i].w);
			for (;(ht&1)==0;ht>>=1) res[i].b++;
			res[i].a = ht;
			link(res[i].b, i);
		}
		for (i = 30; i >= 0; i--)
		{
			for (j = 0; j <= lim; j++) f[i][j*2+((m>>i)&1)] = f[i+1][j];
			for (j = lim*2; j >= 0; j--) f[i][j] = max(f[i][j], f[i][j+1]);
			lim = min(1000, m>>i);  
			for (ke = linke[i]; ke; ke=next[ke])
			{
			  k = point[ke];
			  for (j = 0; j + res[k].a <= lim; j++)
			  {
			     f[i][j] = max(f[i][j], f[i][j+res[k].a] + res[k].w);
			     ans = max(ans, f[i][j]);
			  }
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

