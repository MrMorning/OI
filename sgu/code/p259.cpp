#include <cstdio>
#include <algorithm>
using namespace std;
const int N_MAX = 111;
int N, T[N_MAX], L[N_MAX], arr[N_MAX];
bool cmpL(int i, int j) {
	return L[i] > L[j];
}
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &T[i]);
	for ( int i = 1; i <= N; i ++ )
		scanf("%d", &L[i]);
	for ( int i = 1; i <= N; i ++ )
		arr[i] = i;
	sort(arr + 1, arr + 1 + N, cmpL);
	int ans = 0, acc = 0;
	for ( int i = 1; i <= N; i ++ ) {
		acc += T[arr[i]];
		ans = max(ans, acc + L[arr[i]]);
	}
	printf("%d\n", ans);
}
