#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N_ELE_MAX = 500010;
int sorted[N_ELE_MAX];

namespace tree
{
	const int N_DEPTH_MAX = 30;
	struct Node
	{
		int l, r, mid, depth;
	};
	Node node[N_ELE_MAX * N_DEPTH_MAX];

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
}

struct greater_cmp
{
	bool operator() (const int &a, const int &b)
	{
		return a > b;
	}
};

void solve_with_tree(int n, int m)
{
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &tree::val[0][i]);
		sorted[i] = tree::val[0][i];
	}
	sort(sorted, sorted + n, greater_cmp());
	tree::build(1, 0, n - 1, 0);
	printf("%d\n", tree::ask(0, 2, 2));
	return;
	while(m --)
	{
		int x1, y1, x2, y2, h;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
		y1 --, y2 --;
		int l = -1, r = y2 - y1 + 1, mid = (l + r) >> 1;
		while(l + 1 < r)
		{
			if(tree::ask(y1, y2, mid) < h)
				l = mid;
			else
				r = mid;
			mid = (l + r) / 2;
		}
		printf("%d\n", r);
	}
}

void solve_with_dp(int r, int c, int m)
{
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int r, c, m;
	scanf("%d%d%d", &r, &c, &m);
	if(r == 1)
		solve_with_tree(c, m);
	else
		solve_with_dp(r, c, m);
}
