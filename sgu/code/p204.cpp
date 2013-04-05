#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
typedef long double val_t;
using namespace std;
const val_t PI = atan(1) * 4;
const val_t EPS = 10e-12;

val_t b1, t1, b2, t2, l, ds, df, g;

inline val_t SQR(val_t x)
{
	return x * x;
}

inline val_t adjustSpeed(val_t d, val_t t, val_t s)
{
	val_t b = t * SQR(s / d) / (d * SQR(s / d) - s);
	val_t theta = atan(b);
	val_t cosTheta = cos(theta);
	return g * s / (2 * SQR(cosTheta) * b);
}

inline val_t calcMinSpeed(val_t d, val_t b, val_t t, val_t s)
{
	val_t cosTheta = cos(PI / 4),
		   sinTheta = sin(PI / 4);
	val_t v0 = g * s / (2 * SQR(cosTheta));
	val_t h = -g / (2 * SQR(cosTheta) * v0) * SQR(d) + sinTheta / cosTheta * d;
	if(b <= h && h <= t)
		return v0;
	else if(h > t)
		return adjustSpeed(d, t, s);
	else
		return adjustSpeed(d, b, s);
}

inline val_t solve(val_t s)
{
	return max(calcMinSpeed(ds, b1, t1, ds + s),
			calcMinSpeed(l - s, b2, t2, l - s + df));
}

int main()
{
	freopen("t.in", "r", stdin);
	while(cin >> b1 >> t1 >> b2 >> t2 >> l >> ds >> df >> g)
	{
		val_t lb = 0, rb = l;
		for(val_t lmid = lb + (rb - lb) / 3, rmid = (lmid + rb) / 2;
				rb - lb > EPS; lmid = lb + (rb - lb) / 3, rmid = (lmid + rb) / 2)
		{
			if(solve(lmid) < solve(rmid))
				rb = rmid;
			else
				lb = lmid;
		}
		cout << setprecision(4) << setiosflags(ios::fixed) << sqrt(solve((lb + rb) / 2)) << '\n';
	}
}
