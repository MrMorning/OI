#include <cstdio>
#include <algorithm>
#define mp(a, b) make_pair(a,b)
using namespace std;
typedef pair<int, int> pair_t;
const int kInf = 0x3f3f3f3f;

struct Point {
	int x, y;
	Point(){}
	Point(int xx, int yy):
		x(xx), y(yy){}
} src, des;

struct Platform {
	int l, r, h;
	bool operator< (const Platform &T) const {
		return h < T.h;
	}
	bool contain(Point p) {
		return l <= p.x && p.x <= r && p.y == h;
	}
} plat[111];
int n, s, m;
pair_t f[111][2];

pair_t operator+ (const pair_t &A, const pair_t &B) {
	if ( A.first == kInf ) return B;
	if ( B.first == kInf ) return A;
	return mp(A.first+B.first, A.second+B.second);
}

int getCatcher(Point p) {
	int res = 0;
	for ( int i = 1; i <= m; i ++ )
		if ( plat[i].l < p.x && p.x < plat[i].r && p.y > plat[i].h ) {
			if ( res == 0 ) res = i;
			else if ( plat[res].h < plat[i].h )
				res = i;
		}
	return res;
}

int main() {
#define GETX(P,i) (((i)==0)?(P).l:(P).r)
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &s);
	scanf("%d%d%d%d", &src.x, &src.y, &des.x, &des.y);
	scanf("%d", &m);
	for ( int i = 1; i <= m; i ++ )
		scanf("%d%d%d", &plat[i].l, &plat[i].r, &plat[i].h);
	sort(plat+1, plat+1+m);
	for ( int i = 1; i <= m; i ++ ) {
		for ( int j = 0; j <= 1; j ++ ) {
			int t = getCatcher(Point(GETX(plat[i],j),plat[i].h));
			if ( t == 0 ) 
				f[i][j] = mp(kInf, kInf);
			else {
				f[i][j] = mp(kInf, kInf);
				if ( plat[t].contain(des) ) {
					if ( des.x == GETX(plat[i], j) )
						f[i][j] = min(f[i][j], mp(0, plat[i].h-plat[t].h));
					else { 
						f[i][j] = min(f[i][j], mp((int)(j!=(des.x>GETX(plat[i],j))), plat[i].h-plat[t].h
									+abs(GETX(plat[i],j)-des.x)));
					}
				} else {
					for ( int k = 0; k <= 1; k ++ ) 
						if ( f[t][k].first != kInf ) {
							pair_t tmp = mp((int)(j!=k), plat[i].h-plat[t].h
									+abs(GETX(plat[i],j)-GETX(plat[t],k))) + f[t][k];
							f[i][j] = min(f[i][j], tmp);
						}
				}
			}
		}
	}
	int t = getCatcher(src);
	if ( t == 0 ) {
		puts("0 0");
		return 0;
	} 
	pair_t ans;
	if ( plat[t].contain(des) ) {
		if ( des.x >= src.x )
			ans = mp(0, des.x-src.x+src.y-des.y);
		else
			ans = mp(1, src.y-des.y+src.x-des.x);
	} else  
		ans = min(f[t][0].first==kInf?f[t][0]:(mp(1, src.y-plat[t].h+src.x-plat[t].l)+f[t][0]),
				f[t][1].first==kInf?f[t][1]:(mp(0, src.y-plat[t].h+plat[t].r-src.x)+f[t][1]));
	if ( ans.first == kInf || ans.first >= n ) puts("0 0");
	else 
		printf("%d %d\n", n-ans.first, ans.second+(n-1)*s);
}
