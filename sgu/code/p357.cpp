#include <cstdio>
#include <algorithm>
using namespace std;
int on[10], onUp, onDown, onCho, X, Y;

int calcDist(int X, int Y) {
	if ( X == Y ) return 0;
	int ret = 0x3f3f3f3f;
	if ( onUp )
		ret = min(ret, ((Y-X)%100+100)%100);
	if ( onDown )
		ret = min(ret, ((X-Y)%100+100)%100);
	return ret;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &on[1], &on[2], &on[3], &onUp);
	scanf("%d%d%d%d", &on[4], &on[5], &on[6], &onDown);
	scanf("%d%d%d", &on[7], &on[8], &on[9]);
	scanf("%d%d", &onCho, &on[0]);
	scanf("%d%d", &X, &Y);
	int best = 0x3f3f3f3f;
	best = min(best, calcDist(X, Y));

	for ( int x = 0; x <= 9; x ++ )
		if ( on[x] )
			best = min(best, calcDist(x, Y) + 1);
	for ( int x = 10; x <= 99; x ++ )
		if ( onCho && on[x/10] && on[x%10] )
			best = min(best, 3+calcDist(x, Y));

	if ( best == 0x3f3f3f3f )
		printf("-1\n");
	else
		printf("%d\n", best);
}
