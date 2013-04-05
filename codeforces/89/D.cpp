#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
ll f[105][105][15][15];
int n1, n2, m1, m2;

inline void plus(ll &a, ll b)
{
	a = (a + b) % 100000000;
}

int main()
{
	//freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &n1, &n2, &m1, &m2);
	f[0][0][0][0] = 1;
	for(int i = 0; i <= n1; i ++)
		for(int j = 0; j <= n2; j ++)
		{
			for(int k = 0; k <= m1; k ++)
			{
				if(k != m1)
					plus(f[i + 1][j][k + 1][0], f[i][j][k][0]);
				plus(f[i][j + 1][1][1], f[i][j][k][0]);
			}

			for(int k = 0; k <= m2; k ++)
			{
				if(k != m2)
					plus(f[i][j + 1][k + 1][1], f[i][j][k][1]);
				plus(f[i + 1][j][1][0], f[i][j][k][1]);
			}
		}
	ll res = 0;
	for(int k = 0; k <= m1; k ++)
		plus(res, f[n1][n2][k][0]);
	for(int k = 0; k <= m2; k ++)
		plus(res, f[n1][n2][k][1]);
	printf("%d\n", (int)res);
}
