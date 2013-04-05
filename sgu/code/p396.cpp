#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int kInf = 0x3f3f3f3f;

struct Edge {
	int to, msk, val;
	Edge *next;
} edge[1<<12], *begin[1<<6];
int edgeCnt;
int f[1010][1<<6], g[1010][1<<6];
int n;
char beat[1010];

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int conv(char ch) {
	if ( ch == 'L' ) return 0;
	if ( ch == 'R' ) return 1;
	if ( ch == 'U' ) return 2;
	return 3;
}

char invConv(int t) {
	if ( t == 0 ) return 'L';
	if ( t == 1 ) return 'R';
	if ( t == 2 ) return 'U';
	return 'D';
}

void decrypt(int s, int &cl, int &cr, int &pl, int &pr) {
	cl = s>>4;
	cr = (s>>2)&3;
	pl = (s>>1)&1;
	pr = s&1;
}

int encrypt(int cl, int cr, int pl, int pr) {
	return (cl<<4)|(cr<<2)|(pl<<1)|pr;
}

bool valid(int s) {
	int cl, cr, pl, pr;
	decrypt(s, cl, cr, pl, pr);
	if ( cl == cr || (cl == RIGHT && cr == LEFT) ) return false;
	return true;
}

void addEdge(int u, int v, int msk, int val) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->msk = msk, e->val = val;
	begin[u] = e;
}

void prework() {
	for ( int s = 0; s < (1<<6); s ++ ) {
		int cl, cr, pl, pr;
		decrypt(s, cl, cr, pl, pr);
		addEdge(s, encrypt(cl, cr, 0, 0), 0, 0);
		addEdge(s, encrypt(cl, cr, 1, 0), 1<<cl, 1);
		addEdge(s, encrypt(cl, cr, 0, 1), 1<<cr, 1);
		for ( int dir = 0; dir < 4; dir ++ ) {
			addEdge(s, encrypt(dir, cr, 1, 0), 1<<dir, pl?9:3);
			addEdge(s, encrypt(cl, dir, 0, 1), 1<<dir, pr?9:3);
		}
		for ( int dl = 0; dl < 4; dl ++ )
			for ( int dr = 0; dr < 4; dr ++ )
				addEdge(s, encrypt(dl, dr, 1, 1), (1<<dl)|(1<<dr), 10);
	}
}

void output(int i, int s) {
	if ( g[i][s] != -1 )
		output(i-1, g[i][s]);
	else return;
	int cl, cr, pl, pr;
	decrypt(s, cl, cr, pl, pr);
	printf("%c%c\n", invConv(cl), invConv(cr));
}

int main() {
	freopen("t.in", "r", stdin);
	prework();
	scanf("%d", &n);
	scanf("%s", beat);
	memset(f, 0x3f, sizeof(f));
	memset(g, -1, sizeof(g));
	f[0][encrypt(LEFT,RIGHT,0,0)] = 0;
	for ( int i = 0; i < n; i ++ ) 
		for ( int s = 0; s < (1<<6); s ++ ) 
			if ( f[i][s] != kInf && valid(s) ) {
				for ( Edge *e = begin[s]; e; e = e->next )
					if ( beat[i] == 'N' || (e->msk & (1<<conv(beat[i]))) ) {
						int tmp = f[i][s] + e->val;
						if ( tmp < f[i+1][e->to] ) {
							f[i+1][e->to] = tmp;
							g[i+1][e->to] = s;
						}
					}
			}
	int leastEnergy = kInf, memo;
	for ( int s = 0; s < (1<<6); s ++ )
		if ( f[n][s] != kInf && valid(s) ) {
			if ( leastEnergy > f[n][s] ) {
				leastEnergy = f[n][s];
				memo = s;
			}
		}
	printf("%d\n", leastEnergy);
	output(n, memo);
}
