#include <cstdio>
#include <algorithm>
#define FAC 2
using namespace std;
int ceil_div(int a, int b) {
	if ( a % b == 0 )
		return a / b;
	return a / b + 1;
}
pair<int, int> f(int N) {
	if ( N <= 1 )
		return make_pair(0, 0);
	pair<int, int> res;
	pair<int, int> tmp = f(ceil_div(N, FAC));
	res.second = ceil_div(2 * N * (FAC - 1), FAC) + tmp.second;
	res.first = tmp.first + FAC;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int N;

	scanf("%d", &N);
	printf("%d %d\n", f(N).first, f(N).second);
}
