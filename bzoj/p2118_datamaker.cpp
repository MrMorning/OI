#include <cstdio>
#include <cstdlib>
#include <algorithm>
typedef long long bignum_t;

using namespace std;
int n, seed;

int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	bignum_t BMax = rand();
	bignum_t BMin = rand();
	if(BMin > BMax)
		swap(BMin, BMax);
	printf("%d %lld %lld\n", n, BMin, BMax);
	for(int i = 0; i < n; i ++)
		printf("%d ", rand() % 400000);
}
