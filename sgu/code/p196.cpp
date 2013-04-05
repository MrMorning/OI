#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
int dgr[10000];
int n, m;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i ++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		dgr[a] ++, dgr[b] ++;
	}
	ll ans = 0;
	for(int i = 0; i < n; i ++)
		ans += (ll)dgr[i] * dgr[i];
	cout << ans;
}
