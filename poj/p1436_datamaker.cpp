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
	printf("%d\n", testNum);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
		{
			int y1 = rand()%8000;
			int y2 = rand()%8000;
			if(y1 > y2)
				swap(y1, y2);
			printf("%d %d %d\n", y1, y2, rand()%8000);
		}
	}
}
