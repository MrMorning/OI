#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int over() { cout << "no solution" << endl; return 0; }
inline bool inInterval(double a, double b, double c)
{
	if(b > c) return a < b && a > c;
	else return a > b && a < c;
}
inline double value(double c, double x, double a, double b) { return (c - x * a) / b; }

int main()
{
	freopen("t.in", "r", stdin);
	double x1, x2, y1, y2;
	int k;
	cin >> x1 >> y1 >> x2 >> y2 >> k;

	double a, b, c;
	a = y1 - y2;
	b = x2 - x1;
	c = y1 * x2 - y2 * x1;

	if(a == 0 || b == 0) return over();
	double prex, prey, addx, addy;
	addx = x1 < x2 ? 1 : -1;
	addy = y1 < y2 ? 1 : -1;
	prex = x1, prey = y1;

	while(--k)
	{
		if(value(c, prex + addx, a, b) == prey + addy)
			prex += addx, prey += addy, x1 = prex, y1 = prey;
		else if(inInterval(value(c, prex + addx, a, b), prey, prey + addy))
			prex += addx, x1 = prex, y1 = value(c, prex, a, b);
		else
			prey += addy, y1 = prey, x1 = value(c, prey, b, a);
		if(prex == x2 && prey == y2) return over();
	}

	if(value(c, prex + addx, a, b) == prey + addy)
		x1 = (x1 + prex + addx) / 2, y1 = (y1 + prey + addy) / 2;
	else if(inInterval(value(c, prex + addx, a, b), prey, prey + addy))
		x1 = (x1 + prex + addx) / 2, y1 = (y1 + value(c, prex + addx, a, b)) / 2;
	else
		y1 = (y1 + prey + addy) / 2, x1 = (x1 + value(c, prey + addy, b, a)) / 2;

	cout << (int)floor(x1) << " " << (int)floor(y1) << endl;
	return 0;
}
