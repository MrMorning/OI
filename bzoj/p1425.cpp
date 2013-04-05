#include <cstdio>
#include <cstring>
#include <cassert>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef long long bignum_t;
const int N_MAX = 100001;
const int N_WIDTH_MAX = 11;
const int N_DEPTH_MAX = 19;
const int MOD_NUM = 1000000001;
namespace pre_work
{
	bool hash[N_MAX + 1];
	int ans[N_MAX + 1];
	int f[N_DEPTH_MAX][1 << N_WIDTH_MAX];
	int table_cnt[N_DEPTH_MAX];
	int table[N_DEPTH_MAX][N_WIDTH_MAX];
	void dfs(int x, int depth, int flag);
	void dp(int n);
	void expand(int i, int j, int pre, int w, int begin, int n);
	void update(int &x, int y);
	void main();
}
void pre_work::update(int &x, int y)
{
	x = (bignum_t)(x + y) % MOD_NUM;
}
void pre_work::dfs(int x, int depth, int flag)
{
	assert(x != 0);
	if(x > N_MAX)
		return;
	table[depth][table_cnt[depth] ++] = x;
	assert(hash[x] == false);
	hash[x] = true;
	if(! flag)
		dfs(x * 2, depth + 1, 0);
	dfs(x * 3, depth + 1, 1);
}

void pre_work::expand(int i, int j, int pre, int w, int begin, int n)
{
	update(f[i + 1][j], w);
	for(int t = begin; t < table_cnt[i + 1] && table[i + 1][t] <= n; t ++)
#define GET(x, i) ((x) & (1 << i))
		if(GET(pre, t) == 0 && (t == 0 || GET(pre, t - 1) == 0))
			expand(i, j | 1 << t, pre, w, t + 1, n);
}

void pre_work::dp(int n)
{
	memset(f, 0, sizeof(f));
	int upperlim = 1 << N_WIDTH_MAX;
	f[0][0] = 1;
	for(int i = 0; i < N_DEPTH_MAX; i ++)
		for(int j = 0; j < upperlim; j ++)
			if(f[i][j])
				expand(i, 0, j, f[i][j], 0, n);
	ans[n] = f[N_DEPTH_MAX - 1][0];
}

void pre_work::main()
{
	dfs(1, 1, 0);
	for(int i = 1; i <= N_MAX; i ++)
		if(hash[i])
			dp(i);
		else
			ans[i] = ans[i - 1];
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	pre_work::main();
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		int n;
		scanf("%d", &n);
		int ans = 1;
		for(int i = 1; i <= n; i ++)
			if(i % 2 != 0 && i % 3 != 0)
				ans = (bignum_t)ans * pre_work::ans[n / i] % MOD_NUM;
		printf("%d\n", ans);
	}
}
