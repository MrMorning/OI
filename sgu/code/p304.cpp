#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define IGNORE 0
#define FOLLOW 1
#define BUILD 2

const int inf = 0x3f3f3f3f;

struct Teeth {
	int a, c, id;
} teeth[666];
int f[666][666], g[666][666];
int pre[666], B[666];
int N, K, P;

bool cmpC(const Teeth &a, const Teeth &b) {
	return a.c < b.c;
}

void output(int i, int j) {
	if ( j == 0 )
		return;
	output(g[i][j], j - 1);
	printf("%d ", teeth[i].id);
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &N, &K, &P);
	for ( int i = 1; i <= K; i ++ )
		scanf("%d", &B[i]);
	for ( int i = 1; i <= N; i ++ ) {
		scanf("%d%d", &teeth[i].a, &teeth[i].c);
		teeth[i].id = i;
	}
	sort(teeth + 1, teeth + 1 + N, cmpC);
	for ( int i = 1; i <= N; i ++ ) {
		int st = i;
		while ( i + 1 <= N && teeth[i + 1].c == teeth[i].c )
			i ++;
		pre[teeth[i].c] = st - 1;
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 1; i <= N; i ++ ) {
		for ( int j = 1; j <= i; j ++ ) {
			for ( int k = 0; k < i; k ++ ) {
				if ( k <= pre[teeth[i].c] ) {
					int tmp = f[k][j - 1] + B[teeth[i].c] + teeth[i].a;
					if ( tmp < f[i][j] ) {
						f[i][j] = tmp;
						g[i][j] = k;
					}
				} else {
					int tmp = f[k][j - 1] + teeth[i].a;
					if ( tmp < f[i][j] ) {
						f[i][j] = tmp;
						g[i][j] = k;
					}
				}
			}
		}
	}

	int ansI = 0, ansJ = 0;
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= i; j ++ )
			if ( P >= f[i][j] && ansJ < j ) {
				ansI = i, ansJ = j;
				break;
			}
	printf("%d\n", ansJ);
	output(ansI, ansJ);
}
