#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
const int mod = 1000000007;

int n, x, a[100][100];
int main() {
	freopen("t.in", "r", stdin);
	cin >> x;
	for ( int i = 1; i <= 100; i ++ ) {
		for ( int j = 0; j < 100; j ++ )
			for ( int k = 0; k < 100; k ++ )
				a[j][k] = 0;
		for ( int j = 0; j < i; j ++ ) {
			int l = (j&1), r = i - (j&1)-l;
			while ( r - l > 2 || l==r ) {
				a[j][l] = 1;
				a[j][r] = 1;
				l+=2, r-=2;
			}
		}
		int sum = 0;
		for ( int j = 0; j < 100; j ++ )
			for ( int k = 0; k < 100; k ++ )
				sum += a[j][k];
		int cx = x;
		if ((cx&1) && (i&1)) cx--;
		if ((cx%4==2) && (i&1) && (i>3)) cx-=2;
		if ( sum>=x && cx%4 == 0) {
			cout << i << endl;
			return 0;
		}
	}
}
