#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int n;
string str[111];
bool cmp(const string &a, const string &b) {
	return a + b < b + a;
}
int main() {
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ )
		cin >> str[i];
	sort(str, str + n, cmp);
	string res;
	for ( int i = 0; i < n; i ++ )
		res += str[i];
	cout << res;
}
