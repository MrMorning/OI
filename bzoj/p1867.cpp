#include <cstdio>
typedef long long bignum_t;
const int N_MAX = 61;
bignum_t gcd(bignum_t a, bignum_t b)
{
	return b == 0 ? a : gcd(b, a % b);
}
struct Fraction
{
	bignum_t up, down;
	Fraction(bignum_t _a = 0, bignum_t _b = 1): up(_a), down(_b)
	{
		bignum_t tmp = gcd(up, down);
		up /= tmp, down /= tmp;
	}
	void print()
	{
		bignum_t c = gcd(up, down);
		printf("%lld/%lld\n", up / c, down / c);
	}
};

Fraction operator+ (const Fraction &a, const Fraction &b)
{
	bignum_t LCM = a.down * (b.down / gcd(a.down, b.down));
	return Fraction(a.up * (LCM / a.down) + b.up * (LCM / b.down), LCM);
}

Fraction operator/ (const Fraction &a, int k)
{
	return Fraction(a.up, a.down * k);
}

char nextchar()
{
	char ch = getchar();
	while(ch != '.' && ch != '*')
		ch = getchar();
	return ch;
}

Fraction f[N_MAX][N_MAX];
int n, m;
bool map[N_MAX][N_MAX];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
		{
			map[i][j] = nextchar() == '*';
		}
	f[1][1] = Fraction(1, 1);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= i; j ++)
		{
			if(map[i][j])
			{
				f[i + 1][j] = f[i + 1][j] + (f[i][j] / 2);
				f[i + 1][j + 1] = f[i + 1][j + 1] + (f[i][j] / 2);
			}
			else
				f[i + 2][j + 1] = f[i + 2][j + 1] + f[i][j];
		}
	f[n + 1][m + 1].print();
}
