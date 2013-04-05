#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

bool done[10][7][5][3][3][82];
int memo[10][7][5][3][3][82];
int POW[11][10];

int count_bits(int x) {
	int res = 0;
	while ( x ) {
		res += x & 1;
		x >>= 1;
	}
	return res;
}

int dp(int m, int a1, int a2, int a3, int a4, int s) {
	if ( done[m][a1][a2][a3][a4][s] )
		return memo[m][a1][a2][a3][a4][s];
	done[m][a1][a2][a3][a4][s] = true;
	int &res = memo[m][a1][a2][a3][a4][s] = 0;
	if ( m == 0 ) 
		return res = (POW[2][a1] * POW[3][a2] * POW[5][a3] * POW[7][a4] % s == 0);

	res += dp(m - 1, a1, a2, a3, a4, s + 1); //1
	res += dp(m - 1, min(a1 + 1, 6), a2, a3, a4, s + 2); //2
	res += dp(m - 1, a1, min(a2 + 1, 4), a3, a4, s + 3); //3
	res += dp(m - 1, min(a1 + 2, 6), a2, a3, a4, s + 4); //4
	res += dp(m - 1, a1, a2, min(a3 + 1, 2), a4, s + 5); //5
	res += dp(m - 1, min(a1 + 1, 6), min(a2 + 1, 4), a3, a4, s + 6); //6
	res += dp(m - 1, a1, a2, a3, min(a4 + 1, 2), s + 7); //7
	res += dp(m - 1, min(a1 + 3, 6), a2, a3, a4, s + 8); //8
	res += dp(m - 1, a1, min(a2 + 2, 4), a3, a4, s + 9); //9

	return res;
}

void init() {
	POW[2][0] = POW[3][0] = POW[5][0] = POW[7][0] = POW[9][0] = POW[10][0] = 1;
	for ( int i = 1; i <= 9; i ++ ) {
		POW[2][i] = POW[2][i - 1] * 2;
		POW[3][i] = POW[3][i - 1] * 3;
		POW[5][i] = POW[5][i - 1] * 5;
		POW[7][i] = POW[7][i - 1] * 7;
		POW[9][i] = POW[9][i - 1] * 9;
		POW[10][i] = POW[10][i - 1] * 10;
	}
}

void change(int &a1, int &a2, int &a3, int &a4, int &s, int x) {
	if ( x == 1 ) {
		s += 1;
	} else if ( x == 2 ) {
		s += 2;
		a1 = min(a1 + 1, 6);
	} else if ( x == 3 ) {
		s += 3;
		a2 = min(a2 + 1, 4);
	} else if ( x == 4 ) {
		s += 4;
		a1 = min(a1 + 2, 6);
	} else if ( x == 5 ) {
		s += 5;
		a3 = min(a3 + 1, 2);
	} else if ( x == 6 ) {
		s += 6;
		a1 = min(a1 + 1, 6);
		a2 = min(a2 + 1, 4);
	} else if ( x == 7 ) {
		s += 7;
		a4 = min(a4 + 1, 2);
	} else if ( x == 8 ) {
		s += 8;
		a1 = min(a1 + 3, 6);
	} else if ( x == 9 ) {
		s += 9;
		a2 = min(a2 + 2, 4);
	}
}

int calc(int num) { //how many pds equal or smaller than num
	static int dig[11];

	num ++;
	int ori = num;


	int tmp = num, n_dig = 0;
	while  ( tmp ) {
		dig[n_dig ++] = tmp % 10;
		tmp /= 10;
	}
	//get rid of buzzing zeroes
	int p = -1;
	for ( int i = n_dig - 2; i >= 0; i -- )
		if ( dig[i] == 0 ) {
			p = i;
			break;
		}
	if ( p != -1 ) {
		num = num / POW[10][p + 1];
		for ( int i = p; i >= 0; i -- ) {
			dig[i] = 1;
			num = num * 10 + 1;
		}
	}

	int res = ori - num;

	//ignore zero first
	for ( int i = 1; i < n_dig; i ++ )
		res += dp(i, 0, 0, 0, 0, 0);
	int s = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0;
	for ( int i = n_dig - 1; i >= 0; i -- ) {
		for ( int x = 1; x < dig[i]; x ++ ) {
			int ts = s, t1 = a1, t2 = a2, t3 = a3, t4 = a4;

			change(a1, a2, a3, a4, s, x);

			res += dp(i, a1, a2, a3, a4, s);

			s = ts, a1 = t1, a2 = t2, a3 = t3, a4 = t4;
		} 

		change(a1, a2, a3, a4, s, dig[i]);
	}

	//consider numbers containing zero
	for ( int i = 2; i < n_dig; i ++ )
		res += 9 * POW[10][i - 1] - POW[9][i];
	for ( int i = n_dig - 1; i >= 0; i -- ) {
		for ( int x = (i == n_dig - 1) ? 1 : 0; x < dig[i]; x ++ ) {
			if ( x == 0 )
				res += POW[10][i];
			else
				res += POW[10][i] - POW[9][i];
		}
	}

	return res;
}

int main() {
	int N;

	init();
	while ( scanf("%d", &N), N ) {
		int lb = 0, rb = 2000000000;
		for ( int mid = ((ll)lb + rb) / 2; lb < rb - 1;
				mid = ((ll)lb + rb) / 2 ) 
			if ( calc(mid) >= N )
				rb = mid;
			else
				lb = mid;
		printf("%d\n", rb);
	}
}
