#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#define T_MAX 50
typedef long long ll;


const ll TAB[51] = {0LL, 0LL, 6LL,10LL,24LL,40LL,96LL,212LL,354LL,636LL,1530LL,3790LL,5168LL,11296LL,18032LL,35014LL,127556LL,260036LL,309862LL,646398LL,1120386LL,2824530LL,5937928LL,16229288LL,19019184LL,41221520LL,117897414LL,237197004LL,516947414LL,759363936LL,1860972212LL,3773807884LL,4598370592LL,9226777156LL,20775609554LL,63066868960LL,116781162562LL,271800130134LL,310177951490LL,799988727350LL,1163881006374LL,2974375181854LL,4894820107330LL,11265929685284LL,25674830622610LL,36495497126792LL,108081342245772LL,144959951787524LL,290773131908030LL,798644274095172LL,1251638183065922LL};

struct Matrix {
	int ele[55][55];
	void clear() {
		memset(ele, 0, sizeof(ele));
	}
} F;
int T;
int C[55];
ll ans[55];

Matrix mul(const Matrix &A, const Matrix &B) {
	static Matrix C;
	for ( int i = 1; i <= T; i ++ )
		for ( int j = 1; j <= T; j ++ ) {
			C.ele[i][j] = 0;
			for ( int k = 1; k <= T; k ++ )
				C.ele[i][j] ^= A.ele[i][k] & B.ele[k][j]; 
		}
	return C;
}

bool check(ll n) {
	static Matrix A, R;
	A = F;
	if ( n & 1 ) 
		R = A;
	else {
		R.clear();
		for ( int i = 1; i <= T; i ++ )
			R.ele[i][i] = 1;
	}
	for ( n >>= 1; n; n >>= 1 ) {
		A = mul(A, A);
		if ( n & 1 )
			R = mul(R, A);
	}
	for ( int i = 1; i <= T; i ++ )
		for ( int j = 1; j <= T; j ++ )
			if ( i == j ) {
				if ( R.ele[i][j] != 1 ) return false;
			} else
				if ( R.ele[i][j] != 0 ) return false;
	return true;
}

int main() {
	/*
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	
	for ( T = 2; T <= T_MAX; T ++ ) {
		bool succ = false;
		while ( !succ ) {
			succ = true;
			F.clear();
			for ( int i = 1; i <= T; i ++ )
				F.ele[1][i] = C[i] = rand() % 2;
			for ( int i = 2; i <= T; i ++ )
				F.ele[i][i-1] = 1;
			ll lim = (1LL<<T)-1;
			if ( check(lim) ) {
				for ( ll x = 2; x * x <= lim; x++ )
					if ( lim % x == 0 )
						if ( check(x) || check(lim / x) ) {
							succ = false;
							break;
						}
			} else succ = false;
		}
		for ( int i = 1; i <= T; i ++ )
			if ( C[i] )
				ans[T] ^= 1LL<<i;
		fprintf(stderr, "%d\n", T);
	}
	for ( T = 2; T <= T_MAX; T++ )
		printf("%I64dLL,", ans[T]);
	return 0;
	*/
	int k;
	scanf("%d", &k);
	for ( int i = 1; i <= k; i ++ )
		printf("%d ", (TAB[k]&(1LL<<i))>0);
	printf("\n");
	for ( int i = 0; i < k-1; i ++ )
		printf("0 ");
	printf("1\n");
}
