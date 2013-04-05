#include <cstdio>
#include <bitset>
using namespace std;
const int kLenMax = 100010;
char input[kLenMax];

int dp(int n, int s1, int s2) {
	if ( s1 == 0 && s2 == 0 ) return n & 1;
	if ( s1 == 0 || s2 == 0 ) return n;
	if ( s1 == s2 ) return 1;
	return 0;
}

int main() {
	int n;
	scanf("%d", &n);
	scanf("%s", input + 1);
	input[0] = input[n + 1] = '0';
	int res = 0;
	for ( int i = 1; i <= n; i ++ ) 
		if ( input[i] == '0' ) {
			int st = i;
			while ( i + 1 <= n && input[i + 1] == '0' )
				i ++;
			int en = i;
			res ^= dp(en - st + 1, input[st - 1] - '0', input[en + 1] - '0');
		}
	printf("%s", res ? "FIRST" : "SECOND");
}
