#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n, colornum, m ,seed;

int main()
{
	freopen("t.in","w",stdout);
	scanf("%d%d%d%d", &n, &colornum, &m, &seed);
	printf("%d %d %d\n", n, colornum, m);
	srand(seed);
	for(int i = 1; i <= m; i ++)
	{
		int l = rand()%n+1;
		int r = rand()%n+1;
	//	if(l > r) swap(l ,r);
		int ctrl = rand()%2;
		if(ctrl == 0)
			printf("C %d %d %d\n", l, r, rand()%colornum+ 1);
		else
			printf("P %d %d\n", l, r);
	}
}
