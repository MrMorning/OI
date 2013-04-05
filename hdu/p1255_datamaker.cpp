#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline double randVal()
{
	return (rand()+0.0)/10000;
}
int n, testNum, seed;
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
			double x1 = randVal();
			double x2 = randVal();
			if(x1 > x2) swap(x1, x2);
			double y1 = randVal();
			double y2 = randVal();
			if(y1 > y2) swap(y1, y2);
			printf("%.3f %.3f %.3f %.3f\n", x1, y1, x2, y2);
		}
	}
}
