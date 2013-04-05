#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

const int P_MAX = 10007;

int P, L;

struct Matrix {
	int ele[3][3];
	bool operator< (const Matrix &t) const {
		for ( int i = 0; i < 3; i ++ )
			for ( int j = 0; j < 3; j ++ )
				if ( ele[i][j] < t.ele[i][j] )
					return true;
				else if ( ele[i][j] > t.ele[i][j] )
					return false;	
		return false;
	}
} id_mat, trans_mat;

map<Matrix, int> MP;

Matrix mat_mul(const Matrix &A, const Matrix &B) {
	Matrix C;
	for ( int i = 0; i < 3; i ++ )
		for ( int j = 0; j < 3; j ++ ) {
			C.ele[i][j] = 0;
			for ( int k = 0; k < 3; k ++ )
				C.ele[i][j] += A.ele[i][k] * B.ele[k][j];
			C.ele[i][j] %= P;
		}
	return C;
}

Matrix mat_pow(Matrix A, ll n) {
	Matrix res = n & 1 ? A : id_mat;
	for ( n >>= 1; n; n >>= 1 ) {
		A = mat_mul(A, A);
		if ( n & 1 ) 
			res = mat_mul(res, A);
	}
	return res;
}

Matrix mat_inv(const Matrix &A) {
	return mat_pow(A, P - 2);
}

int mat_log(const Matrix &des, bool above_zero = false) {
	for ( int e = 0; e * L <= P * P; e ++ ) {
		Matrix T = mat_pow(trans_mat, e * L),
			   X = mat_mul(des, mat_inv(T));
		if ( MP.count(X) && !(above_zero && e * L + MP[X] == 0))
			return e * L + MP[X];
	}
	return -1;
}

int appear[P_MAX];

void solve() {
	int A, B, X, Y, Z, C, Q;
	scanf("%d%d%d%d%d%d%d%d", &A, &B, &X, &Y, &Z, &P, &C, &Q);
	L = P * (int)sqrt(P) + 1;
	memset(id_mat.ele, 0, sizeof(id_mat.ele));
	for ( int i = 0; i < 3; i ++ )
		id_mat.ele[i][i] = 1;

	memset(trans_mat.ele, 0, sizeof(trans_mat.ele));
	trans_mat.ele[0][1] = trans_mat.ele[2][2] = 1;
	trans_mat.ele[1][0] = Y;
	trans_mat.ele[1][1] = X;
	trans_mat.ele[1][2] = Z;

	Matrix init_mat;
	memset(init_mat.ele, 0, sizeof(init_mat));
	init_mat.ele[0][0] = A;
	init_mat.ele[1][0] = B;
	init_mat.ele[2][0] = 1;

	Matrix acc_mat = init_mat;
	for ( int i = 1; i < TEST_MAX; i ++ ) {
		printf("%d\n", acc_mat.ele[0][0]);
		acc_mat = mat_mul(trans_mat, acc_mat);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
