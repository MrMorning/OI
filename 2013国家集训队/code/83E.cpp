#include <cstdio>
#include <cstring>
#include <cassert>
const int kInf = 0x3f3f3f3f;
int len, n;
int msk[200010];
int mem[21][1<<20];
int f[200010], s[200010];
int conv(char *s) {
	int res = 0;
	for ( int i = 0; i < len; i ++ )
		res = (res<<1)+(s[i]-'0');
	return res;
}
int g(int i, int j) {
	int p = msk[i], q = msk[j];
	for ( int i = len; i >= 0; i -- )
		if ( (p&((1<<i)-1))==(q>>(len-i)) ) return i;
	assert(0);
}
inline void upd(int &x, int y) {
	if ( y < x ) x = y;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ ) {
		static char ts[22];
		scanf("%s", ts);
		len = strlen(ts);
		msk[i] = conv(ts);
	}
	for ( int i = 2; i <= n; i ++ ) 
		s[i] = s[i-1] + g(i-1, i);
	memset(mem, 0x3f, sizeof(mem));
	mem[0][0] = 0;
	for ( int i = 1; i <= n; i ++ ) {
		f[i] = kInf;
		if ( i < n ) {
			for ( int l = 0; l <= len; l ++ ) {
				int tmp = mem[l][msk[i+1]>>(len-l)];
				if ( tmp != kInf )
					upd(f[i], tmp+i*len-s[i]-l);
			}
			for ( int l = 0; l <= len; l ++ )
				upd(mem[l][msk[i]&((1<<l)-1)], f[i]+s[i+1]-i*len);
		} else {
			f[i] = mem[0][0]+i*len-s[i];
		}
	}
	printf("%d\n", f[n]);
}
