#include <cstdio>
#include <iostream>
using namespace std;
long long l, r;
void zj(long long &x){
	long long p = 1;
	while(x >= p && x / p % 10 == 7)
	{
		x = x - p * 3;
		p *= 10;
	}
	if(p > x) x += p * 4;
	else x += p * 3;
}
void work()
{
	long long x = 4, y, ans = 0;
	while(x<l) zj(x);
	if(x<r) ans += x * (x - l + 1);
	else ans += x * (r - l + 1);
	while(x <= r){
		y = x;
		zj(x);
		if(x>r)ans += x * (r - y);
		else ans += x * (x - y);
	}
	cout << ans << endl;
}
int main(){
	cin >> l >> r;
	work();
}
