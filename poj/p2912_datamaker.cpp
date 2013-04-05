#include <cstdio>
#include <cstdlib>

int main()
{
	freopen("t.in","w",stdout);
	int n, m, seed;
	char ch;
	scanf("%d%d%d",&n,&m,&seed);
	srand(seed);
	printf("%d %d\n",n,m);
	for(int i = 1; i <= m ; i ++)
	{
		int k = rand()%3;
		switch(k)
		{
			case 0:
				ch = '<';
				break;
			case 1:
				ch = '=';
				break;
			case 2:
				ch = '>';
				break;
		}
		printf("%d%c%d\n",rand()%n,ch,rand()%n);
	}
}
