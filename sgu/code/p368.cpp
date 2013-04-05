#include <cstdio>
char s1[111], s2[111];
int n, m;
int a[111], b[111];
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= m; i ++ )
		scanf("%d", &a[i]);
	scanf("\n");
	bool ac = false;
	for ( int i = 1; i <= n; i ++ ) {
		gets(s1);
		int k;
		scanf("%d\n", &k);
		for ( int j = 1; j <= k; j ++ )
			scanf("%d", &b[j]);
		int score = 0;
		for ( int j = 1; j <= k; j ++ ) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			if ( a[b[j]] < x ) score += 2;
			else if ( a[b[j]] < y ) score += 3;
			else if ( a[b[j]] < z ) score += 4;
			else score += 5;
		}
		scanf("%d\n", &k);
		while ( k -- ) {
			gets(s2);
			int req;
			scanf("%d\n", &req);
			if ( score >= req ) {
				ac = true;
				printf("%s %s\n", s1, s2);
			}
		}
	}
	if ( !ac )
		printf("Army\n");
}
