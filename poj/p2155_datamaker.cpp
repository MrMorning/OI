#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
int n,m,seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d",&n,&m,&seed);
	srand(seed);
	printf("1\n");
	printf("%d %d\n", n, m);
	while(m --)
	{
		int t = rand() %2;
		int x1 = rand() % n + 1;
		int x2 = rand() % n + 1;
		int y1 = rand() % n + 1;
		int y2 = rand() % n + 1;
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		if(t)
			printf("C %d %d %d %d\n", x1, y1, x2, y2);
		else
			printf("Q %d %d\n", x1, y1);
	}
}

