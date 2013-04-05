#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int RANGE = 1000;
int n, m, seed;

int randval()
{
	return rand() % (2 * RANGE) - RANGE;
}

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 0; i < n; i ++)
		printf("%d ", randval());
	printf("\n%d\n", m);
	for(int i = 0; i < m; i ++)
	{
		int t = rand() % 4;
		int x = rand() % n, y = rand() % n;
		if(x > y)
			swap(x, y);
		x ++, y ++;
		if(t == 0 || t == 1)
			printf("Q %d %d\n", x, y);
		else if(t == 1)
			printf("A %d %d\n", x, y);
		else if(t == 2)
			printf("P %d %d %d\n", x, y, randval());
		else
			printf("C %d %d %d\n", x, y, randval());
	}
}
