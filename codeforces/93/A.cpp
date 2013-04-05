#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
ll t1, t2, x1, x2, t0;
long double eval(ll y1, ll y2){
	return (long double)(t1 * y1 + t2 * y2) / (y1 + y2);
}
int main(){
//	freopen("t.in", "r", stdin);
	cin >> t1 >> t2 >> x1 >> x2 >> t0;
	long double ansDiff = 10e100;
	ll ansY1, ansY2;
	for(ll y1 = 0; y1 <= x1; y1 ++){
		ll lb = -1, rb = x2;
		for(ll mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
			if(eval(y1, mid) >= t0)
				rb = mid;
			else
				lb = mid;
		if(eval(y1, rb) < t0)
			continue;
		ll y2 = rb;
		long double diff = fabs(eval(y1, y2) - t0);
		lb = y2, rb = x2 + 1;
		for(ll mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
			if(eval(y1, mid) - t0 == diff)
				lb = mid;
			else
				rb = mid;
		y2 = lb;
		if(diff < ansDiff ||(diff == ansDiff && ansY1 + ansY2 < y1 + y2)){
			ansY1 = y1, ansY2 = y2;
			ansDiff = diff;
		}
	}
	cout << ansY1 << ' ' << ansY2;
}
