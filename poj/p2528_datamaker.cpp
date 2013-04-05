#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, seed, testNum;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	printf("%d\n", testNum);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
		{
			int l = rand() % n +1;
			int r = rand() % n +1;
			if(l > r)
				swap(l ,r);
			printf("%d %d\n", l, r);
		}
	}
}
