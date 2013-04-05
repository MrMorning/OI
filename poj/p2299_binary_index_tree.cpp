#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#define MAXN 500010
using std::map;
using std::cout;

int A[MAXN], B[MAXN], C[MAXN];

inline int lowbit(int x)
{return x & (-x);}

int comp(const void *a, const void *b)
{return *(int*)a - *(int*)b;}

int Sum(int i)
{
	int cnt = 0;
	while(i > 0)
	{
		cnt += C[i];
		i -= lowbit(i);
	}
	return cnt;
}

void Add(int i, int x)
{
	while(i <= MAXN)
	{
		C[i] += x;
		i += lowbit(i);
	}
}


int main()
{
	freopen("t.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	while(1)
	{
		int n;
		long long ans = 0;
		memset(C, 0 ,sizeof(C));
		scanf("%d\n", &n);
		if(n == 0) break;
		int index_cnt = 0;
		map<int, int> index;
		for(int i = 1; i <= n; i ++)
		{
			scanf("%d\n", &A[i]);
			B[i] = A[i];
		}
		qsort(A + 1, n, sizeof(int), comp);
		for(int i = 1, x; i <= n; i ++)
		{
			x = A[i];
			if(index.find(x) == index.end())
				index[x] = ++ index_cnt;
		}
		for(int i = 1, x; i <= n; i ++)
		{
			x = index[B[i]];
			ans += i-1 - Sum(x);
			Add(x, 1);
		}
		cout << ans << '\n';
	}
}
