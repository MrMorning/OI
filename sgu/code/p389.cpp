#include <cstdio>
#include <cstring>
typedef long long ll;
const int kMod = 1000000007;
const int kNMax = 100010;

char str1[kNMax], str2[kNMax], str3[kNMax];
int fact[kNMax], invfact[kNMax];

int mul(int a, int b) {
	return (ll)a*b%kMod;
}

void add(int &a, int b) {
	a += b;
	a %= kMod;
}

int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = mul(a, a);
		if ( n & 1 )
			res = mul(res,a);
	}
	return res;
}

int bino(int n, int k) {
	if ( n < k ) return 0;
	return mul(fact[n],mul(invfact[k], invfact[n-k]));
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s%s%s", str1, str2, str3);
	int n = strlen(str1);
	fact[0] = invfact[0] = 1;
	for ( int i = 1; i <= n; i ++ ) {
		fact[i] = mul(i, fact[i-1]);
		invfact[i] = powMod(fact[i], kMod-2);
	}
	int cnt0 = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0;
	for ( int i = 0; i < n; i ++ )
		if ( str1[i] == str2[i] && str1[i] == str3[i] )
			cnt0++;
		else if ( str1[i] == str2[i] )
			cnt3++;
		else if ( str1[i] == str3[i] )
			cnt2++;
		else
			cnt1++;
	int ans = 0;
	for ( int x1 = 0; x1 <= cnt1; x1 ++ ) {
		int d = x1-(cnt1-x1);
		if ( (d+cnt2)%2 != 0 || (d+cnt3)%2 != 0 )
			continue;
		int x2 = (d+cnt2)/2, x3 = (d+cnt3)/2;
		if ( x2 < 0 || x2 > cnt2 || x3 < 0 || x3 > cnt3 )
			continue;
		add(ans, mul(bino(cnt1,x1), mul(bino(cnt2,x2), bino(cnt3,x3))));
	}
	ans = mul(ans, powMod(2, cnt0));
	printf("%d\n", ans);
}
