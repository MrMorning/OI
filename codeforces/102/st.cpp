#include <iostream>
#include <cstdio>
using namespace std;

int main(){
	long long n;
	cin >> n;
	long long max = (n + 1) * 9 - n;
	long long min = max;
	for(long long i = 1; i * i * i <= n; i ++)
		if(n % i == 0)
			for(long long j = i, m = n / i; j * j <= m; j ++)
				if(m % j == 0){
					long long t = (i + 1) * (j + 2) * (m / j + 2) - n;
					if(t < min) min = t;
				}
	cout << min << ' ' << max;
	return 0;
}
