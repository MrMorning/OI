#include <cstdio>
#include <cstdlib>
void swap(int &a, int &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}
int seed;
int n;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	int a = rand() % n + 1, b = rand() % n + 1;
	if(a > b)
		swap(a, b);
	//printf("%d %d\n", a, b);
	printf("1 1");
	for(int i = 1; i <= 100; i ++)
		printf("0");
	printf("\n");
	int l = rand() % 100 + 1, r = rand() % 100 + 1;
	if(l > r)
		swap(l, r);
	printf("%d %d %d\n", rand() % 10 + 1, l, r);
}
