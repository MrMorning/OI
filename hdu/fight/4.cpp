#include <cstdio>
#include <algorithm>
using namespace std;
int N, P, A, B;
double f[100010][2];
int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d%d%d", &N, &P, &A, &B) != EOF ) {
		if ( N == 0 && P == 0 && A == 0 && B == 0 )
			break;
		if ( N == 0 ) {
			printf("0.0000\n");
			continue;
		}
		f[N][0] = B;
		f[N][1] = 0;
		double Q = (double)P / 100;
		for ( int i = N - 1; i >= 1; i -- ) {
			f[i][0] = min(f[i + 1][0], f[i + 1][1] + A) + B;
			f[i][1] = Q * min(f[i + 1][0], f[i + 1][1] + A)
				+ (1 - Q) * f[i + 1][1];
		}
		printf("%.4lf\n", f[1][1]);
	}
}
