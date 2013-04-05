#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#include <cassert>
using namespace std;
typedef long long ll;

const int BRUTE_LIM = 1800;

int N, M, P;
int X[20010], Y[20010];
vector<pair<int, int> > out;

inline int eval(int x, int y) {
	return X[x] + Y[y] >= P ? (X[x] + Y[y]) % P : X[x] + Y[y];
}

void solve_small(int x1, int y1, int x2, int y2) {
	static ll f[BRUTE_LIM][BRUTE_LIM];
	static int way[BRUTE_LIM][BRUTE_LIM];
	static stack<pair<int, int> > stk;
	int n = x2 - x1 + 1, m = y2 - y1 + 1, des = n + m - 2;
	f[0][0] = eval(x1, y1);
	for ( int k = 1; k <= des; k ++ )
		for ( int i = max(0, k - m + 1); i <= min(n - 1, k); i ++ ) {
			int j = k - i;
			f[k][i] = 0;
			if ( i >= 1 ) {
				f[k][i] = f[k - 1][i - 1];
				way[k][i] = 0;
			}
			if ( j - 1 >= 0 ) {
				if ( f[k - 1][i] >= f[k][i] ) {
					f[k][i] = f[k - 1][i];
					way[k][i] = 1;
				}
			}
			f[k][i] += eval(i + x1, j + y1);
		}
	int last_k = des, last_x = n - 1;
	while ( 1 ) {
		int s = way[last_k][last_x];
		if ( s == 0 )
			last_x --;
		last_k --;
		if ( last_k == 0 )
			break;
		stk.push(make_pair(last_k + x1 + y1, last_x + x1));
	}	
	while ( stk.size() ) {
		out.push_back(stk.top());
		stk.pop();
	}
}

void solve(int x1, int y1, int x2, int y2) {
	static ll f[2][20010], g[2][20010];
	int n = x2 - x1 + 1, m = y2 - y1 + 1;
	if ( n * m == 2 )
		return;
	if ( n + m - 1 < BRUTE_LIM ) {
		solve_small(x1, y1, x2, y2);
		return;
	}
	int des = x1 + y1 + (n + m - 2) / 2;
	f[(x1 + y1) & 1][x1] = eval(x1, y1);
	for ( int k = x1 + y1 + 1; k <= des; k ++ ) 
		for ( int i = max(x1, k - y2), lim = min(x2, k - y1); i <= lim; i ++ ) {
			int j = k - i;
			f[k & 1][i] = 0;
			if ( i - 1 >= x1 )
				f[k & 1][i] = f[(k - 1) & 1][i - 1];
			if ( j - 1 >= y1 )
				f[k & 1][i] = max(f[k & 1][i], f[(k - 1) & 1][i]);
			f[k & 1][i] += eval(i, j);
		}
	g[(x2 + y2) & 1][x1] = eval(x2, y2);
	for ( int k = x2 + y2 - 1; k >= des; k -- ) 
		for ( int i = max(x1, k - y2), lim = min(x2, k - y1); i <= lim; i ++ ) {
			int j = k - i;
			g[k & 1][i] = 0;
			if ( i + 1 <= x2 )
				g[k & 1][i] = g[(k + 1) & 1][i + 1];
			if ( j + 1 <= y2 )
				g[k & 1][i] = max(g[k & 1][i], g[(k + 1) & 1][i]);
			g[k & 1][i] += eval(i, j);
		}
	int note;
	ll best = -1;
	for ( int i = x1; i <= x2; i ++ ) {
		int j = des - i;
		if ( y1 <= j && j <= y2 ) {
			ll val = f[des & 1][i] + g[des & 1][i] - eval(i, des - i);
			if ( val > best ) {
				best = val;
				note = i;
			}
		}
	}
	solve(x1, y1, note, des - note);
	out.push_back(make_pair(des, note));
	solve(note, des - note, x2, y2);
}

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> N >> M >> P;
	for ( int i = 0; i < N; i ++ )
		cin >> X[N - i - 1];
	for ( int j = 0; j < M; j ++ )
		cin >> Y[M - j - 1];
	if ( N == M && N == 1 ) {
		cout << eval(0, 0) << '\n' << '\n';
		return 0;
	}	
	out.push_back(make_pair(0, 0));
	solve(0, 0, N - 1, M - 1);
	out.push_back(make_pair(N + M - 2, N - 1));
	ll res = 0;
	for ( int i = 0, sz = out.size();
			i < sz; i ++ ) 
		res += eval(out[i].second, out[i].first - out[i].second);
	cout << res << '\n';
	return 0;
	for ( int sz = out.size(), i = sz - 2; i >= 0; i -- ) {
		if ( out[i].second == out[i + 1].second )
			cout << 'S';
		else
			cout << 'C';
	}
}
