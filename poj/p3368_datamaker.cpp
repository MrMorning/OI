#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RAND() (rand() % 20 - 10)
using namespace std;
int a[100000];
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i ++)
		a[i] = RAND();
	sort(a, a + n);
	for(int i = 0; i < n; i ++)
		printf("%d ", a[i]);
	printf("\n");
	while(m --)
	{
		int a = rand() % n + 1,
			b = rand() % n + 1;
		printf("%d %d\n", MIN(a, b), MAX(a, b));
	}
	printf("0\n");
}
