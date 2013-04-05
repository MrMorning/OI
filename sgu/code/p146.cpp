#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
int n;
int main()
{
	freopen("t.in", "r", stdin);
	double ltmp;
	cin >> ltmp >> n;
	ll L = round(ltmp * 10000);
	ll T, V;
	ll acc = 0;
	for(int i = 0; i < n; i ++)
	{
		cin >> T >> V;
		V *= 10000;
		acc += V * T;
		acc %= L;
	}
	ll ans = min(acc, L - acc);
	printf("%.4lf\n", (double)ans / 10000);
}
