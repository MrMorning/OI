#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int seed;
typedef long long ll;
const ll RANGE = 100LL;

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d", &seed);
	srand(seed);
	ll a = rand() % RANGE+1,
	   b = rand() % RANGE+1;
	if ( a > b )
		swap(a, b);
	printf("%lld %lld\n", a, b);
}
