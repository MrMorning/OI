#include <cstdio>
#include <algorithm>
using namespace std;
int a[111111], b[111111], arr[111111];
int n;

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		scanf("%d%d", &a[i], &b[i]);
	for ( int i = 0; i < n - 1; i ++ ) {
		arr[i] = a[i] - b[i];
		a[i + 1] += arr[i];
	}
	sort(arr, arr + n - 1);
	int mid = -arr[(n - 1) / 2];
	int res = abs(mid);
	for ( int i = 0; i < n - 1; i ++ )
		res += abs(mid + arr[i]);
	printf("%d\n", res);
}
