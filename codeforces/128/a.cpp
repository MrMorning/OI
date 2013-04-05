#include <cstdio>

int main() {
//	freopen("t.in", "r", stdin);
	int x, t, a, b, da, db;
	scanf("%d%d%d%d%d%d", &x, &t, &a, &b, &da, &db);
	bool suc = x == 0;
	for ( int i = 0; i < t; i ++ ) 
		for ( int j = 0; j < t; j ++ ) {
			if ( x == (a - da * i) + (b - db * j) )
				suc = true;
			if ( x == (a - da * i) )
				suc = true;
			if ( x == (b - db * j) )
				suc = true;
		}
	printf("%s\n", suc ? "YES" : "NO");
}
