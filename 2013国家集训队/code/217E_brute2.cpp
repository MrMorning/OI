#include <cstdio>
#include <cstring>
int n, k;
char str[3000010];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str+1);
	scanf("%d", &k);
	scanf("%d", &n);
	while ( n -- ) {
		int l, r;
		scanf("%d%d", &l, &r);
		memmove(str+r+1+(r-l+1), str+r+1, strlen(str+1)-r);
		for ( int t = 0; t < (r-l+1)/2; t++ )
			str[r+1+t] = str[l+1+t*2];
		for ( int t = 0; t < (r-l+2)/2; t++ )
			str[r+1+(r-l+1)/2+t] = str[l+t*2];
		//fprintf(stderr, "%s\n", str+1);
	}
	for ( int i = 1; i <= k; i ++ )
		printf("%c", str[i]);
}
