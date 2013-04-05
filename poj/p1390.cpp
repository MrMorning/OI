#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define SQR(x) ((x)*(x))

const int N_MAX = 210;
const int INFINITY = 0x3f3f3f3f;

struct Block
{
	int c, cnt, pre;
	Block(int _c = -1, int _cnt = -1):
		c(_c), cnt(_cnt){}
} blk[N_MAX];

int f[N_MAX][N_MAX][N_MAX];
bool done[N_MAX][N_MAX][N_MAX];
int hash[N_MAX];
int n, n_blk, a[N_MAX];

void init()
{
	n = 0, n_blk = 0;
	memset(blk, -1, sizeof(blk));
	memset(hash, -1, sizeof(hash));
	memset(done, 0, sizeof(done));
}

void read_data()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
}

void pre_work()
{
	for(int i = 0; i < n; i ++)
	{
		int j = i;
		while(i + 1 < n && a[i + 1] == a[i])
			i ++;
		blk[n_blk ++] = Block(a[i], i - j + 1);
	}
	
	for(int i = 0; i < n; i ++)
	{
		blk[i].pre = hash[blk[i].c];
		hash[blk[i].c] = i;
	}
}

int dp(int i, int j, int k)
{
	assert(i <= j);
	if(done[i][j][k])
		return f[i][j][k];
	done[i][j][k] = true;
	int &ret = f[i][j][k] = -INFINITY;
	if(i == j)
		ret = SQR(k + blk[j].cnt);
	else
	{
		ret = max(ret, dp(i, j - 1, 0) + SQR(k + blk[j].cnt));
		for(int p = blk[j].pre; p >= i; p = blk[p].pre)
			ret = max(ret, dp(i, p, k + blk[j].cnt) + dp(p + 1, j - 1, 0));
	}
	return ret;
}

void solve(int i)
{
	printf("Case %d: %d\n", i, dp(0, n_blk - 1, 0));
}

int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	for(int i = 1; i <= _; i ++)
	{
		init();
		read_data();
		pre_work();
		solve(i);
	}
}
