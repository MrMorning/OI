#include <cstring>
#include <cstdio>
#include <cassert>
#define MOD 1000000007 
#define STEP 15
int L[STEP];
int f[16];

struct Matrix{
	int nrow, ncol;
	int ele[20][20];
	Matrix(){
		memset(ele, 0, sizeof(ele));
	}
} F, T, R;

Matrix operator* (const Matrix &A, const Matrix &B){
	assert(A.ncol == B.nrow);
	Matrix res;
	res.nrow = A.nrow;
	res.ncol = B.ncol;
	for(int i = 0; i < res.nrow; i ++)
		for(int j = 0; j < res.ncol; j ++)
			for(int k = 0; k < A.ncol; k ++)
				res.ele[i][j] = (res.ele[i][j] + (long long)A.ele[i][k] * B.ele[k][j]) % MOD;
	return res;
}

Matrix pow(Matrix A, long long n){
	Matrix res;
	if(n & 1)
		res = A;
	else{
		res.nrow = res.ncol = A.nrow;
		for(int i = 0; i < res.nrow; i ++)
			res.ele[i][i] = 1;
	}
	for(n >>= 1; n; n >>= 1){
		A = A * A;
		if(n & 1)
			res = res * A;
	}
	return res;
}

long long N;
void work(){
	int K;
	scanf("%lld", &N);
	scanf("%d", &K);
	for(int i = 0; i < K; i ++)
		scanf("%d", &L[i]);
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for(int i = 1; i <= STEP; i ++)
		for(int j = 0; j < K; j ++)
			if(i >= L[j])
				f[i] = (f[i] + f[i - L[j]]) % MOD;
	if(N <= STEP){
		printf("%d\n", f[N]);
		return;
	}
	F.ncol = 1;
	F.nrow = STEP;
	for(int i = 1; i <= STEP; i ++)
		F.ele[i - 1][0] = f[i];
	T = Matrix();
	T.ncol = T.nrow = STEP;
	for(int i = 0; i < K; i ++){
		int p = STEP - L[i];
		if(p <= STEP)
			T.ele[STEP - 1][p] ++;
	}
	for(int j = 0; j < STEP - 1; j ++)
		T.ele[j][j + 1] ++;
	R = pow(T, N - STEP);
	F = R * F;
	printf("%d\n", F.ele[STEP - 1][0]);
}

int main(){
	freopen("t.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T --)
		work();
}
