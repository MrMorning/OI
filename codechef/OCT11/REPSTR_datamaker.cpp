#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, seed;
int l, r;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	int l = rand() % n + 1, r = rand() % n + 1;
	if(l > r)
		swap(l, r);
	printf("%d %d\n", l, r);
	for(int i = 0; i < n; i ++)
		printf("%c", rand() % 2 + 'a');
	printf("\n0 0\n");
}
