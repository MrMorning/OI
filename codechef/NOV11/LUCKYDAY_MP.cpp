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
	bool operator== (const Matrix &t) const {
		return !(t < (*this)) && ! ((*this) < t);
	}
} id_mat, trans_mat, inv_mat;

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

int mat_log(const Matrix &des) {
	for ( int e = 0; e * L <= P * P; e ++ ) {
		Matrix T = mat_pow(inv_mat, e * L),
			   X = mat_mul(T, des);
		if ( MP.count(X) )
			return e * L + MP[X];
	}
	return -1;
}

int pow_mod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = a * a % P;
		if ( n & 1 )
			res = res * a % P;
	}
	return res;
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

	memset(inv_mat.ele, 0, sizeof(inv_mat.ele));
	inv_mat.ele[0][0] = (P - X) * pow_mod(Y, P - 2) % P;
	inv_mat.ele[0][1] = pow_mod(Y, P - 2) % P;
	inv_mat.ele[0][2] = (P - Z) * pow_mod(Y, P - 2) % P;
	inv_mat.ele[1][0] = 1;
	inv_mat.ele[2][2] = 1;


	Matrix init_mat;
	memset(init_mat.ele, 0, sizeof(init_mat));
	init_mat.ele[0][0] = A;
	init_mat.ele[1][0] = B;
	init_mat.ele[2][0] = 1;

	assert(mat_mul(trans_mat, inv_mat) == id_mat);

	MP.clear();
	Matrix acc_mat = id_mat;
	for ( int i = 0; i < L; i ++ ) {
		Matrix tmp_mat = mat_mul(acc_mat, init_mat);
		if ( MP.count(tmp_mat) == 0)
			MP[tmp_mat] = i;
		acc_mat = mat_mul(acc_mat, trans_mat);
	}

	int loop = -1;
	for ( int i = 1; i <= L; i ++ ) {
		if ( mat_pow(trans_mat, i) == id_mat ) {
			loop = i;
			break;
		}
	}
	if ( loop == -1 )
		for ( int e = 1; e * L <= P * P; e ++ ) {
			Matrix T = mat_pow(inv_mat, e * L),
				   X = mat_mul(T, init_mat);
			if ( MP.count(X) ) {
				loop = e * L + MP[X];
				break;
			}
		}
	int appear_size = 0;
	for ( int i = 0; i < P; i ++ ) {
		Matrix tmp_mat;
		memset(tmp_mat.ele, 0, sizeof(tmp_mat.ele));
		tmp_mat.ele[0][0] = C;
		tmp_mat.ele[1][0] = i;
		tmp_mat.ele[2][0] = 1;
		int res = mat_log(tmp_mat);
		if ( res != -1 )
			appear[appear_size ++] = res + 1;
	}
	sort(appear, appear + appear_size);

	while ( Q -- ) {
		ll l, r;
		scanf("%lld%lld", &l, &r);
		ll res = 0;
		ll lpos = (l - 1) % loop + 1,
		   rpos = (r - 1) % loop + 1;
#define IN_RANGE(x) (0 <= (x) && (x) < appear_size)
		if ( (r - 1) / loop == (l - 1) / loop ) {
			int lb = -1, rb = appear_size - 1;
			for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 )
				if ( appear[mid] >= lpos )
					rb = mid;
				else
					lb = mid;
			if ( IN_RANGE(rb) && appear[rb] >= lpos ) {

				int tmp = rb;
				lb = 0, rb = appear_size;
				for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 )
					if ( appear[mid] <= rpos )
						lb = mid;
					else
						rb = mid;
				if ( IN_RANGE(lb) && appear[lb] <= rpos && tmp <= lb )
					res += lb - tmp + 1;
			}
		} else {
			ll cnt = (r - 1) / loop - (l - 1) / loop - 1;
			if ( cnt > 0 )
				res += cnt * appear_size;
			int lb = -1, rb = appear_size - 1;
			for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 )
				if ( appear[mid] >= lpos )
					rb = mid;
				else
					lb = mid;
			if ( IN_RANGE(rb) && appear[rb] >= lpos )
				res += appear_size - rb;
			lb = 0, rb = appear_size;
			for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 )
				if ( appear[mid] <= rpos )
					lb = mid;
				else
					rb = mid;
			if ( IN_RANGE(lb) && appear[lb] <= rpos )
				res += lb + 1;
		}
		printf("%lld\n", res);
	}
	fprintf(stderr, "*%d\n", appear_size);
	fprintf(stderr, "*%d\n", loop);
	fprintf(stderr, "*%d\n", L);
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
