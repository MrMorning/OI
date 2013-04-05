#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

int n_spe;
ll spe[222];

bool same_digit(ll x) {
	int t = x % 10;
	while ( x ) {
		if ( x % 10 != t )
			return false;
		x /= 10;
	}
	return true;
}	

ll extend(ll x, int M, int N) {
	int bonus = 0;
	if ( x % 5 == 0 )
		bonus += M;
	if ( same_digit(x) )
		bonus += N;
	x += bonus;
	return x;
}

ll work(ll x, int M, int N) {
	while ( 1 ) {
		while ( same_digit(x) )
			x = extend(x, M, N);
		if ( x % 5 != 0 )
			return x;
		bool found = false;
		for ( int i = 0; i < n_spe; i ++ ) 
			if ( spe[i] > x ) {
				ll delta = spe[i] - x;
				if ( delta % M == 0 ) {
					found = true;
					x = spe[i];
					break;
				}
			}
		if ( !found )
			return -1;
	}
}

ll solve(int M, int N) {
	ll res = 0;
	for ( ll x = 1; x <= 10000; x ++ ) {
		ll tmp = work(x, M, N);
		if ( tmp == -1 )
			return -1;
		res = max(res, tmp);
	}
	return res;
}

ll brute_work(ll x, int M, int N) {
	while ( 1 ) {
		ll tmp = extend(x, M, N);
		if ( tmp != x )
			x = tmp;
		else
			return x;
	}
}

ll brute(int M, int N) {
	ll res = 0;
	for ( ll x = 1; x <= 10000; x ++ ) {
		ll tmp = brute_work(x, M, N);
		res = max(res, tmp);
	}
	return res;
}

void pre_work() {
	for ( ll x = 1; x <= 9; x ++ ) {
		ll cur = x;
		while ( 1 ) {
			spe[n_spe ++] = cur;
			if ( ((ull)cur * 10 + (ull)x) >= (1ULL << 63) )
				break;
			cur = cur * 10 + x;
		}
	}
	sort(spe, spe + n_spe);
}

int main() {
	freopen("t.out", "w", stdout);
	pre_work();
	for ( int i = 1; i <= 50; i ++ )
		for ( int j = 1; j <= 50; j ++ ) {
			if ( i % 5 == 0 )
				cout << solve(i, j) << ',';
			else
				cout << brute(i, j) << ',';
		}
}
