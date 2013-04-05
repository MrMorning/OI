
// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}

const int N_MAX = 100000;
const int POW[5] = {1, 10, 100, 1000, 10000};
vector<int> f[10], g[10][10], h[10][10][10], w[10][10][10][10];
int prime[N_MAX];
int n_prime;

int GET(int x, int i) {
	return x / POW[i - 1] % 10;
}

int solve5(int p) {
	static int mat[6][6];
	int res = 0;
	memset(mat, -1, sizeof(mat));
	for ( int j = 1; j <= 5; j ++ )
		mat[1][j] = mat[j][1] = GET(p, 5 - j + 1);
	for ( int i = 0, sz = f[mat[2][1]].size(); i < sz; i ++ ) {
		int x = f[mat[2][1]][i];
		for ( int j = 2; j <= 5; j ++ )
			mat[2][j] = mat[j][2] = GET(x, 5 - j + 1);
		for ( int k = 0, sz = g[mat[3][1]][mat[3][2]].size();
				k < sz; k ++ ) {
			int y = g[mat[3][1]][mat[3][2]][k];
			for ( int l = 3; l <= 5; l ++ )
				mat[3][l] = mat[l][3] = GET(y, 5 - l + 1);
			for ( int m = 0, sz = h[mat[4][1]][mat[4][2]][mat[4][3]].size();
					m < sz; m ++ ) {
				int z = h[mat[4][1]][mat[4][2]][mat[4][3]][m];
				for ( int n = 4; n <= 5; n ++ )
					mat[4][n] = mat[n][4] = GET(z, 5 - n + 1);
				res += w[mat[5][1]][mat[5][2]][mat[5][3]][mat[5][4]].size();
			}
		}
	}
	return res;
}

int solve4(int p) {
	static int mat[5][5];
	int res = 0;
	memset(mat, -1, sizeof(mat));
	for ( int j = 1; j <= 4; j ++ )
		mat[1][j] = mat[j][1] = GET(p, 4 - j + 1);
	for ( int i = 0, sz = g[0][mat[2][1]].size(); i < sz; i ++ ) {
		int x = g[0][mat[2][1]][i];
		for ( int j = 2; j <= 4; j ++ )
			mat[2][j] = mat[j][2] = GET(x, 4 - j + 1);
		for ( int k = 0, sz = h[0][mat[3][1]][mat[3][2]].size();
				k < sz; k ++ ) {
			int y = h[0][mat[3][1]][mat[3][2]][k];
			for ( int l = 3; l <= 4; l ++ )
				mat[3][l] = mat[l][3] = GET(y, 4 - l + 1);
			res += w[0][mat[4][1]][mat[4][2]][mat[4][3]].size();
		}
	}
	return res;
}

int solve3(int p) {
	static int mat[4][4];
	int res = 0;
	memset(mat, -1, sizeof(mat));
	for ( int j = 1; j <= 3; j ++ )
		mat[1][j] = mat[j][1] = GET(p, 3 - j + 1);
	for ( int i = 0, sz = h[0][0][mat[2][1]].size(); i < sz; i ++ ) {
		int x = h[0][0][mat[2][1]][i];
		for ( int j = 2; j <= 3; j ++ )
			mat[2][j] = mat[j][2] = GET(x, 3 - j + 1);
			res += w[0][0][mat[3][1]][mat[3][2]].size();
	}
	return res;
}

int solve2(int p) {
	static int mat[3][3];
	int res = 0;
	memset(mat, -1, sizeof(mat));
	for ( int j = 1; j <= 2; j ++ )
		mat[1][j] = mat[j][1] = GET(p, 2 - j + 1);
	res += w[0][0][0][mat[2][1]].size();
	return res;
}

void make_prime() {
	static bool not_prime[N_MAX];
	for ( int x = 2; x < N_MAX; x ++ ) 
		if ( !not_prime[x] ) {
			prime[n_prime ++] = x;
			for ( int y = x + x; y < N_MAX; y += x )
				not_prime[y] = true;
		}
}

int count_dig(int x) {
	int res = 0;
	while ( x ) {
		res ++;
		x /= 10;
	}
	return res;
}

int main(){
	//freopen("t.in", "r", stdin);
	make_prime();
	for ( int i = 0; i < n_prime; i ++ ) {
		int x = prime[i];
		f[GET(x, 5)].push_back(x);
		g[GET(x, 5)][GET(x, 4)].push_back(x);
		h[GET(x, 5)][GET(x, 4)][GET(x, 3)].push_back(x);
		w[GET(x, 5)][GET(x, 4)][GET(x, 3)][GET(x, 2)].push_back(x);
	}


	int TST, p;
	scanf("%d", &TST);
	while ( TST -- ) {
		scanf("%d", &p);
		int n_dig = count_dig(p);
		if ( n_dig == 5 )
			printf("%d\n", solve5(p));
		else if ( n_dig == 4 )
			printf("%d\n", solve4(p));
		else if ( n_dig == 3 )
			printf("%d\n", solve3(p));
		else if ( n_dig == 2 )
			printf("%d\n", solve2(p));
	}
}
