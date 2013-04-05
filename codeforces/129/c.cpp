#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef long double val_t;
int n;
char s1[200010], s2[200010];
ll pre[200010], suf[200010], cnt[200010];
int main() {
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);

	val_t ans = 0;
	ll tot = 0;
	for ( int i = 1; i <= n; i ++ )
		tot += (ll)(n - i + 1) * (n - i + 1);

	for ( int a = 0; a < 26; a ++ ) {
		char ch = a + 'A';
		memset(pre, 0, sizeof(pre));
		memset(suf, 0, sizeof(suf));
		memset(cnt, 0, sizeof(cnt));
		for ( int i = 1; i <= n; i ++ )
			pre[i] = pre[i-1] + (s2[i]==ch?i:0);
		for ( int i = n; i >= 1; i -- ) {
			suf[i] = suf[i+1] + (s2[i]==ch?i:0);
			cnt[i] = cnt[i+1] + (s2[i]==ch);
		}
		for ( int i = 1; i <= n; i ++ ) 
			if ( s1[i]==ch ) {
				ll tmp = 0;
				tmp += pre[i]*(n-i+1);
				if ( suf[i+1] > 0 )
					tmp += (ll)(n+1)*i*cnt[i+1] - i*suf[i+1];
				ans += (val_t)tmp / tot;
			}
	}
	cout << setprecision(15) << setiosflags(ios::fixed) << ans;
}
