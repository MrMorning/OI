#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f;

struct Info{

	//f[i][j][b]
	//i: digits unknown, 
	//j: The number of lucky digits needed, 
	//b: close to upperlim or not
	//c: all zeros?
	
	int memo[11][10][2][2];
	bool done[11][10][2][2];
	int dig[11], n_dig;
	int ori;

	int f(int i, int j, bool b, bool c = true) {
		if ( j < 0 )
			return 0;

		if ( done[i][j][b][c] )
			return memo[i][j][b][c];
		done[i][j][b][c] = true;
		int &res = memo[i][j][b][c] = 0;

		if ( i == 0 )
			return res = (j == 0 && !c);
		for ( int x = 0; x <= (b ? dig[i - 1] : 9); x ++ )
			res += f(i - 1, j - (x == 4 || x == 7), b ? x == dig[i - 1] : false, c && (x == 0));
		return res;
	}

	void init(int lim) {
		ori = lim;
		n_dig = 0;
		while ( lim ) {
			dig[n_dig ++] = lim % 10;
			lim /= 10;
		}
		memset(done, 0, sizeof(done));
	}
} M_info;

int N, M, K;
int C[55], ans[55];
int dp[55][10];

int count_lucky(int x) {
	int res = 0;
	while ( x ) {
		res += x % 10 == 4 || x % 10 == 7;
		x /= 10;
	}
	return res;
}


int search(int s, int k) {
	//The kth number of x's satisfying F(x) \in s
	//s is in binary composition
	
	int got = 0;
	bool b = true, c = true;
	int res = 0;

	for ( int i = M_info.n_dig - 1; i >= 0; i -- ) {

		for ( int x = 0; ; x ++ ) {
			int cnt = 0, nxt_got = got + (x == 4 || x == 7);
			bool b2 = b && (x == M_info.dig[i]),
				 c2 = c && (x == 0);
			for ( int t = 0; t <= 9; t ++ )
				if ( s & (1 << t) )
					if ( t - nxt_got >= 0 )
						cnt = min(cnt + M_info.f(i, t - nxt_got, b2, c2), k);

			if ( cnt >= k ) {
				got = nxt_got;
				b = b2;
				c = c2;
				res = res * 10 + x;
				break;
			}

			k -= cnt;
		}
	}
	return res;
}
int calc_link(int s, int i, int it) {
	static Info I;

	I.init(it);

	int res = 0;
	for ( int t = 0; t <= 9; t ++ )
		if ( s & (1 << t) ) {
			if ( i == N )
				res = min(inf, res + I.f(I.n_dig, t, true));
			else
				for ( int t2 = 0; t2 <= 9; t2 ++ ) 
					if ( (C[i] && t == t2) || (!C[i] && t != t2) )
						res = (int)min((ll)inf, res + (ll)I.f(I.n_dig, t, true) * dp[i + 1][t2]);
		}
	return res;
}
void work() {
	scanf("%d%d%d", &N, &M, &K);
	M_info.init(M);

	for ( int i = 1; i <= N - 1; i ++ )
		scanf("%d", &C[i]);

	//perform a DP on C
	memset(dp, 0, sizeof(dp));
	for ( int t = 0; t <= 9; t ++ )
		dp[N][t] = M_info.f(M_info.n_dig, t, true);
	for ( int i = N; i >= 2; i -- ) 
		for ( int t = 0; t <= 9; t ++ ) 
			for ( int t2 = 0; t2 <= 9; t2 ++ ) {
				if ( (C[i - 1] && t == t2) || (!C[i - 1] && t != t2) )
					dp[i - 1][t2] = (int)min((ll)inf, dp[i - 1][t2] + (ll)M_info.f(M_info.n_dig, t2, true) * dp[i][t]);
			}

	bool fail = false;
	for ( int i = 1; i <= N; i ++ ) {
		int s;
		if ( i == 1 )
			s = (1 << 10) - 1;
		else {
			int t = count_lucky(ans[i - 1]);
			if ( C[i - 1] )
				s = 1 << t;
			else
				s = (1 << 10) - 1 - (1 << t);
		}

		int tot = 0;
		for ( int t = 0; t <= 9; t ++ )
			if ( s & (1 << t) )
				tot += M_info.f(M_info.n_dig, t, true);	
		int lb = 0, rb = tot;

		for ( int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 ) {
			if ( calc_link(s, i, search(s, mid)) >= K ) 
				rb = mid;
			else
				lb = mid;
		}

		if ( calc_link(s, i, search(s, rb)) >= K ) {
			ans[i] = search(s, rb);
			if ( rb > 1 )
				K -= calc_link(s, i, search(s, rb - 1));
		} else {
			fail = true;
			break;
		}
	}
	if ( fail )
		printf("-1\n");
	else {
		for ( int i = 1; i <= N; i ++ ) 
			printf("%d ", ans[i]);
		printf("\n");
	}
}

int main() {
	int TST;

	scanf("%d", &TST);
	while ( TST -- )
		work();
}
