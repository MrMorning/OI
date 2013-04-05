#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll q, f[4000000];
int c;
int main() {
	freopen("t.in", "r", stdin);
	cin >> q >> c;
	for ( int i = 0; i <= c; i ++ )
		f[i] = i;
	for ( int i = c + 1; ; i ++ ) {
		f[i] = f[i - 1] + f[i - c - 1] + 1;
		if ( f[i] >= q )
			break;
	}
	for ( int i = 0; ; i ++ ) {
		if ( f[i] >= q ) {
			cout << i + c;
			return 0;
		}
	}
}
