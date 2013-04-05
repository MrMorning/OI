#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
typedef int bignum_t;
#define BIGNUM_T_FMT "%d"

const int N_MAX = 50010;
const int MOD_NUM = 10007;

int n, m;
bignum_t f[N_MAX], sum[N_MAX];
int len_sum[N_MAX], len[N_MAX], low[N_MAX];
int len_max, len_min;
void read_data()
{
	scanf("%d%d", &n, &m);
	m ++;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d", &len[i]);
		len_sum[i] = len_sum[i - 1] + len[i];
		len_min = std::max(len_min, len[i]);
	}
	len_sum[n + 1] = len_sum[n];
}
bool check(int upper_len)
{
	int tmp = m, i, j;
	for(i = 1; i <= n; i = j, tmp --)
		for(j = i; j <= n && len_sum[j] - len_sum[i - 1] <= upper_len; j ++);
	return tmp >= 0;
}
void work_len_max()
{
	int l = len_min - 1, r = len_sum[n], mid = (l + r) / 2;
	while(l + 1 < r)
	{
		if(check(mid))
			r = mid;
		else
			l = mid;
		mid = (l + r) / 2;
	}
	len_max = r;
}
void init_lower_bound()
{
	for(int i = 1; i <= n; i ++)
	{
		int l = 0, r = i, mid = (l + r) / 2;
		while(l + 1 < r)
		{
			if(len_sum[i] - (mid == 0 ? 0 : len_sum[mid - 1]) <= len_max)
				r = mid;
			else
				l = mid;
			mid = (l + r) / 2;
		}
		low[i] = r;
	}
}
void work_dp()
{
	for(int i = 0; i <= n; i ++)
		sum[i] = 1;
	for(int i = 1; i <= m; i ++)
	{
		for(int j = 1; j <= n; j ++)
			f[j] = sum[j - 1] - ((low[j] <= 1) ? 0 : sum[low[j] - 2]);
		for(int j = 1; j <= n; j ++)
		{
			sum[j] = f[j] + sum[j - 1];
			while(sum[j] >= MOD_NUM)
				sum[j] -= MOD_NUM;
			while(sum[j] < 0)
				sum[j] += MOD_NUM;
		}
	}
	printf("%d " BIGNUM_T_FMT "\n", len_max, (f[n] + MOD_NUM) % MOD_NUM);
}
int main()
{
	freopen("t.in", "r", stdin);
	read_data();
	work_len_max();
	init_lower_bound();
	work_dp();
}
