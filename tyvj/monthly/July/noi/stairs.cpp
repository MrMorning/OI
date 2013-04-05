#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>

typedef long long ll;

const int INIT_MATRIX[2][2] =
{
	{1, 0},
	{0, 0}
};

const int TRANSFER_MATRIX[2][2] =
{
	{1, 1},
	{1, 0}
};

struct Matrix
{
	int rowNum, colNum;
	int element[2][2];
	Matrix()
	{
		memset(element, 0, sizeof(element));
		rowNum = colNum = 0;
	}
} Identity;

ll stairNum;
int modNum;

Matrix operator* (const Matrix &M1, const Matrix &M2)
{
	assert(M1.colNum == M2.rowNum);
	Matrix result;
	result.rowNum = M1.rowNum;
	result.colNum = M2.colNum;
	for(int i = 0; i < result.rowNum; i ++)
		for(int j = 0; j < result.colNum; j ++)
			for(int k = 0; k < M1.colNum; k ++)
				result.element[i][j] = ((ll)result.element[i][j] + (ll)M1.element[i][k] * M2.element[k][j]) % modNum;
	return result;
}

Matrix pow(Matrix B, ll n)
{
	Matrix result = n & 1 ? B : Identity;
	for(n >>= 1; n; n >>= 1)
	{
		B = B * B;
		if(n & 1)
			result = result * B;
	}
	return result;
}

int fib(ll n)
{
	Matrix base;
	base.rowNum = 2, base.colNum = 1;
	memcpy(base.element, INIT_MATRIX, sizeof(INIT_MATRIX));
	Matrix trans;
	trans.rowNum = trans.colNum = 2;
	memcpy(trans.element, TRANSFER_MATRIX, sizeof(TRANSFER_MATRIX));
	Matrix accumulate = pow(trans, n);
	base = accumulate * base;
	return base.element[0][0];
}

int main()
{
	Identity.rowNum = Identity.colNum = 2;
	Identity.element[0][0] = Identity.element[1][1] = 1;
	std::cin >> stairNum >> modNum;
	printf("%d\n", (int)((ll)fib(stairNum) * fib(stairNum + 1) % modNum));
}
