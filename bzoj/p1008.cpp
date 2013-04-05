#include <cstdio>
#include <iostream>
#define MODNUM 100003
using std::cin;
using std::cout;
typedef long long ll;
ll expMod(ll a, ll b)
{
	if(b == 0)
		return 1;
	if(b == 1)
		return a % MODNUM;
	ll tmp = expMod(a % MODNUM, b >> 1);
	ll ans = tmp * tmp % MODNUM;
	if(b & 1)
		return (ans * (a % MODNUM) % MODNUM);
	else
		return ans;
}
ll n, m;
int main()
{
	freopen("t.in", "r", stdin);
	cin >> m >> n;
	ll r = expMod(m, n), s = (m % MODNUM * expMod(m - 1, n - 1)) % MODNUM;
	ll ans = r - s;
	if(ans < 0)
		ans += MODNUM;
	cout << ans << '\n';
}
