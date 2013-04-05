#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long int64;

const int N_FIB = 89;

int64 fib[N_FIB];
int64 f[N_FIB + 1], g[N_FIB + 1];

int64 solve(string s){
	int n = s.size();
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	f[n - 1] = 1;
	g[n - 1] = s[n - 1] == '0';
	for(int i = n - 2; i >= 0; i --)
		if(s[i] == '0')
			f[i] = f[i + 1], g[i] = f[i + 1] + (s[i + 1] == '0' ? g[i + 2] : 0);
		else
			f[i] = f[i + 1] + (s[i + 1] == '0' ? g[i + 2] : 0), g[i] = (s[i + 1] == '0' ? g[i + 2] : 0);
	return f[0];
}

int main(){
	fib[0] = fib[1] = 1;
	for(int i = 2; i < N_FIB; i ++)
		fib[i] = fib[i - 1] + fib[i - 2];
	int T;
	scanf("%d", &T);
	while(T --){
		int64 x;
		cin >> x;
		string str(N_FIB - 1, '0');
		for(int i = N_FIB - 1; i >= 1; i --)
			if(x >= fib[i]){
				str[N_FIB - i - 1] = '1';
				x -= fib[i];
			}
		cout << solve(str) << '\n';
	}
}
