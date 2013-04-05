#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int l, r;
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i ++)
	{
		int t = rand() % 2;
		if(t == 1)
			printf("%c", '(');
		else
			printf("%c", ')');
	}
	printf("\n");
	for(int i = 0; i < m; i ++)
	{
		int t = rand() % 3;
		int l = rand() % n + 1;
		int r = rand() % n + 1;
		if(l > r)
			swap(l, r);
		printf("%d %d %d\n", t, l, r);
	}
}
