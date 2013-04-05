#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cassert>
typedef long long ll;
using namespace std;

ll a1, a2, p, k, x0, y0, x1, y1, g;

ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}

void exGcd(ll a, ll b, ll &x, ll &y)
{
	if(b == 0)
		x = 1, y = 0;
	else
	{
		ll x0, y0;
		exGcd(b, a % b, x0, y0);
		x = y0, y = x0 - a / b * y0;
	}
}

void noSol()
{
	printf("NO\n");
	exit(0);
}

void genSol()
{
	ll p1, n1, p2, n2;
	if(x1 < 0)
		p1 = 0, n1 = -x1;
	else
		p1 = x1, n1 = 0;

	if(y1 < 0)
		p2 = 0, n2 = -y1;
	else
		p2 = y1, n2 = 0;

	ll t = p1 + n1 + p2 + n2;
	if(t <= k)
		p1 += (k - t) / 2, n1 += (k - t) / 2;
	else
		noSol();
	assert(p1 * a1 - n1 * a1 + p2 * a2 - n2 * a2 == p);
	assert(p1 + n1 + p2 + n2 == k);
	assert(p1 >= 0 && p2 >= 0 && n1 >= 0 && n2 >= 0);
	printf("YES\n");
	//cout << p1 << ' ' << n1 << ' ' << p2 << ' ' << n2;
	exit(0);
}

void test(ll x0, ll y0, ll t)
{
	if(abs(x0 + a2 / g * t) + abs(y0 - a1 / g * t) < abs(x1) + abs(y1))
		x1 = x0 + a2 / g * t, y1 = y0 - a1 / g * t;
}

int main()
{
	freopen("t.in", "r", stdin);
	x1 = y1 = 1000000000000000000LL;
	cin >> a1 >> a2 >> p >> k;
	if(k == 0)
	{
		if(p == 0)
			printf("YES\n0 0 0 0\n");
		else
			noSol();
		exit(0);
	}
	g = gcd(a1, a2);
	if(p % g != 0)
		noSol();
	exGcd(a1, a2, x0, y0);
	x0 *= p / g, y0 *= p / g;

	//minimize |x1| + |y1|
	ll r1 = x0 / (a2 / g), r2 = y0 / (a1 / g);
	for(int r = -10; r <= 10; r ++)
	{
		test(x0, y0, r1 + r);
		test(x0, y0, -r1 + r);
		test(x0, y0, r2 + r);
		test(x0, y0, -r2 + r);
	}

	if((x1 + y1 + k) % 2 == 0)
		genSol();
	else
		if((a2 - a1) / g % 2 != 0)
		{
			x0 = x1, y0 = y1;
			x1 = y1 = 1000000000000000000LL;
			for(int r = -11; r <= 11; r += 2)
				test(x0, y0, r);
			genSol();
		}
		else
			noSol();
}
