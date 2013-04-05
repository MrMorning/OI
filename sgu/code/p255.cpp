#include <cstdio>
typedef long long ll;
const int LIM = 100000;
int calc1(int M) {
	int res = 0;
	for ( ll p1 = 0; p1 <= LIM; p1 ++ )
		if ( p1 * (p1 - 1) / 2 == M )
			res ++;
	return res;
}
int calc2(int M) {
	int res = 0;
	for ( ll p2 = 0; p2 <= LIM; p2 ++ ) {
		ll p1 = M - (p2 * (p2 - 1) / 2);
		if ( 0 <= p1 && p1 < p2 )
			res ++;
	}
	return res;
}
int calc3(int M) {
	int res = 0;
	for ( ll p3 = 0; p3 <= LIM; p3 ++ ) {
		ll p2 = M - (p3 * (p3 - 1) / 2) - 1;
		if ( 0 < p2 && p2 < p3 ) {
			if ( p2 > 1 )
				res += 2;
			else
				res ++;
		}
	}
	return res;
}
void solve() {
	int M;
	scanf("%d", &M);
	int ans = 0;
	ans += calc1(M);
	if ( ans <= 1 )
		ans += calc2(M);
	if ( ans <= 1 )
		ans += calc3(M);
	printf("%s\n", ans == 1 ? "YES" : "NO");
}
int main() {
	int TST;
	scanf("%d", &TST);
	while ( TST -- ) 
		solve();
}
