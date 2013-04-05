#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int N_MAX = 100010;
int X[N_MAX], R, L;
ll sum[N_MAX], B;

ll get_sum(int l, int r) {
	return sum[r] - sum[l - 1];
}

bool check(int l, int r) {
	int mid = (l + r) >> 1;
	ll val = (ll)X[mid] * (mid - l + 1) - get_sum(l, mid);
	val += get_sum(mid + 1, r) - (ll)X[mid] * (r - mid);
	return val <= B;
}

int main() {
	freopen("t.in", "r", stdin);
	cin >> R >> L >> B;
	for ( int i = 1; i <= R; i ++ ) {
		cin >> X[i];
		sum[i] = sum[i - 1] + X[i];
	}
	int res = 0;
	for ( int p = 1, q = 1; p <= R; p ++ ) {
		q = max(p, q);
		while ( q + 1 <= R && check(p, q + 1) )
			q ++;
		res = max(res, q - p + 1);
	}
	cout << res;
}
