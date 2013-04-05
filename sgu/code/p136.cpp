#include <cstdio>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

const double EPS = 10e-3;
vector<double> coef[2], res[2];

void check(const vector<double> &coef, const vector<double> &res)
{
	int n = coef.size();
	for(int i = 0; i < n; i ++)
		assert(fabs(res[i] + res[(i + 1) % n] - coef[i]) < EPS);
}

void solve(const vector<double> &coef, vector<double> &output)
{
	int n = coef.size();
	double base;
	if(n & 1)
	{
		double acc = 0;
		for(int i = 0; i < n - 1; i ++)
			acc += coef[i] * ((i + 1) & 1 ? -1 : 1);
		acc += coef[n - 1];
		base = acc / 2;
	}
	else
	{
		double acc = 0;
		for(int i = 0; i < n; i ++)
			acc += coef[i] * ((i + 1) & 1 ? 1 : -1);
		if(fabs(acc) > EPS)
			return;
		base = 0;
	}

	for(int i = 0; i < n; i ++, base = output.back())
		output.push_back(coef[(i - 1 + n) % n] - base);
}

int main()
{
	freopen("t.in", "r", stdin);
	int np;
	scanf("%d", &np);
	for(int i = 0; i < np; i ++)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		coef[0].push_back(x * 2), coef[1].push_back(y * 2);
	}

	for(int t = 0; t < 2; t ++)
		solve(coef[t], res[t]);
	if(res[0].size() == 0 || res[1].size() == 0)
		printf("NO\n");
	else
	{
		printf("YES\n");
		assert(res[0].size() == res[1].size());
		for(int i = 0; i < (int)res[0].size(); i ++)
			printf("%.3lf %.3lf\n", res[0][i], res[1][i]);
		for(int t = 0; t < 2; t ++)
			check(coef[t], res[t]);
	}
}
