#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long ll;

const int PRIME[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
const int INTERV[5][2] = {{0, 8}, {9, 13}, {14, 18}, {19, 22}, {23, 24}};
const int N_MAX = 10000;
vector<int> f[15][5];
int COMP[5];
int size[15], len[15];
int int_pow[18][20];
int n, m;
ll a[N_MAX];

int get(int b, int x, int i) {
	return x / int_pow[b][i] % b;
}

int main() {
	//freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	for ( int i = 0; i < 5; i ++ ) {
		int acc = 1;
		for ( int k = INTERV[i][0]; k <= INTERV[i][1]; k ++ )
			acc *= PRIME[k];
		COMP[i] = acc;
	}


	cin >> n;
	for ( int b = 0; b < 15; b ++ ) 
		len[b] = (int)floor(log(n) / log(b + 2)) + 1;

	for ( int b = 1; b <= 17; b ++ ) {
		int_pow[b][0] = 1;
		for ( int i = 1; i < 20; i ++ )
			int_pow[b][i] = int_pow[b][i - 1] * b;
	}

	for ( int b = 0; b < 15; b ++ ) 
		size[b] = int_pow[b + 3][len[b]];
	for ( int b = 0; b < 15; b ++ ) 
		for ( int p = 0; p < 5; p ++ )
			f[b][p] = vector<int>(size[b], 1);
	for ( int i = 0; i < n; i ++ ) {
		cin >> a[i];
		for ( int b = 0; b < 15; b ++ ) {
			int x = 0;
			for ( int t = len[b] - 1; t >= 0; t -- ) {
				x *= b + 2 + 1;
				x += get(b + 2, i, t);
			}
			for ( int p = 0; p < 5; p ++ )
				f[b][p][x] = a[i] % COMP[p];
		}
	}
	for ( int b = 0; b < 15; b ++ )
		for ( int p = 0; p < 5; p ++ )
			for ( int msk = 0; msk < size[b]; msk ++ ) {
				for ( int t = 0; t < len[b]; t ++ )
					if ( get(b + 2 + 1, msk, t) == b + 2 ) {
						for ( int x = 0; x < b + 2; x ++ ) {
							int tmp = msk - (b + 2) * int_pow[b + 2 + 1][t];
							tmp += x * int_pow[b + 2 + 1][t];
							f[b][p][msk] = (ll)f[b][p][msk] * f[b][p][tmp] % COMP[p];
						}
						break;
					}
			}
	cin >> m;
	while ( m -- ) {
		int b;
		ll c;
		char s[33];
		cin >> b >> s >> c;
		b -= 2;
		int sl = strlen(s);
		if ( sl > len[b] ) {
			bool invalid = false;
			for ( int i = 0; i < sl - len[b]; i ++ )
				if ( s[i] != '?' && s[i] != '0' ) {
					invalid = true;
					break;
				}
			if ( invalid ) {
				bool found = false;
				for ( int i = 0; i < 25; i ++ )
					if ( c % PRIME[i] == 0 ) {
						found = true;
						cout << PRIME[i] << '\n';
					}
				if ( !found )
					cout << -1 << '\n';
				continue;
			} else {
				memcpy(s, s + sl - len[b], sizeof(char) * len[b]);
				sl = len[b];
			}
		}

		int pat = 0;
		for ( int i = 0; i < sl; i ++ ) {
			int x;
			if ( isdigit(s[i]) )
				x = s[i] - '0';
			else if ( isalpha(s[i]) )
				x = s[i] - 'A' + 10;
			else {
				assert(s[i] == '?');
				x = b + 2;
			}
			pat *= b + 2 + 1;
			pat += x;
		}
		
		bool found = false;
		for ( int p = 0; !found && p < 5; p ++ ) 
			for ( int k = INTERV[p][0]; k <= INTERV[p][1]; k ++ ) {
				ll res = c % PRIME[k];
				res += f[b][p][pat];
				res %= PRIME[k];
				if ( res == 0 ) {
					found = true;
					cout << PRIME[k] << '\n';
					break;
				}
			}
		if ( !found ) 
			cout << -1 << '\n';
	}
}
