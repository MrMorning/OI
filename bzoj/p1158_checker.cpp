#include <cstdio>
#include <cassert>

int n, m;
int main()
{
	FILE *fin = fopen("t.in", "r"),
		 *fout = fopen("t.out", "r");
	int n, m;
	fscanf(fin, "%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
	{
		int a, b, c, d;
		fscanf(fin, "%d%d", &a, &b);
		fscanf(fout, "%d%d", &c, &d);
		if(!(a == c && b == d))
			printf("%d\n", i + 1);
	}
}
