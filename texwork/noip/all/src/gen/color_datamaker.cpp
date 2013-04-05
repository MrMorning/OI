#include <cstdio>
#include <cstdlib>
int seed;
long long n;
int main(){
	scanf("%lld%d", &n, &seed);
	srand(seed);
	int k = rand();
	printf("%lld %lld\n", (long long)n * k, (long long)k * (rand() % (n - 1) + 1));
}
