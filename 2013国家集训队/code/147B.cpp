#include <cstdio>
#include <algorithm>
using namespace std;

const int kInf = 0x3f3f3f3f;

struct Matrix {
	int ele[300][300];
} E, F[10], C;
int n, m;

Matrix operator* (const Matrix &A, const Matrix &B) {
	static Matrix res;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < n; j ++ ) {
			res.ele[i][j] = i==j?0:-kInf;
			for ( int k = 0; k < n; k ++ )
				if ( A.ele[i][k] != -kInf && B.ele[k][j] != -kInf )
					res.ele[i][j] = max(res.ele[i][j], A.ele[i][k]+B.ele[k][j]);
		}
	return res;
}

bool test(const Matrix &T) {
	for ( int i = 0; i < n; i ++ )
		if ( T.ele[i][i] > 0 ) return true;
	return false;
}

int myLog2(int n) {
	int res = 0;
	while ( n ) {
		res ++;
		n >>= 1;
	}
	return res-1;
}

int main() {
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < n; j ++ )
			E.ele[i][j] = i==j?0:-kInf;
	while ( m -- ) {
		int i, j, v1, v2;
		scanf("%d%d%d%d", &i, &j, &v1, &v2);
		i--, j--;
		E.ele[i][j] = v1, E.ele[j][i] = v2;
	}

	F[0] = E;
	for ( int i = 1; (1 << i) <= n; i ++ )
		F[i] = F[i-1] * F[i-1];

	C = E;
	int cnt = 1;
	for ( int i = myLog2(n); i >= 0; i -- ) {
		static Matrix N;
		N = C * F[i];
		if ( !test(N) ) {
			C = N;
			cnt += 1<<i;
		}
	}
	C = C * E;
	cnt ++;
	if ( test(C) ) 
		printf("%d\n", cnt);
	else 
		printf("0\n");
}
