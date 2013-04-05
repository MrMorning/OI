#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long num_t;
const num_t oo = 0x3f3f3f3f3f3f3f3f;

num_t gcd(num_t a, num_t b)
{
	return b ? gcd(b, a % b) : a;
}

void exGcd(num_t a, num_t b, num_t &x, num_t &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return;
	}
	num_t x0, y0;
	exGcd(b, a % b, x0, y0);
	x = y0, y = x0 - a / b * y0;
}

int main()
{
	freopen("t.in", "r", stdin);
	num_t a, b, c, x1, y1, x2, y2;
	cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
	if(a < 0)
		a *= -1, x1 *= -1, x2 *= -1, swap(x1, x2);
	if(b < 0)
		b *= -1, y1 *= -1, y2 *= -1, swap(y1, y2);
	if(a == 0 || b == 0)
	{
		if(a == 0 && b == 0)
			cout << (c == 0 ? (x2 - x1 + 1) * (y2 - y1 + 1): 0);
		else 
		{
			if(a == 0)
				swap(a, b), swap(x1, y1), swap(x2, y2);
			if(-c % a != 0)
				cout << 0;
			else if(!(x1 <= -c / a && -c / a <= x2))
				cout << 0;
			else
				cout << y2 - y1 + 1;
		}
		return 0;
	}
	num_t g = gcd(a, b);
	if(-c % g != 0)
	{
		cout << 0;
		return 0;
	}
	num_t x0, y0;
	exGcd(a, b, x0, y0);
	x0 *= -c / g, y0 *= -c / g;
	num_t uplim = oo, lowlim = -oo;
	
	uplim = min(uplim, (num_t)(floor((double)(x2 - x0) / (b / g))));
	lowlim = max(lowlim, (num_t)(ceil((double)(x1 - x0) / (b / g))));
	uplim = min(uplim, (num_t)(floor((double)(y1 - y0) / -(a / g))));
	lowlim = max(lowlim, (num_t)(ceil((double)(y2 - y0) / -(a / g))));
	if(lowlim > uplim)
		cout << 0;
	else
		cout << uplim - lowlim + 1;
}
