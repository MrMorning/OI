#include <cstdio>
#include <cstring>

#define maxn 200005
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
LL sum[2][maxn][26];
char s[2][maxn];
int n;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s%s", s[0], s[1]);
	for ( int i = 0; i < 2; i ++ )
		for ( int j = n - 1; j >= 0; j -- ) {
			for ( int k = 0; k < 26; k ++ )
				sum[i][j][k] = sum[i][j+1][k];
			sum[i][j][s[i][j]-'A'] += n-j;
		}
	double ans = 0;
	for ( int i = 0; i < 2; i ++ )
		for ( int j = 0; j < n; j ++ ) {
			if ( i == 0 )
				ans += sum[i^1][j][s[i][j]-'A']*(j+1);
			else
				ans += sum[i^1][j+1][s[i][j]-'A']*(j+1);
		}
	double z = 0;
	for ( int i = 1; i <= n; i ++ )
		z += sqr((n-i+1)*1.0);
	printf("%.8lf\n", ans/z);
}
