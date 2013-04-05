#include <iostream>
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}
int main()
{
	ll t, n;
	cin >> t;
	n = (t + 1) >> 1;
	ll g = gcd(2 * n - 1, n + 1);
	cout << g * ((2 * n - 1) / g / 2) + 1;
}
