#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int BUFFER_LEN = 1024 * 1024 * 5;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
	ptr ++; \
	if (ptr == buf_end) \
	{ \
		ptr = buffer; \
		buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
	} \
}
#define READ_INT(_x_) \
{ \
	while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
	PTR_NEXT(); \
	bool _nega_ = false; \
	if (*ptr == '-') \
	{ \
		_nega_ = true; \
		PTR_NEXT(); \
	} \
	int register _n_ = 0; \
	while (*ptr >= '0' && *ptr <= '9') \
	{ \
		_n_ = _n_ * 10 + *ptr - '0'; \
		PTR_NEXT(); \
	} \
	if (_nega_) \
	_n_ = - _n_; \
	(_x_) = (_n_); \
}

namespace tree
{
	const int N_ELE_MAX = 500010;
	const int N_DEPTH_MAX = 30;
	struct Node
	{
		int l, r, mid, depth;
	};

	struct greater_cmp
	{
		bool operator() (const int &a, const int &b)
		{
			return a > b;
		}
	};

	Node node[N_ELE_MAX * 4];

	int sorted[N_ELE_MAX];
	int val[N_DEPTH_MAX][N_ELE_MAX];
	int to_left[N_DEPTH_MAX][N_ELE_MAX];
	int sum[N_DEPTH_MAX][N_ELE_MAX];
	int ans;

	void build(int i, int l, int r, int depth)
	{
		node[i].l = l, node[i].r = r, node[i].mid = (l + r) / 2, node[i].depth = depth;
		if(l == r)
			return;
		int mid = node[i].mid;
		int lsame = mid - l + 1, same = 0;
		for(int k = l; k <= r; k ++)
			if(val[depth][k] < sorted[mid])
				lsame --;
		int lpos = l, rpos = mid + 1;
		for(int k = l; k <= r; k ++)
		{
			to_left[depth][k] = k == l ? 0 : to_left[depth][k - 1];
			sum[depth][k] = k == l ? 0 : sum[depth][k - 1];
			if(val[depth][k] < sorted[mid])
			{
				val[depth + 1][lpos ++] = val[depth][k];
				to_left[depth][k] ++, sum[depth][k] += val[depth][k];
			}
			else if(val[depth][k] > sorted[mid])
			{
				val[depth + 1][rpos ++] = val[depth][k];
			}
			else
			{
				if(same < lsame)
				{
					val[depth + 1][lpos ++] = val[depth][k];
					to_left[depth][k] ++, sum[depth][k] += val[depth][k];
					same ++;
				}
				else
					val[depth + 1][rpos ++] = val[depth][k];
			}
		}
		build(i * 2, l, mid, depth + 1);
		build(i * 2 + 1, mid + 1, r, depth + 1);
	}

	void query(int i, int l, int r, int k)
	{
		if(l == r)
		{
			ans += val[node[i].depth][l];
			return;
		}
		int l1, l2, lsum;
		int depth = node[i].depth;
		if(node[i].l == l)
			l1 = to_left[depth][r], l2 = 0, lsum = sum[depth][r];
		else
			l1 = to_left[depth][r] - to_left[depth][l - 1], l2 = to_left[depth][l - 1], lsum = sum[depth][r] - sum[depth][l - 1];
		if(k <= l1)
		{
			int newl = l2 + node[i].l,
				newr = newl + l1 - 1;
			query(i * 2, newl, newr, k);
		}
		else
		{
			ans += lsum;
			int r2 = l - 1 - node[i].l + 1 - l2,
				r1 = r - l + 1 - l1;
			int newl = node[i].mid + r2 + 1,
				newr = newl + r1 - 1;
			query(i * 2 + 1, newl, newr, k - l1);
		}
	}

