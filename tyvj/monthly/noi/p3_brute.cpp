#include <cstdio>
#ifdef unix
	#define VAL_T_FMT "%lld"
#else
	#define VAL_T_FMT "%I64d"
#endif
typedef long long val_t;

bool check(val_t x)
{
	if(x % 13 == 0)
	{
		while(x)
		{
			if(x % 10 == 3 && x / 10 % 10 == 1)
				return true;
			x /= 10;
		}
	}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	val_t n, ans = 0;
	scanf(VAL_T_FMT, &n);
	for(val_t x = 1; x <= n; x ++)
		if(check(x))
			ans ++;
	printf(VAL_T_FMT "\n", ans);
}
