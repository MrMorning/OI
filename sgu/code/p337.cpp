#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
string cyc, str, ans;
int bound;

bool check(int len) {
	int diff = 0;
	for ( int i = 0; i + 2 * len - 1 < (int)str.length(); i ++ ) {
		if ( i == 0 ) {
			diff = 0;
			for ( int k = 0; k < len; k ++ )
				diff += str[i + k] != str[i + len + k];
		} else {
			diff -= str[i - 1] != str[i - 1 + len];
			diff += str[i - 1 + len] != str[i - 1 + 2 * len];
		}
		if ( diff <= bound ) 
			return true;
	}
	return false;
}

void makeAns(int len) {
	ans = "";
	int diff = 0;
	for ( int i = 0; i + 2 * len - 1 < (int)str.length(); i ++ ) {
		if ( i == 0 ) {
			diff = 0;
			for ( int k = 0; k < len; k ++ )
				diff += str[i + k] != str[i + len + k];
		} else {
			diff -= str[i - 1] != str[i - 1 + len];
			diff += str[i - 1 + len] != str[i - 1 + 2 * len];
		}
		if ( diff <= bound ) {
			string ts = str.substr(i, 2 * len);
			if ( ans == "" || ans > ts )
				ans = ts;
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	cin >> bound;
	cin >> cyc;
	str = cyc + cyc;
	int lim = cyc.length() / 2;
	for ( int len = lim; len >= 1; len -- ) 
		if ( check(len) ) {
			makeAns(len);
			cout << ans << '\n';
			return 0;
		}
	cout << '\n';
}
