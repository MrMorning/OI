#include <cstdio>
#include <algorithm>
using namespace std;

int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

int calc(int a, int b){
	if(b > a)
		return calc(b, a);
	if(b == 1)
		return a - 1;
	return a / b + calc(b, a % b);
}

int main(){
	//freopen("t.in", "r", stdin);
	int n;
	scanf("%d", &n);
	int ans = 0x3f3f3f3f;
	for(int x = 1; x <= n; x ++)
		if(gcd(x, n) == 1)
			ans = min(ans, calc(n, x));
	printf("%d\n", ans);
}
