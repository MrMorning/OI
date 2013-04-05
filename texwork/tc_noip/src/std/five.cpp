#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;
typedef long long ll;

map<ll, bool> mp;
int w[55][55], f[55];


class CuttingBitString {
public:
	bool ok(string s) {
		int h = s.length();
		if ( s[0] == '0' ) return false;
		ll t = 0;
		for ( int i = 0; i < h; i ++ ) {
			t += (s[i]-'0') * (1LL<<(h-i-1));
		}
		return mp.count(t);
	}

	int getmin(string S) {
		for ( ll x = 1; x < (1LL << 50); x *= 5 )
			mp[x] = true;
		int len = S.length();
		memset(w, 0, sizeof(w));
		for ( int i = 0; i < len; i ++ )
			for ( int j = i; j < len; j ++ )
				w[i][j] = ok(S.substr(i, j-i+1));
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		for ( int i = 0; i < len; i ++ )
			for ( int j = 0; j <= i; j ++ )
				if ( w[j][i] )
					f[i+1] = min(f[i+1], f[j]+1);
		if ( f[len] <= len ) return f[len];
		return -1;
	}
} cls;

int main() {
	freopen("five.in", "r", stdin);
	freopen("five.out", "w", stdout);
	string str;
	cin >> str;
	cout << cls.getmin(str);
}
