#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long int64;
const int64 INF = 0x3f3f3f3fLL;
int64 findBelow(int64 x, int64 y, int neg, int64 k){
	int64 lb = -INF, rb = INF;
	for(int64 mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
		if(neg * x + k * mid <= y)
			lb = mid;
		else
			rb = mid;
	return lb;
}

int64 findAbove(int64 x, int64 y, int neg, int64 k){
	int64 lb = -INF, rb = INF;
	for(int64 mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
		if(neg * x + k * mid >= y)
			rb = mid;
		else
			lb = mid;
	return rb;
}
int64 a, b, x1, y1, x2, y2;
int main(){
	freopen("t.in", "r", stdin);
	cin >> a >> b >> x1 >> y1 >> x2 >> y2;
	a *= 2, b *= 2;
	int64 p[2], q[2];
	p[0] = findAbove(x1, y1, 1, b);
	p[1] = findBelow(x1, y1, 1, b);
	q[0] = findAbove(x2, y2, 1, b);
	q[1] = findBelow(x2, y2, 1, b);
	int64 tmp = INF;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++){
			tmp = min(tmp, abs(p[i] - q[j]) + 1);
		}
	bool suc = false;
	for(int d = -1; d <= 1; d ++){
		int64 curB = p[0] + d;
		bool b1 = x1 + curB * b > y1;
		bool b2 = x1 + curB * b < y1;
		bool b3 = x2 + curB * b > y2;
		bool b4 = x2 + curB * b < y2;
		if((b1 && b4) || (b2 && b3))
			suc = true;
	}
	if(!suc)
		tmp = 0;
	int64 ans = tmp;
	p[0] = findAbove(x1, y1, -1, a);
	p[1] = findBelow(x1, y1, -1, a);
	q[0] = findAbove(x2, y2, -1, a);
	q[1] = findBelow(x2, y2, -1, a);
	tmp = INF;
	for(int i = 0; i < 2; i ++)
		for(int j = 0; j < 2; j ++)
			tmp = min(tmp, abs(p[i] - q[j]) + 1);

	suc = false;
	for(int d = -1; d <= 1; d ++){
		int64 curA =  p[0] + d;
		bool b1 = -x1 + curA * a > y1;
		bool b2 = -x1 + curA * a< y1;
		bool b3 = -x2 + curA * a> y2;
		bool b4 = -x2 + curA * a< y2;
		if((b1 && b4) || (b2 && b3))
			suc = true;
	}
	if(!suc)
		tmp = 0;
	ans = max(ans, tmp);
	cout << ans;
}
