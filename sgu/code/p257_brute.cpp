#include <cstdio>
int P, O, S, N;
char str[5];
int info[111111];
int arr[111111];
bool found;
bool check() {
	int tp = P, to = O, ts = S;
	for ( int i = 1; i <= N; i ++ ) 
		if ( arr[i] == 0 )
			tp -= (info[i] & 1) + 1;
		else if ( arr[i] == 1 )
			to -= ((info[i] >> 1) & 1) + 1;
		else if ( arr[i] == 2 )
			ts -= ((info[i] >> 2) & 1) + 1;
	return tp <= 0 && to <= 0 && ts <= 0;
}
void dfs(int i) {
	if ( i == N + 1 ) {
		if ( check() ) 
			found = true;
		return;
	}
	for ( int t = 0; t < 3; t ++ ) {
		arr[i] = t;
		dfs(i + 1);
	}
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &P, &O, &S);
	scanf("%d", &N);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%s", str);
		info[i] = 0;
		for ( int k = 0; k < 3; k ++ )
			if ( str[k] == 'B' )
				info[i] |= 1 << k;
	}
	dfs(1);
	if ( found ) {
		printf("yeah!");
/*		for ( int i = 1; i <= N; i ++ )
			if ( out[i] == 0 )
				printf("P");
			else
				printf("%c", out[i]);
*/	} else
		printf("no solution\n");
}
