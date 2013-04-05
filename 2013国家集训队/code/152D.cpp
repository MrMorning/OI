#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define ASSERT(xx,yy) \
	if ( bd[xx][yy] != '#' ) return false; \
	else if ( tag[xx][yy] != stamp ) { \
		tag[xx][yy] = stamp; \
		cnt++; \
	}

const int kSelMax = 6;
pair<int, int> a[kSelMax+10], b[kSelMax+10];
int n, m, na, nb, tot;
int tag[1005][1005];
char bd[1005][1005];
int disX[1005*1005], disY[1005*1005], nDisX, nDisY;

void output(int i1, int j1, int i2, int j2) {
	puts("YES");
	printf("%d %d %d %d\n", a[i1].first, a[i1].second,
			b[j1].first, b[j1].second);
	printf("%d %d %d %d\n", a[i2].first, a[i2].second,
			b[j2].first, b[j2].second);
}
bool check(int i1, int j1, int i2, int j2) {
	if (! (b[j1].first-a[i1].first>=2&&b[j1].second-a[i1].second>=2
			&&b[j2].first-a[i2].first>=2&&b[j2].second-a[i2].second>=2) )
		return false;
	static int stamp = 0;
	stamp++;
	int cnt = 0;
	for ( int x = a[i1].first; x <= b[j1].first; x ++ ) {
		ASSERT(x, a[i1].second);
		ASSERT(x, b[j1].second);
	}
	for ( int y = a[i1].second; y <= b[j1].second; y ++ ) {
		ASSERT(a[i1].first, y);
		ASSERT(b[j1].first, y);
	}
	for ( int x = a[i2].first; x <= b[j2].first; x ++ ) {
		ASSERT(x, a[i2].second);
		ASSERT(x, b[j2].second);
	}
	for ( int y = a[i2].second; y <= b[j2].second; y ++ ) {
		ASSERT(a[i2].first, y);
		ASSERT(b[j2].first, y);
	}
	if (cnt==tot) {
		output(i1, j1, i2, j2);
		exit(0);
	}
	return false;
}

void crazyCheck(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4) {
	int valX[4], valY[4];
	valX[0] = x1;
	valX[1] = x2;
	valX[2] = x3;
	valX[3] = x4;
	valY[0] = y1;
	valY[1] = y2;
	valY[2] = y3;
	valY[3] = y4;

#define GET(s, i) (((s)>>(2*(i)))&3)
	for ( int s = 0, lim = (1<<16); s < lim; s ++ ) {
		a[na] = make_pair(valX[GET(s,0)], valY[GET(s,1)]);
		b[nb] = make_pair(valX[GET(s,2)], valY[GET(s,3)]);
		a[na+1] = make_pair(valX[GET(s,4)], valY[GET(s,5)]);
		b[nb+1] = make_pair(valX[GET(s,6)], valY[GET(s,7)]);
		check(na, nb, na+1, nb+1);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%s", bd[i]+1);
		for ( int j = 1; j <= m; j ++ )
			tot += bd[i][j] == '#';
	}

	for ( int i = 3; nb < kSelMax && i <= n; i ++ )
		for ( int j = 3; nb < kSelMax && j <= m; j ++ )
			if ( bd[i][j]=='#'&&bd[i-1][j]=='#'&&bd[i-2][j]=='#'
					&&bd[i][j-1]=='#'&&bd[i][j-2]=='#' )
				b[nb++] = make_pair(i, j);
	for ( int i = 1; na < kSelMax && i <= n-2; i ++ )
		for ( int j = 1; na < kSelMax && j <= m-2; j ++ )
			if ( bd[i][j]=='#'&&bd[i+1][j]=='#'&&bd[i+2][j]=='#'
					&&bd[i][j+1]=='#'&&bd[i][j+2]=='#' )
				a[na++] = make_pair(i, j);
	for ( int i = 1; i <= n; i ++ )
		for ( int j = 1; j <= m; j ++ ) {
			if ( i >= 3 &&bd[i][j]=='#'&&bd[i-1][j]=='#'&&bd[i-2][j]=='#' )
				disY[nDisY++] = j;
			if ( j >= 3 &&bd[i][j]=='#'&&bd[i][j-1]=='#'&&bd[i][j-2]=='#' )
				disX[nDisX++] = i;
		}
	sort(disX, disX+nDisX);
	nDisX=unique(disX, disX+nDisX)-disX;
	sort(disY, disY+nDisY);
	nDisY=unique(disY, disY+nDisY)-disY;
	if ( nDisX >= 4 && nDisY >= 4 )
		crazyCheck(disX[0], disX[1], disX[nDisX-2], disX[nDisX-1],
				disY[0], disY[1], disY[nDisY-2], disY[nDisY-1]);
	if ( max(na, nb) >= kSelMax ) {
		printf("NO\n");
		return 0;
	}

	for ( int i1 = 0; i1 < na; i1 ++ )
		for ( int i2 = 0; i2 < na; i2 ++ )
			for ( int j1 = 0; j1 < nb; j1 ++ )
				for ( int j2 = 0; j2 < nb; j2 ++ ) {
					check(i1, j1, i2, j2); 
				}


	printf("NO\n");
	return 0;
}
