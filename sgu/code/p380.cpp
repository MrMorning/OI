#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int h[100010];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int minH = 0x3f3f3f3f, maxH = -0x3f3f3f3f;
	int minC = 0, maxC = 0;
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d", &h[i]);
		minH = min(minH, h[i]);
		maxH = max(maxH, h[i]);
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( h[i] == minH )
			minC ++;
		if ( h[i] == maxH )
			maxC++;
	}
	if ( minC%2==1 && maxC%2==1 ) puts("NO");
	else puts("YES");
}
