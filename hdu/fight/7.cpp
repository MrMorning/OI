#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[11][11], b[11][11], c[11][11];
bool marked[11][11];
bool check() {
	memcpy(b, a, sizeof(a));
	while ( 1 ) {
		memcpy(c, b, sizeof(b));
		memset(marked, 0, sizeof(marked));
		for ( int i = 1; i <= 8; i ++ )
			for ( int j = 1; j <= 8; j ++ ) {
				if ( c[i][j] == 0 ) continue;
				int st = j;
				while ( j + 1 <= 8 && (c[i][j + 1] == 0 || c[i][j + 1] == c[i][st]) )
					j ++;
				int cnt = 0;
				for ( int k = st; k <= j; k ++ )
					if ( c[i][k] > 0 )
						cnt ++;
				if ( cnt >= 3 ) 
					for ( int k = st; k <= j; k ++ )
						if ( c[i][k] > 0 )
							marked[i][k] = true;
			}
		for ( int i = 1; i <= 8; i ++ )
			for ( int j = 1; j <= 8; j ++ ) {
				if ( c[j][i] == 0 ) continue;
				int st = j;
				while ( j + 1 <= 8 && (c[j + 1][i] == 0 || c[j + 1][i] == c[st][i]) )
					j ++;
				int cnt = 0;
				for ( int k = st; k <= j; k ++ )
					if ( c[k][i] > 0 )
						cnt ++;
				if ( cnt >= 3 )
					for ( int k = st; k <= j; k ++ )
						if ( c[k][i] > 0 )
							marked[k][i] = true;
			}
		bool found = false;
		for ( int i = 1; i <= 8; i ++ )
			for ( int j = 1; j <= 8; j ++ )
				if ( marked[i][j] )
					found = true;
		if ( !found ) {
			for ( int i = 1; i <= 8; i ++ )
				for ( int j = 1; j <= 8; j ++ )
					if ( c[i][j] > 0 )
						return false;
			return true;
		}
		memset(b, 0, sizeof(b));
		for ( int i = 1; i <= 8; i ++ ) {
			int n = 0;
			for ( int j = 1; j <= 8; j ++ )
				if ( c[i][j] > 0 && !marked[i][j] )
					b[i][++ n] = c[i][j];
		}
	}
}
char str[11][11];
int main() {
	freopen("t.in", "r", stdin);
	while ( 1 ) {
		memset(a, 0, sizeof(a));
		scanf("%s", str[8] + 1);
		if ( str[8][1] == '0' )
			break;
		for ( int i = 7; i >= 1; i -- )
			scanf("%s", str[i] + 1);
		for ( int i = 1; i <= 8; i ++ )
			for ( int j = 1; j <= 8; j ++ ) {
				if ( str[j][i] == '.' ) 
					a[i][j] = 0;
				else
					a[i][j] = str[j][i] - '0';
			}
		bool suc = false;
		for ( int x1 = 1; x1 <= 8; x1 ++ )
			for ( int y1 = 1; y1 <= 8; y1 ++ ) 
				for ( int x2 = 1; x2 <= 8; x2 ++ )
					for ( int y2 = 1; y2 <= 8; y2 ++ )
						if ( abs(x1 - x2) + abs(y1 - y2) == 1 ) {
							swap(a[x1][y1], a[x2][y2]);
							if ( check() )
								suc = true;
							swap(a[x2][y2], a[x1][y1]);
						}
		if ( suc )
			printf("Yes\n");
		else
			printf("No\n");
	}
}

