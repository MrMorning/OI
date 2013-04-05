#include <cstdio>
#include <map>
#define foreach(I, C) for (__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
typedef long long ll;
const int N_MAX = 111111;
const int M_MAX = 1024;
const int MOD = 1000000007;
map<int, int> stat;
int a[N_MAX];
int N, K;
ll f[M_MAX + 1];
bool is_lucky(int x) {
	while (x) {
		if (x % 10 != 4 && x % 10 != 7)
			return false;
		x /= 10;
	}
	return true;
}
ll pow_mod(ll a, ll n) {
	a %= MOD;
	ll res = n & 1 ? a : 1;
	for (n >>= 1; n; n >>= 1) {
		a = a * a % MOD;
		if (n & 1)
			res = res * a % MOD;
	}
	return res;
}
int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	int luck_cnt = 0;
	for (int i = 1; i <= N; i ++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= N; i ++) {
		if (is_lucky(a[i])) {
			luck_cnt ++;
			if (!stat.count(a[i]))
				stat[a[i]] = 1;
			else
				stat[a[i]] ++;
		}
	}
	f[0] = 1;
	foreach (it, stat)
		for (int j = M_MAX; j >= 1; j --) {
			f[j] = (f[j] + f[j - 1] * it->second) % MOD;
		}
	int unluck_cnt = N - luck_cnt;
	ll acc = 1, res = 0;
	for (int t = 0; t <= K; t ++) {
		//choose t from unlucky numbers
		if (K - t <= M_MAX) {
			res += f[K - t] * acc % MOD;
			res %= MOD;
		}
		if (t > unluck_cnt)
			break;
		acc = acc * (unluck_cnt - t) % MOD;
		acc = acc * pow_mod(t + 1, MOD - 2) % MOD;
	}
	printf("%d\n", (int)res);
}
