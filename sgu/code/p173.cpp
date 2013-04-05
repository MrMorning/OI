#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

struct Matrix
{
	int ele[51][51];
	int n, m;
	Matrix()
	{
		memset(ele, 0, sizeof(ele));
	}
} elimMat;

int N, M, K, L, S[11], D[11], A[51];
char str[55], finalStr[55];

Matrix mul(const Matrix &A, const Matrix &B)
{
	assert(A.m == B.n);
	Matrix res;
	res.n = A.n, res.m = B.m;
	for(int i = 1; i <= A.n; i ++)
		for(int j = 1; j <= B.m; j ++)
			for(int k = 1; k <= A.m; k ++)
				res.ele[i][j] ^= A.ele[i][k] & B.ele[k][j];
	return res;
}

Matrix pow(Matrix A, int n)
{
	assert(A.n == A.m);
	Matrix res;
	if(n & 1)
		res = A;
	else
	{
		res.n = res.m = A.n;
		for(int i = 1; i <= A.n; i ++)
			res.ele[i][i] = 1;
	}
	for(n >>= 1; n; n >>= 1)
	{
		A = mul(A, A);
		if(n & 1)
			res = mul(res, A);
	}
	return res;
}

void readData()
{
	scanf("%d%d%d%d", &N, &M, &K, &L);
	for(int i = 1; i <= M; i ++)
		scanf("%d%d", &S[i], &D[i]);
	elimMat.n = L, elimMat.m = K;
	for(int i = 1; i <= L; i ++)
	{
		scanf("%s", str);
		for(int j = 1; j <= K; j ++)
			elimMat.ele[i][(j - 2 + K) % K + 1] = str[j - 1] - '0';
		char ch = str[0];
		scanf("%s", str);
		elimMat.ele[i][K] = str[K - 1] != ch;
	}
	scanf("%s", finalStr);
}

void elimination()
{
	Matrix &mat = elimMat;
	for(int i = 1; i <= K - 1; i ++)
	{
		int p;
		for(p = i; p <= L && mat.ele[p][i] == 0; p ++);
		assert(p != L + 1);
		for(int k = 1; k <= K; k ++)
			swap(mat.ele[i][k], mat.ele[p][k]);
		for(int j = 1; j <= L; j ++)
			if(j != i && mat.ele[j][i] == 1)
				for(int k = 1; k <= K; k ++)
					mat.ele[j][k] ^= mat.ele[i][k];
	}
	for(int i = 1, j = 1; j != K && i <= L; i ++)
	{
		if(mat.ele[i][j])
			A[j] = mat.ele[i][K], j ++;
	}
}

void workBackward()
{
	static Matrix moveMat, turnMat, transMat;
	moveMat.n = moveMat.m = turnMat.n = turnMat.m = K;
	for(int i = 1; i <= K; i ++)
	{
		moveMat.ele[i][(i - 2 + K) % K + 1] = 1;
		turnMat.ele[i][i] = 1;
	}
	for(int i = 1; i <= K - 1; i ++)
		turnMat.ele[K][i] = A[i];
	transMat = mul(moveMat, turnMat);
	for(int i = M; i >= 1; i --)
	{
		Matrix tmpMat;
		tmpMat.n = K, tmpMat.m = 1;
		for(int j = S[i]; j <= S[i] + K - 1; j ++)
			tmpMat.ele[j - S[i] + 1][1] = finalStr[j - 1] - '0';
		tmpMat = mul(pow(transMat, D[i]), tmpMat);
		for(int j = S[i]; j <= S[i] + K - 1; j ++)
			finalStr[j - 1] = '0' + tmpMat.ele[j - S[i] + 1][1];
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	readData();
	elimination();
	workBackward();
	printf("%s", finalStr);
}
