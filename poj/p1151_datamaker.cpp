#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int testNum, n, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d",&testNum,&n,&seed);
	srand(seed);
	while(testNum --)
	{
		printf("%d\n", n);
		for(int i = 1; i <= n; i ++)
		{
			double x1 = rand() % 100000000 / 1000000.0 - rand()%100000;
			double y1 = rand() % 100000000 / 1000000.0 - rand()%100000;
			double x2 = rand() % 100000000 / 1000000.0 - rand()%100000;
			double y2 = rand() % 100000000 / 1000000.0 - rand()%100000;
			if(x1 > x2)
				swap(x1, x2);
			if(y1 > y2)
				swap(y1, y2);
			printf("%.3f %.3f %.3f %.3f\n", x1, y1, x2, y2);
		}
	}
	printf("0\n");
}
