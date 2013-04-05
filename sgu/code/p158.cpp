#include <cstdio>
#include <cmath>
int L, M, N, P[301], D[301];
double solve(double S)
{
	int j = 1;
	double res = 0;
	for(int i = 1; i <= M; i ++)
	{
		while(j < N && fabs(S + D[j + 1] - P[i]) < fabs(S + D[j] - P[i]))
			j ++;
		res += fabs(S + D[j] - P[i]);
	}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &L, &M);
	for(int i = 1; i <= M; i ++)
		scanf("%d", &P[i]);
	scanf("%d", &N);
	D[1] = 0;
	for(int i = 2; i <= N; i ++)
		scanf("%d", &D[i]);
	double ans = 0, bestPos = -1;
	for(double pos = 0; D[N] + pos <= L; pos += 0.5)
	{
		double tmp = solve(pos);
		if(tmp > ans)
			ans = tmp, bestPos = pos;
	}
	printf("%.1lf %.1lf\n", bestPos, ans);
}
