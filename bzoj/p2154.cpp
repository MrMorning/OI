#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 10000010;
const int MOD = 20101009;
bool not_prime[N_MAX];
int prime[N_MAX], coef[N_MAX], sum[N_MAX];
int prime_cnt;
void init() {
	for ( int x = 2; x < N_MAX; x ++ ) {
		if ( ! not_prime[x] ) {
			coef[x] = -1;
			prime[prime_cnt ++] = x;
		}

		for ( int upper = (N_MAX - 1) / x, i = 0; prime[i] <= upper; i ++ ) {
			int y = x * prime[i];
			not_prime[y] = true;
			if ( x % prime[i] == 0 ) {
				coef[y] = 0;
				break;
			} else
				coef[y] = coef[x] * -1;
		}
	}
	coef[1] = 1;
	for ( int x = 1; x < N_MAX; x ++ ) {
		coef[x] = ((ll)x * x % MOD * coef[x] + MOD) % MOD;
		sum[x] = ((ll)sum[x - 1] + coef[x]) % MOD;
	}
}

struct Segment {
	int l, r, x, y;
	Segment(int _l, int _r, int _x, int _y):
		l(_l), r(_r), x(_x), y(_y) {}
};
vector<int> split(int n) {
	vector<int> res;
	int lim = (int)sqrt(n);
	for ( int x = 1; x <= lim; x ++ )
		res.push_back(x + x + 1);
	for ( int k = 1; k <= lim; k ++ )
		res.push_back(n / k + n / k + 1);
	sort(res.begin(), res.end());
	res.resize(unique(res.begin(), res.end()) - res.begin());
	return res;
}
vector<int> split(int n, int m) {
	vector<int> res1 = split(n), res2 = split(m);
	vector<int> res(res1.size() + res2.size() + 1);
	res[0] = 1;
	merge(res1.begin(), res1.end(),
			res2.begin(), res2.end(), res.begin() + 1);
	res.resize(unique(res.begin(), res.end()) - res.begin());
	return res;
}

ll solve(int n, int m) {
	vector<int> tmp = split(n, m);
	ll res = 0;
	for ( int i = 0, sz = tmp.size(); i < sz - 1; i ++ ) {
		int st = (tmp[i] + 1) / 2, en = (tmp[i + 1] - 1) / 2;
		ll k = (sum[en] - sum[st - 1] + MOD) % MOD;
		ll kn = (ll)(n / st) * (n / st + 1) / 2 % MOD;
		ll km = (ll)(m / st) * (m / st + 1) / 2 % MOD;
		res += k * kn % MOD * km % MOD;
		res %= MOD;
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> tmp = split(n, m);
	ll res = 0;
	for ( int i = 0, sz = tmp.size(); i < sz - 1; i ++ ) {
		int st = (tmp[i] + 1) / 2, en = (tmp[i + 1] - 1) / 2;
		ll k = (ll)(en + st) * (en - st + 1) / 2 % MOD;
		res += k * solve(n / st, m / st) % MOD;
		res %= MOD;
	}
	printf("%lld\n", res);
}
