#include <cstdio>
#include <cmath>

const double kPi = acos(-1);
struct Matrix {
	double ele[4][4];
	Matrix(){}
	Matrix(double a00, double a01, double a02, double a03,
			double a10, double a11, double a12, double a13,
			double a20, double a21, double a22, double a23,
			double a30, double a31, double a32, double a33) {
		ele[0][0] = a00; ele[0][1] = a01; ele[0][2] = a02; ele[0][3] = a03;
		ele[1][0] = a10; ele[1][1] = a11; ele[1][2] = a12; ele[1][3] = a13;
		ele[2][0] = a20; ele[2][1] = a21; ele[2][2] = a22; ele[2][3] = a23;
		ele[3][0] = a30; ele[3][1] = a31; ele[3][2] = a32; ele[3][3] = a33;
	}
} memo[11];

Matrix operator* (const Matrix &A, const Matrix &B) {
	Matrix C;
	for ( int i = 0; i < 4; i ++ )
		for ( int j = 0; j < 4; j ++ ) {
			C.ele[i][j] = 0;
			for ( int k = 0; k < 4; k ++ )
				C.ele[i][j] += A.ele[i][k] * B.ele[k][j];
		}
	return C;
}

int main() {
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	Matrix T (	1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
	for ( int i = 0; i < n; i ++ ) {
		static char cmd[4];
		scanf("%s", cmd);
		if ( cmd[0] == 'T' ) {
			double x, y, z;
			scanf("%lf%lf%lf", &x, &y, &z);
			Matrix F (	1, 0, 0, x,
						0, 1, 0, y,
						0, 0, 1, z,
						0, 0, 0, 1);
			T = F * T;
		} else if ( cmd[0] == 'S' ) {
			double x, y, z;
			scanf("%lf%lf%lf", &x, &y, &z);
			Matrix F (	x, 0, 0, 0,
						0, y, 0, 0,
						0, 0, z, 0,
						0, 0, 0, 1);
			T = F * T;
		} else {
			double x, y, z, a;
			scanf("%lf%lf%lf%lf", &x, &y, &z, &a);
			double c = 1/sqrt(x*x+y*y+z*z);
			x *= c, y *= c, z *= c;
			a = a / 180 * kPi;
			double sina = sin(a), cosa = cos(a);
			Matrix F (	cosa+(1-cosa)*x*x, (1-cosa)*x*y-sina*z, (1-cosa)*x*z+sina*y, 0,
						(1-cosa)*y*x+sina*z, cosa+(1-cosa)*y*y, (1-cosa)*y*z-sina*x, 0,
						(1-cosa)*z*x-sina*y, (1-cosa)*z*y+sina*x, cosa+(1-cosa)*z*z, 0,
						0, 0, 0, 1);
			T = F * T;
		}
	}

	int m;
	scanf("%d", &m);
	while ( m -- ) {
		double x, y, z;
		scanf("%lf%lf%lf", &x, &y, &z);
		Matrix A (	x, 0, 0, 0,
					y, 0, 0, 0,
					z, 0, 0, 0,
					1, 0, 0, 0);
		A = T * A;
		printf("%.2lf %.2lf %.2lf\n", A.ele[0][0], A.ele[1][0], A.ele[2][0]);
	}
}
