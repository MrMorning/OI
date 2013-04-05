#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

long long res1 = 0x3f3f3f3f3f3f3f3fLL;
long long res2 = -0x3f3f3f3f3f3f3f3fLL;
void test(long long a, long long b, long long c, int n){
	res1 = min(res1, (a + 1) * (b + 2) * (c + 2) - n);
	res2 = max(res2, (a + 1) * (b + 2) * (c + 2) - n);
}
int main(){
	int n;
	scanf("%d", &n);
	for(long long a = 1; a * a * a <= n; a ++)
		for(long long b = a; a * b * b <= n; b ++)
			if(n % (a * b) == 0){
				long long c = n / (a * b);
				test(a, b, c, n);
				test(a, c, b, n);
				test(b, a, c, n);
				test(b, c, a, n);
				test(c, a, b, n);
				test(c, b, a, n);
			}
	cout << res1 << ' ' << res2;
}