	int ask(int l, int r, int k)
	{
		ans = 0;
		query(1, l, r, k);
		return ans;
	}
	void main(int n, int m)
	{
		static int sum[N_ELE_MAX];
		for(int i = 0; i < n; i ++)
		{
			READ_INT(val[0][i]);
			sorted[i] = val[0][i];
			sum[i] = (i == 0 ? 0 : sum[i - 1]) + tree::val[0][i];
		}
		sort(sorted, sorted + n);
		build(1, 0, n - 1, 0);
		while(m --)
		{
			int x1, y1, x2, y2, h;
			READ_INT(x1); READ_INT(y1); READ_INT(x2); READ_INT(y2); READ_INT(h);
			y1 --, y2 --;
			int tot_sum = y1 == 0 ? sum[y2] : sum[y2] - sum[y1 - 1];
			if(tot_sum < h)
			{
				printf("Poor QLW\n");
				continue;
			}
			int tot_len = y2 - y1 + 1;
			int l = -1, r = y2 - y1 + 1, mid = (l + r) / 2;
			while(l + 1 < r)
			{
				if(tot_sum - tree::ask(y1, y2, tot_len - mid) < h)
					l = mid;
				else
					r = mid;
				mid = (l + r) / 2;
			}
			printf("%d\n", r);
		}
	}

}

namespace dp
{
	const int N_WIDTH_MAX = 201;
	const int N_VAL_MAX = 1001;
	int f[N_VAL_MAX][N_WIDTH_MAX][N_WIDTH_MAX];
	int g[N_VAL_MAX][N_WIDTH_MAX][N_WIDTH_MAX];
	int val[N_WIDTH_MAX][N_WIDTH_MAX];

	inline int calc_f(int k, int x1, int y1, int x2, int y2)
	{
		return f[k][x2][y2] - f[k][x1 - 1][y2] - f[k][x2][y1 - 1] + f[k][x1 - 1][y1 - 1];
	}

	inline int calc_g(int k, int x1, int y1, int x2, int y2)
	{
		return g[k][x2][y2] - g[k][x1 - 1][y2] - g[k][x2][y1 - 1] + g[k][x1 - 1][y1 - 1];
	}

	void init(int r, int c)
	{
		for(int i = 0; i < r; i ++)
			for(int j = 0; j < c; j ++)
				READ_INT(val[i][j]);
		for(int k = 0; k < N_VAL_MAX; k ++)
			for(int i = 0; i < r; i ++)
			{
				static int sum[N_WIDTH_MAX], cnt[N_WIDTH_MAX];
				sum[0] = cnt[0] = 0;
				if(val[i][0] >= k)
					sum[0] += val[i][0], cnt[0] ++;
				for(int j = 1; j < c; j ++)
					if(val[i][j] >= k)
						sum[j] = sum[j - 1] + val[i][j], cnt[j] = cnt[j - 1] + 1;
					else
						sum[j] = sum[j - 1], cnt[j] = cnt[j - 1];
				if(i == 0)
				{
					memcpy(f[k][i], sum, sizeof(sum));
					memcpy(g[k][i], cnt, sizeof(cnt));
				}
				else
					for(int j = 0; j < c; j ++)
					{
						f[k][i][j] = f[k][i - 1][j] + sum[j];
						g[k][i][j] = g[k][i - 1][j] + cnt[j];
					}
			}
	}

	int ask(int x1, int y1, int x2, int y2, int h)
	{
		int l = 1, r = N_VAL_MAX, mid = (l + r) / 2;
		while(l < r - 1)
		{
			if(calc_f(mid, x1, y1, x2, y2) < h)
				r = mid;
			else
				l = mid;
			mid = (l + r) / 2;
		}
		int now = l;
		if(calc_f(now, x1, y1, x2, y2) < h)
			return -1;
		if(now == 1000)
			return (h - 1) / now + 1;
		else
		{
			int ret = calc_g(now + 1, x1, y1, x2, y2) + (h - calc_f(now + 1, x1, y1, x2, y2) - 1) / now + 1; 
			return ret;
		}
	}

	void main(int r, int c, int m)
	{
		init(r, c);
		while(m --)
		{
			int x1, y1, x2, y2, h;
			READ_INT(x1); READ_INT(y1); READ_INT(x2); READ_INT(y2); READ_INT(h);
			x1 --, y1 --, x2 --, y2 --;
			int tmp = ask(x1, y1, x2, y2, h);
			if(tmp == -1)
				printf("Poor QLW\n");
			else
				printf("%d\n", tmp);
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int r, c, m;
	scanf("%d%d%d", &r, &c, &m);
	if(r == 1)
		tree::main(c, m);
	else
		dp::main(r, c, m);
}
