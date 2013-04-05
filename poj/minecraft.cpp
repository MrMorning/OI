#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define GET(s, i) (((s) & (3 << (((i) - 1) << 1))) >> (((i) - 1) << 1))
#define CLR(s, i) ((s) & ~(3 << (((i) - 1) << 1)))
#define SET(s, i, t) (CLR(s, i) + ((t) << (((i) - 1) << 1)))

int toMask[111111];
int toId[1 << 20];
int f[2][111111];
int N, M, K;
int forbid[200][15], fbdsum[200][15];
bool okayv[200][15], okayh[200][15];
int maskCnt;

int rev(int s){
	if(toId[s] == -1){
		toMask[maskCnt ++] = s;
		toId[s] = maskCnt - 1;
	}
	return toId[s];
}

void expand(int i, int j, int s, int ns, int val){
	f[(i + 1) & 1][rev(ns)] = max(f[(i + 1) & 1][rev(ns)], val);
	if(j > M)
		return;
	expand(i, j + 1, s, ns, val);
	if(okayv[i][j] && GET(s, j) == 0 && GET(s, j + 1) == 0){
		int tns = SET(ns, j, 2);
		tns = SET(tns, j + 1, 2);
		expand(i, j + 2, s, tns, val + 1);
	}
	if(okayh[i][j] && GET(s, j) == 0 && GET(s, j + 1) == 0 && GET(s, j + 2) == 0){
		int tns = SET(ns, j, 1);
		tns = SET(tns, j + 1, 1);
		tns = SET(tns, j + 2, 1);
		expand(i, j + 3, s, tns, val + 1);
	}
}

int getsum(int x1, int y1, int x2, int y2){
	return fbdsum[x2][y2] - fbdsum[x1 - 1][y2] - fbdsum[x2][y1 - 1] + fbdsum[x1 - 1][y1 - 1];
}

void solve(){
	scanf("%d%d%d", &N, &M, &K);
	memset(forbid, 0, sizeof(forbid));
	memset(fbdsum, 0, sizeof(fbdsum));
	memset(okayv, 0, sizeof(okayv));
	memset(okayh, 0, sizeof(okayh));
	memset(toId, -1, sizeof(toId));
	maskCnt = 0;

	for(int i = 0; i < K; i ++){
		int x, y;
		scanf("%d%d", &x, &y);
		forbid[x][y] = true;
	}
	for(int i = 1; i <= N; i ++)
		for(int j = 1; j <= M; j ++)
			fbdsum[i][j] = fbdsum[i - 1][j] + fbdsum[i][j - 1] - fbdsum[i - 1][j - 1] + forbid[i][j];
	for(int i = 1; i <= N - 2; i ++)
		for(int j = 1; j <= M - 1; j ++)
			okayv[i][j] = (getsum(i, j, i + 2, j + 1) == 0);
	for(int i = 1; i <= N - 1; i ++)
		for(int j = 1; j <= M - 2; j ++)
			okayh[i][j] = (getsum(i, j, i + 1, j + 2) == 0);

	f[1][rev(0)] = 0;
	for(int i = 1; i <= N; i ++){
		memset(f[(i + 1) & 1], 0, sizeof(f[0]));
		for(int k = 0, tot = maskCnt; k < tot; k ++){
			int ns = toMask[k];
			for(int j = 1; j <= M; j ++){
				int t = GET(ns, j);
				if(t > 0)
					ns = SET(ns, j, t - 1);
			}
			expand(i, 1, toMask[k], ns, f[i & 1][k]);
		}
	}
	printf("%d\n", f[(N + 1) & 1][rev(0)]);
}

int main(){
	freopen("minecraft.in", "r", stdin);
//	freopen("minecraft.out", "w", stdout);
	int TST;
	scanf("%d", &TST);
	while(TST --)
		solve();
}
