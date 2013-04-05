#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kInf = 0x3f3f3f3f;
const int kDigMax = 100000;
const int kBase = 10;
int f[kDigMax][2], a[kDigMax], m;
char str[kDigMax];
int B;

void upd(int &a, int b) {
	a = min(a, b);
}

struct Bigint {
	int num[kDigMax], len;
	Bigint(){}
	Bigint(char *s, int n) {
		len = n;
		for ( int i = 0; i < n; i ++ )
			num[i] = s[n-i-1]-'0';
	}
	int mod(int B) {
		int res = 0;
		for ( int i = len-1; i >= 0; i -- )
			res = (res*kBase+num[i]) % B;
		return res;
	}
	void operator/= (int k) {
		int acc = 0;
		bool first = true;
		for ( int i = len-1; i >= 0; i -- ) {
			acc = acc*kBase+num[i];
			if ( acc >= k ) {
				first = false;
				num[i] = acc / k;
				acc %= k;
			} else {
				num[i] = 0;
				if ( first ) len--;
			}
		}
	}
} A;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	scanf("%d", &B);
	if ( B == 1 ) {
		puts(str);
		return 0;
	}
	int n = strlen(str);
	A = Bigint(str, n);
	while ( A.len != 0 ) {
		a[++m] = A.mod(B);
		A /= B;
	}
	memset(f, 0x3f, sizeof(f));
	f[m][0] = 0;
	f[m][1] = 1;
	for ( int i = m; i >= 1; i-- ) 
		for ( int d = 0; d <= 1; d ++ ) 
			if ( f[i][d] != kInf ) {
				int x = a[i]-d*B;
				if ( -B < x && x < B ) 
					upd(f[i-1][0], f[i][d]+abs(x));
				x++;
				if ( -B < x && x < B ) 
					upd(f[i-1][1], f[i][d]+abs(x));
			}
	printf("%d\n", f[0][0]);
}
