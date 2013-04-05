#include <cstdio>
#include <algorithm>
#define FAC 3
using namespace std;
int max_dep;
int ceil_div(int a, int b) {
	if ( a % b == 0 )
		return a / b;
	return a / b + 1;
}
int f(int dep, int N) {
	max_dep = max(max_dep, dep);
	if ( N == 1 )
		return 0;
	return ceil_div(N, FAC) + f(dep + 1,(FAC - 1) * N / FAC) + f(dep + 1, ceil_div(N, FAC));
}

int main() {
	freopen("t.in", "r", stdin);
	int N;

	scanf("%d", &N);
	printf("%d\n", f(1, N));
	printf("%d\n", max_dep);
}
