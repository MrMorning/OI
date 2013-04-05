#include <cstdio>
#include <cstring>
const int N_MAX = 100010;
const int inf = 0x3f3f3f3f;
int f[N_MAX][27];
char str[N_MAX];
bool e[27][27];
void upd(int &x, int y) {
	if ( y < x ) x = y;
}
int main() {
	scanf("%s", str);
	int n = strlen(str), m;
	scanf("%d", &m);
	while ( m -- ) {
		static char pat[4];
		scanf("%s", pat);
		e[pat[0] - 'a' + 1][pat[1] - 'a' + 1] = true;
		e[pat[1] - 'a' + 1][pat[0] - 'a' + 1] = true;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 0; i < n; i ++ ) 
		for ( int a = 0; a <= 26; a ++ )
			if ( f[i][a] != inf ) {
				upd(f[i + 1][a], f[i][a] + 1);
				if ( !e[a][str[i] - 'a' + 1] )
					upd(f[i + 1][str[i] - 'a' + 1], f[i][a]);
			}	   
	int res = inf;
	for ( int a = 0; a <= 26; a ++ )
		upd(res, f[n][a]);
	printf("%d\n", res);
}
