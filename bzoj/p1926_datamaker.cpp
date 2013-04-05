#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int randVal()
{
	return rand() % 1000 + 1;
}

int main()
{
	freopen("t.in", "w", stdout);
	int r, c, m, seed;
	scanf("%d%d%d%d", &r, &c, &m, &seed);
	srand(seed);
	printf("%d %d %d\n", r, c, m);
	for(int i = 1; i <= r; i ++)
	{
		for(int j = 1; j <= c; j ++)
			printf("%d ", randVal());
		printf("\n");
	}

	while(m --)
	{
		int x1 = rand() % r,
			x2 = rand() % r,
			y1 = rand() % c,
			y2 = rand() % c;
		if(x1 > x2)
			swap(x1, x2);
		if(y1 > y2)
			swap(y1, y2);
		printf("%d %d %d %d %d\n", x1 + 1, y1 + 1, x2 + 1, y2 + 1, rand() % 2000000000);
	}
}
