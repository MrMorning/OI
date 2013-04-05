#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

// input optimization
#define BUFSIZE 200 * 200 * 5 + 200000 * (4 + 4 + 4 + 4 + 9)
char buf[BUFSIZE], *pt = buf;
#define scan(t) \
{ \
	while (!((*pt) >= '0' && (*pt) <= '9')) pt ++; \
	t = 0; \
	while (((*pt) >= '0' && (*pt) <= '9')) t = t * 10 + (*(pt ++)) - '0'; \
}

int n, m, T;
// n == 1
#define MAXN 500000
#define MAXDEPTH 20
int a[MAXN + 1];
int tree[MAXDEPTH][MAXN + 1];
int treesum[MAXDEPTH][MAXN + 1];
void MergeSort(int l, int r, int dep)
{
	if (l == r)
	{
		tree[dep][l] = a[l];
		treesum[dep][l] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	MergeSort(l, mid, dep + 1), MergeSort(mid + 1, r, dep + 1);
	int register p1 = l;
	int register p2 = mid + 1;
	// int p1 = l, p2 = mid + 1;
	int *b = tree[dep + 1], *a = tree[dep], *s = treesum[dep];
	for (int i = l; i <= r; i ++)
	{
		if (p1 <= mid && p2 <= r)
		{
			if (b[p1] >= b[p2])
				a[i] = b[p1 ++];
			else
				a[i] = b[p2 ++];
		}
		else if (p1 <= mid)
			a[i] = b[p1 ++];
		else if (p2 <= r)
			a[i] = b[p2 ++];
		s[i] = a[i];
		if (i > l)
			s[i] += s[i - 1];
	}
}
void InitMergeTree()
{
	MergeSort(1, m, 0);
}

// n, m <= 200
const int MAXNUM = 1000;
int s[201][201][MAXNUM + 1];
int b[201][201];
void Init()
{
	scanf("%d%d%d", &n, &m, &T);
	fread(buf, 1, BUFSIZE, stdin);
	if (n == 1)
	{
		for (int i = 1; i <= m; i ++)
			scan(a[i]);
		InitMergeTree();
	}
	else
	{
		int t;
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= m; j ++)
			{
				scan(t);
				s[i][j][t] ++;
				for (int register k = 1; k <= MAXNUM; k ++)
					s[i][j][k] += s[i][j - 1][k] + s[i - 1][j][k] - s[i - 1][j - 1][k];
			}
	}
}


#define Get(num, x1, y1, x2, y2) (s[x2][y2][num] - s[x1 - 1][y2][num] - s[x2][y1 - 1][num] + s[x1 - 1][y1 - 1][num])
// n == 1
int Sum, Cnt;
void Ask(int L, int R, int num, int l, int r, int dep)
{
	if (l >= L && r <= R)
	{
		int origl = l;
		int *a = tree[dep];
		if (a[l] < num)
			return;
		r ++;
		while (l + 1 < r)
		{
			int mid = (l + r) >> 1;
			if (a[mid] >= num)
				l = mid;
			else
				r = mid;
		}
		Cnt += l - origl + 1;
		Sum += treesum[dep][l];
		return;
	}
	else
	{
		int mid = (l + r) >> 1;
		if (R <= mid)
			Ask(L, R, num, l, mid, dep + 1);
		else if (L > mid)
			Ask(L, R, num, mid + 1, r, dep + 1);
		else
		{
			Ask(L, R, num, l, mid, dep + 1);
			Ask(L, R, num, mid + 1, r, dep + 1);
		}
	}
}

int Query(int x1, int y1, int x2, int y2, int sum)
{
	if (n == 1)
	{
		// first binary search the max number needed O(log(MAXNUM))
		// then calculate how many number is needed and the sum in a static merge tree in O(log(m) * log(m))
		// total time complexity is O(log(MAXNUM) * log(m) * log(m)) per query
		int l = 1, r = MAXNUM + 1;
		while (l + 1 < r)
		{
			int mid = (l + r) >> 1;
			Sum = 0, Cnt = 0;
			Ask(y1, y2, mid, 1, m, 0);
			if (Sum >= sum)
				l = mid;
			else
				r = mid;
		}
		Sum = 0, Cnt = 0;
		Ask(y1, y2, l, 1, m, 0);
		if (Sum < sum)
			return -1;
		return Cnt - (Sum - sum) / l;
	}
	else
	{
		// use a MAXNUM * n * m a(rray to record appearing time for each number
		// then chose numbers from the biggest and see if their summary is bigger than query
		int v = 0, tmp, cnt = 0;
		int register t;
		for (int register i = MAXNUM; i >= 1; i --)
		{
			t = Get(i, x1, y1, x2, y2);
			tmp = t * i + v;
			if (tmp >= sum)
				return cnt + (sum - v- 1) / i + 1;
			else
				v = tmp, cnt += t;
		}
		return -1;
	}
	return -2;
}

void Solve()
{
	int x1, y1, x2, y2, v;
	while (T --)
	{
		scan(x1); scan(y1); scan(x2); scan(y2); scan(v);
		int t = Query(x1, y1, x2, y2, v);
		if (t == -1)
			printf("Poor QLW\n");
		else
			printf("%d\n", t);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	Init();
	Solve();
	return 0;
}

