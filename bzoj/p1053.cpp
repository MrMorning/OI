#include <cstdio>

typedef long long bignum_t;

const int N_PRIME = 10;
const int prime[N_PRIME] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

bignum_t cur_x = 2000000000;
int cur_cnt = 0;
int upperlim;

void dfs(bignum_t x, int cnt, int begin)
{
	if(x > upperlim)
		return;
	if(cnt >= cur_cnt)
	{
		if(cnt > cur_cnt || (cnt == cur_cnt && x < cur_x))
		{
			cur_x = x;
			cur_cnt = cnt;
		}
	}
	bignum_t acc;
	for(int i = begin; i < N_PRIME; i ++)
	{
		acc = 1;
		for(int j = 1; ; j ++)
		{
			acc *= prime[i];
			if(acc * x > upperlim)
				break;
			dfs(acc * x, cnt * (j + 1), i + 1);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d", &upperlim);
	dfs(1, 1, 0);
	printf("%d\n", (int) cur_x);
}
