#include <cstdio>
#define ABS(a) ((a)>(0)?(a):(-(a)))
const int INFINITY = 1000000;
int f[12][12], num1, num2, digit[12];

int calc(int n, int uplim, int obs, bool flag)
{
	int cnt = 0;
	for(int i = ! flag; i < uplim; i ++)
		if(ABS(i - obs) >= 2)
			cnt += f[n][i];
	return cnt;
}

int calc(int x)
{
	if(x == 0)
		return 0;
	else if(x < 10)
		return x;
	int l = 0, cnt = 0;
	while(x)
		digit[++ l] = x % 10, x /= 10;
	for(int i = 1; i < l; i ++)
		cnt += calc(i, 10, INFINITY, 0);
	digit[l + 1] = INFINITY;
	for(int i = l; i >= 1; i --)
	{
		if(i == 1)
			cnt += calc(1, digit[1] + 1, digit[2], 1);
		else if(i == l)
			cnt += calc(i, digit[i], INFINITY, 0);
		else
			cnt += calc(i, digit[i], digit[i + 1], 1);
		if(ABS(digit[i] - digit[i + 1]) <= 2)
			break;
	}
	return cnt;
}
//f[i][j] : i digits, begin with j (pre 0s available)
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 0; i <= 9; i ++)
		f[1][i] = 1;
	for(int i = 2; i <= 10; i ++)
		for(int j = 0; j <= 9; j ++)
			for(int k = 0; k <= 9; k ++)
				if(ABS(j - k) >= 2)
					f[i][j] += f[i - 1][k];
	scanf("%d%d", &num1, &num2);
	printf("%d\n", calc(num2) - calc(num1 - 1));
}
