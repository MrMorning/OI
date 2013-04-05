#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define MAXN 300000
#define TIMES MAXN

using namespace std;

int n, a[MAXN], seed;
int tree[MAXN];
int testNum;

inline int lowbit(int i)
{return i & (- i);}

void Add(int i, int val)
{
	while(i <= MAXN)
	{
		tree[i] += val;
		i += lowbit(i);
	}
}

int Sum(int i)
{
	int cnt = 0;
	while(i > 0)
	{
		cnt += tree[i];
		i -= lowbit(i);
	}
	return cnt;
}

int main()
{
	FILE *flog = fopen("t.log", "w");
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	printf("%d\n", testNum);
	while(testNum --)
	{
		memset(tree, 0, sizeof(tree));
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
			a[i] = i;
		for(int i = 1; i <= TIMES; i ++)
		{
			int j = rand() % n + 1;
			int k = rand() % n + 1;
			swap(a[j], a[k]);
		}
		for(int i = 1; i <= n; i ++)
			fprintf(flog, "%d ", a[i]);
		fprintf(flog, "\n");
		for(int i = 1; i <= n; i ++)
		{
			Add(a[i], 1);
			printf("%d ", i - Sum(a[i]));
		}
		printf("\n");
	}
}
