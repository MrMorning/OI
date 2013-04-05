#include <cstdio>
#include <algorithm>
const int kNMax = 100010;
using namespace std;
int a[kNMax];
pair<int, int> out[kNMax][6];
int two[kNMax][6], three[kNMax][6];
int n, nOut, nTwo, nThree;
bool vis[kNMax];

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d", &n);
	for ( int i = 1; i <= n; i ++ )
		scanf("%d", &a[i]);
	for ( int i = 1; i <= n; i ++ )
		if ( !vis[i] ) {
			static int tmp[kNMax];
			int nTmp = 0;
			int cur = i;
			do {
				vis[cur] = true;
				tmp[++nTmp] = cur;
				cur = a[cur];
			} while ( cur != i );
		//	fprintf(stderr, "%d\n", nTmp);
			if ( nTmp >= 5 ) {
				int cnt = 0;
				for ( int i = 1; nTmp-i+1 > 4; i += 4 ) {
					out[nOut][0] = make_pair(5, 5);
					out[nOut][1] = make_pair(tmp[nTmp], tmp[i]);
					out[nOut][2] = make_pair(tmp[i], tmp[i+1]);
					out[nOut][3] = make_pair(tmp[i+1], tmp[i+2]);
					out[nOut][4] = make_pair(tmp[i+2], tmp[i+3]);
					out[nOut][5] = make_pair(tmp[i+3], tmp[nTmp]);
					nOut++;
					cnt+=4;
				}
				for ( int i = cnt+1; i <= nTmp; i ++ )
					tmp[i-cnt] = tmp[i]; 
				nTmp -= cnt;
			} 
			if ( nTmp == 4 ) {
				out[nOut][0] = make_pair(4, 4);
				out[nOut][1] = make_pair(tmp[1], tmp[2]);
				out[nOut][2] = make_pair(tmp[2], tmp[3]);
				out[nOut][3] = make_pair(tmp[3], tmp[4]);
				out[nOut][4] = make_pair(tmp[4], tmp[1]);
				nOut++;
			} else if ( nTmp == 3 ) {
				for ( int t = 1; t <= 3; t ++ )
					three[nThree][t] = tmp[t];
				nThree++;
			} else if ( nTmp == 2 ) {
				for ( int t = 1; t <= 2; t ++ )
					two[nTwo][t] = tmp[t];
				nTwo++;
			}
		}
	for ( int i = 0; i < min(nThree, nTwo); i ++ ) {
		out[nOut][0] = make_pair(5, 5);
		out[nOut][1] = make_pair(two[i][1], two[i][2]);
		out[nOut][2] = make_pair(two[i][2], two[i][1]);
		out[nOut][3] = make_pair(three[i][1], three[i][2]);
		out[nOut][4] = make_pair(three[i][2], three[i][3]);
		out[nOut][5] = make_pair(three[i][3], three[i][1]);
		nOut++;
	}
	if ( nThree > nTwo ) {
		int cur = nTwo;
		for ( int i = nTwo; i + 2 < nThree; i += 3 ) {
			out[nOut][0] = make_pair(5, 5);
			out[nOut][1] = make_pair(three[i][1], three[i][2]);
			out[nOut][2] = make_pair(three[i][2], three[i][3]);
			out[nOut][3] = make_pair(three[i][3], three[i][1]);
			out[nOut][4] = make_pair(three[i+1][1], three[i+1][2]);
			out[nOut][5] = make_pair(three[i+1][2], three[i+1][1]);
			nOut++;

			out[nOut][0] = make_pair(5, 5);
			out[nOut][1] = make_pair(three[i+1][1], three[i+1][3]);
			out[nOut][2] = make_pair(three[i+1][3], three[i+1][1]);
			out[nOut][3] = make_pair(three[i+2][1], three[i+2][2]);
			out[nOut][4] = make_pair(three[i+2][2], three[i+2][3]);
			out[nOut][5] = make_pair(three[i+2][3], three[i+2][1]);
			nOut++;
			cur = i+3;
		}
		for ( int i = cur; i < nThree; i ++ ) {
			out[nOut][0] = make_pair(3, 3);
			out[nOut][1] = make_pair(three[i][1], three[i][2]);
			out[nOut][2] = make_pair(three[i][2], three[i][3]);
			out[nOut][3] = make_pair(three[i][3], three[i][1]);
			nOut++;
		}
	}
	if ( nTwo > nThree ) {
		for ( int i = nThree; i+1 < nTwo; i += 2 ) {
			out[nOut][0] = make_pair(4, 4);
			out[nOut][1] = make_pair(two[i][1], two[i][2]);
			out[nOut][2] = make_pair(two[i][2], two[i][1]);
			out[nOut][3] = make_pair(two[i+1][1], two[i+1][2]);
			out[nOut][4] = make_pair(two[i+1][2], two[i+1][1]);
			nOut++;
		}
		if ( (nTwo-nThree)&1 ) {
			out[nOut][0] = make_pair(2, 2);
			out[nOut][1] = make_pair(two[nTwo-1][1], two[nTwo-1][2]);
			out[nOut][2] = make_pair(two[nTwo-1][2], two[nTwo-1][1]);
			nOut++;
		}
	}
	printf("%d\n", nOut);
	for ( int i = 0; i < nOut; i ++ ) {
		printf("%d\n", out[i][0].first);
		for ( int t = 1; t <= out[i][0].first; t ++ )
			printf("%d ", out[i][t].first);
		puts("");
		for ( int t = 1; t <= out[i][0].first; t ++ )
			printf("%d ", out[i][t].second);
		puts("");
	}
}
