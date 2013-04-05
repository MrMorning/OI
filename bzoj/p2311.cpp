#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define ABS(x) ((x) > 0 ? (x) : (-(x)))

const int N_MAX = 55;
const double EPS = 10E-8;
double mtx[N_MAX * N_MAX][N_MAX * N_MAX + 1];
int n_row, n_col, n_ele;

namespace trick
{
	const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
	int p2i(int i, int j);
}

namespace pre_work
{
	double prob[N_MAX][N_MAX][4];
	void read_data();
	void create_equation();
	void main();
}

namespace solve
{
	void elimination();
	void main();
}

void pre_work::read_data()
{
	scanf("%d%d", &n_row, &n_col);
	n_ele = n_row * n_col;
	for(int dir = 0; dir < 4; dir ++)
		for(int i = 0; i < n_row; i ++)
			for(int j = 0; j < n_col; j ++)
				scanf("%lf", &prob[i][j][dir]);
}

void pre_work::create_equation()
{
	for(int i = 0; i < n_row; i ++)
		for(int j = 0; j < n_col; j ++)
		{
			int now = trick::p2i(i, j);
			mtx[now][now] = -1;
			mtx[now][n_ele] = -1;
			for(int dir = 0; dir < 4; dir ++)
			{
				int ni = i + trick::dx[dir],
					nj = j + trick::dy[dir];
				if(0 <= ni && ni < n_row)
					if(0 <= nj && nj < n_col)
						mtx[now][trick::p2i(ni, nj)] = prob[i][j][dir];
			}
		}
	mtx[trick::p2i(n_row - 1, n_col - 1)][n_ele] = 0;
}

void pre_work::main()
{
	read_data();
	create_equation();
}

void solve::elimination()
{
	for(int i = n_row - 1; i >= 0; i --)
		for(int j = n_col - 1; j >= 0; j --)
		{
			int now = trick::p2i(i, j);
			double tmp = mtx[now][now];
			for(int k = 0; k <= n_ele; k ++)
				mtx[now][k] /= tmp;
			for(int cur = max(0, trick::p2i(i - 1, j)); cur < now; cur ++)
			{
				tmp = mtx[cur][now];
				for(int k = max(0, trick::p2i(i - 1, j)); k <= now; k ++)
					mtx[cur][k] -= tmp * mtx[now][k];
				mtx[cur][n_ele] -= tmp * mtx[now][n_ele];
			}
		}
}

void solve::main()
{
	elimination();
	printf("%.3lf\n", mtx[trick::p2i(0, 0)][n_ele]);
}

int trick::p2i(int i, int j)
{
	return i * n_col + j;
}

int main()
{
	freopen("t.in", "r", stdin);
	pre_work::main();
	solve::main();
}
