#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double kEps = 1e-8;
const double kInf = 1e100;

int X;

double f[33], g[33][33], h[33][33][33], 
	   w1[33], w2[33][33], w3[33][33][33];

inline int sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	return x > 0 ? 1 : -1;
}

double profit(int i, int j) {
	if ( i <= 21 && (j > 21 || j < i) ) 
		return 1.0;
	return -1.0;
}

bool bigmanRoll(int i) {
	if ( i == 0 ) return true;
	if ( i >= 22 ) return false;
	double sum = 0;
	for ( int t = 1; t <= 6; t ++ )
		sum += f[i+t];
	sum /= 6;
	return sgn(f[i]-sum)==0?true:false;
}

bool casinoRoll(int i, int j, int k) {
	if ( k == 0 ) return true;
	if ( k >= 22 ) return false;
	double sum = 0;
	for ( int t = 1; t <= 6; t ++ )
		sum += h[i][j][k+t];
	sum /= 6;
	return sgn(h[i][j][k]-sum)==0?true:false;
}

int main() {
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	scanf("%d", &X);
	for ( int i = 1; i <= 27; i ++ ) {
		for ( int j = 22; j <= 27; j ++ )
			g[i][j] = profit(i,j) * X;
		for ( int j = 21; j >= 1; j -- ) {
			g[i][j] = profit(i,j) * X;
			double sum = 0;
			for ( int t = 1; t <= 6; t ++ )
				sum += g[i][j+t];
			sum /= 6;
			g[i][j] = min(g[i][j], sum);
		}
		double sum = 0;
		for ( int t = 1; t <= 6; t ++ )
			sum += g[i][t];
		sum /= 6;
		g[i][0] = sum;
	}

	for ( int i = 27; i >= 1; i -- ) {
		f[i] = g[i][0];
		if ( i <= 21 ) {
			double sum = 0;
			for ( int t = 1; t <= 6; t ++ )
				sum += f[i+t];
			sum /= 6;
			f[i] = max(f[i], sum);
		}
	}

	for ( int i = 1; i <= 27; i ++ )
		for ( int j = 1; j <= 27; j ++ ) {
			for ( int k = 27; k >= 22; k -- ) 
				h[i][j][k] = profit(j,k) + profit(i,k)*X;
			for ( int k = 21; k >= 1; k -- ) {
				h[i][j][k] = profit(j,k) + profit(i,k)*X;
				double sum = 0;
				for ( int t = 1; t <= 6; t ++ )
					sum += h[i][j][k+t];
				sum /= 6;
				h[i][j][k] = min(h[i][j][k], sum);
			}
		}

	for ( int i = 27; i >= 1; i -- )
		for ( int j = 27; j >= 1; j -- )
			for ( int k = 27; k >= 0; k -- ) {
				if ( casinoRoll(i, j, k) ) {
					w3[i][j][k] = 0;
					for ( int t = 1; t <= 6; t ++ )
						w3[i][j][k] += w3[i][j][k+t];
					w3[i][j][k] /= 6;
				} else {
					w3[i][j][k] = profit(j,k);
				}
			}

	for ( int i = 27; i >= 1; i -- )
		for ( int j = 27; j >= 0; j -- ) {
			w2[i][j] = j==0?-kInf:w3[i][j][0];
			if ( j <= 21 ) {
				double sum = 0;
				for ( int t = 1; t <= 6; t ++ )
					sum += w2[i][j+t];
				sum /= 6;
				w2[i][j] = max(w2[i][j], sum);
			}
		}
	for ( int i = 27; i >= 0; i -- ) {
		if ( bigmanRoll(i) ) {
			w1[i] = 0;
			for ( int t = 1; t <= 6; t ++ )
				w1[i] += w1[i+t];
			w1[i] /= 6;
		} else 
			w1[i] = w2[i][0];
	}

	printf("%.10lf\n", (w1[0]+1)/2);
}
