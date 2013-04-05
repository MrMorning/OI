#include <cstdio>
#include <algorithm>
using namespace std;
int weight[111111], arr[111111], ans[111111], nAns;
bool cmpW(int i, int j) {
	return weight[i] < weight[j];
}
int n, d, a, b;
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &d);
	scanf("%d%d", &a, &b);
	for ( int i = 1; i <= n; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		weight[i] = x * a + b * y;
		arr[i] = i;
	}
	sort(arr + 1, arr + 1 + n, cmpW);
	for ( int i = 1; i <= n; i ++ ) {
		if ( d >= weight[arr[i]] ) {
			ans[nAns++] = arr[i];
			d -= weight[arr[i]];
		} else
			break;
	}
	printf("%d\n", nAns);
	for ( int i = 0; i < nAns; i ++ )
		printf("%d ", ans[i]);
}
