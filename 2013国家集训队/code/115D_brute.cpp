#include <cstdio>
#include <cstring>
#include <cctype>
typedef long long ll;
const int kMod = 1000003;
char str[2222], ns[2222];
bool done[2222][2222];
int memo[2222][2222];

int dp(int l, int r) {
	if ( done[l][r] ) return memo[l][r];
	done[l][r] = true;
	int &res = memo[l][r] = 0;
	if ( l == r ) 
		return res = (ns[l] == 'x');
	if ( ns[l] == '+' ) 
		res = (res+dp(l+1, r)) % kMod;
	for ( int k = l + 1; k < r; k ++ )
		if ( ns[k] == '+' || ns[k] == '*' )
			res = (res+(ll)dp(l, k-1) * dp(k+1, r)%kMod)%kMod;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str+1);
	int len = strlen(str+1), n;
	for ( int i = 1; i <= len; i ++ ) {
		if ( str[i] == '+' || str[i] == '-' )
			ns[++n] = '+';
		else if ( str[i] == '*' || str[i] == '/' )
			ns[++n] = '*';
		else {
			ns[++n] = 'x';
			while ( i+1 <= len && isdigit(str[i+1]) )
				i++;
		}
	}
	printf("%d\n", dp(1, n));
}
