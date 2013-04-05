#include <cstdio>
#include <cstring>
#include <cstdlib>
typedef long long ll;
const int BASE = 99991;
const int kMod = 1000000007;
const int kLenMax = 400005;
int n, d, powD, kInv;
char str[kLenMax], cur[kLenMax];

inline int plus(int a, int b) {
	return (a + b) % kMod;
}

inline int minus(int a, int b) {
	a -= b;
	if ( a < 0 ) a += kMod;
	return a;
}

inline int mul(int a, int b) {
	return (ll)a*b%kMod;
}

int powMod(int a, int n) {
	int res = n & 1 ? a : 1;
	for ( n >>= 1; n; n >>= 1 ) {
		a = mul(a, a);
		if ( n & 1 )
			res = mul(res, a);
	}
	return res;
}

void dfs(int i, int s1, int s2, bool cling) {
	if ( i == n ) {
		printf("%s\n", cur);
		exit(0);
	}
	for ( int a = cling?str[i]:'a'; a <= 'z'; a ++ ) {
		if ( (i-d+1<0 || plus(mul(s1,BASE),a) != plus(s2,mul(powD,a)))
		  && (i-d<0 || plus(mul(cur[i-d],mul(powD,BASE)),plus(mul(s1,BASE),a)) 
			  != plus(cur[i-d],mul(BASE,plus(s2,mul(powD,a))))) ) {
			cur[i] = (char)a;
			dfs(i+1, minus(plus(mul(s1,BASE),a),i-d+1>=0?mul(powD,cur[i-d+1]):0), 
					mul(plus(minus(s2,(i-d+1>=0?cur[i-d+1]:0)),mul(powD,a)),kInv),
					cling&&a==str[i]);
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &d);
	scanf("%s", str);
	n = strlen(str);
	int t;
	for ( t = n-1; t >= 0 && str[t] == 'z'; t -- );
	if ( t == -1 ) {
		printf("Impossible\n");
		return 0;
	}
	str[t]++;
	for ( int i = t+1; i < n; i ++ ) 
		str[i] = 'a';
	powD = powMod(BASE, d-1);
	kInv = powMod(BASE, kMod-2);
	dfs(0, 0, 0, 1);
	printf("Impossible\n");
}
