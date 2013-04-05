#include <cstdio>
#include <algorithm>
using namespace std;
const int kInf = 0x3f3f3f3f;
int fr[111111], bk[111111];
int co[222222], cs[222222];
int n, nCo, nCs;

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		scanf("%d%d", &fr[i], &bk[i]);
		co[nCo++] = fr[i];
		co[nCo++] = bk[i];
	}
	sort(co, co + nCo);
	for ( int i = 0; i < nCo; i ++ ) {
		int st = i;
		while ( i + 1 < nCo && co[i+1] == co[i] )
			 i ++;
		int en = i;
		if ( 2*(en - st + 1) >= n )
			cs[nCs++] = co[i];
	}
	int ans = kInf;
	for ( int i = 0; i < nCs; i ++ ) {
		int cnt1 = 0, cnt2 = 0;
		for ( int j = 0; j < n; j ++ )
			if ( fr[j] == cs[i] ) cnt1 ++;
			else if ( bk[j] == cs[i] ) cnt2 ++;
		if ( 2*(cnt1 + cnt2) >= n ) 
			ans = min(ans, max(0, (n+1)/2-cnt1));
	}
	if ( ans == kInf )
		puts("-1");
	else
		printf("%d\n", ans);
}
