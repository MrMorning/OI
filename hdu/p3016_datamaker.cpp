#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

int testNum, n, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &testNum, &n, &seed);
	srand(seed);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
		{
			int l = rand()%99999 + 1;
			int r = rand()%99999 + 1;
			if(l > r)
				swap(l, r);
			printf("%d %d %d %d\n", rand()+1, l, r, rand()%2000-1000);
		}
	}
}
