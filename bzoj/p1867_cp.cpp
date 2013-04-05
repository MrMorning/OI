#include <cstdio>
#include <cassert>
typedef long long bignum_t;
const int N_MAX = 61;
bignum_t gcd(bignum_t a, bignum_t b)
{
	return b == 0 ? a : gcd(b, a % b);
}

char nextchar()
{
	char ch = getchar();
	while(ch != '.' && ch != '*')
		ch = getchar();
	return ch;
}

bignum_t f[N_MAX][N_MAX];
int n, m;
bool map[N_MAX][N_MAX];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
			map[i][j] = nextchar() == '*';
	f[1][1] = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
		{
			if(map[i][j])
			{
				f[i + 1][j] += f[i][j] / 2;
				f[i + 1][j + 1] += f[i][j] / 2;
			}
			else
				f[i + 2][j + 1] += f[i][j];
		}
}
