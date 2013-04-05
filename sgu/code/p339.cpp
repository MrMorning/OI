#include <cstdio>
#include <algorithm>
using namespace std;
struct Segment {
	int l, r;
	Segment(){}
	Segment(int _l, int _r):
		l(_l), r(_r){}
} seg[1111];
int n;
int main() {
	freopen("t.in", "r", stdin);
	static char cmd[3];
	int l, r;
	while ( scanf("%s%d%d", cmd, &l, &r) != EOF ) {
		if ( cmd[0] == '+' ) {
			int cnt = 0;
			for ( int i = 0; i < n; i ++ )
				if ( seg[i].l >= l && seg[i].r <= r )
					cnt ++;
			printf("%d\n", cnt);
			seg[n++] = Segment(l, r);
		} else {
			for ( int i = 0; i < n; i ++ )
				if ( seg[i].l == l && seg[i].r == r ) {
					swap(seg[n - 1], seg[i]);
					n --;
					break;
				}
		}
	}
}
