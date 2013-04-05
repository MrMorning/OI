#include <cstdio>
#include <cstdlib>
#include <ctime>
int my_rand()
{
	static int x = 1;
	x += (x << 2) + 1;
	x &= (0x7fffffff);
	return x;
}
int main()
{
	freopen("seed.txt", "w", stdout);
	for(int i = 0; i < 100000; i ++)
		printf("%d\n", my_rand());
}
