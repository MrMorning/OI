#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    maxN    = 500 + 10;
const int    Edge    = maxN * maxN * 4;
const int    d        [4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int    ii0        [6] = {0,  0,  1,  0,  0,  1};
const int    jj0        [6] = {0,  1,  0, -1, -1,  -1};
const int    s0        [6] = {1,  0,  1,  0,  1,  1};
const int    ii1        [6] = {0, -1, -1,  1, -1,  0};
const int    jj1        [6] = {0,  0,  0,  0,  1,  1};
const int    s1        [6] = {0,  1,  0,  1,  0,  0};
const int    pp0        [6] = {1,  1,  1,  0,  0,  0};
const int    pp1        [6] = {1,  2,  2,  1,  2,  1};
const int    st01    [6] = {0,  1,  1,  1,  1,  0};
const int    st02    [6] = {1,  1,  0,  1,  0,  1};
const int    st11    [6] = {0,  1,  1,  1,  0,  1};
const int    st12    [6] = {1,  1,  0,  1,  1,  0};

int            N, M, K;
int            tot     = 1;
int            a        [maxN][maxN];
int            w        [Edge];
int            flag    [maxN][maxN];
int            add        [Edge];
int            qi        [Edge];
int            qj        [Edge];
int            qs        [Edge];
int            vis        [maxN][maxN][2];

void DFS(int x, int y, int t)
{
	int     nx, ny;

	flag[x][y] = t;
	++ w[t];
	for(int i = 0; i < 4; ++ i) {
		nx = x + d[i][0];
		ny = y + d[i][1];
		if (nx >= 0 && nx <= N + 1 && ny >= 0 && ny <= M + 1) {
			if (! flag[nx][ny] && a[nx][ny] == a[x][y])
				DFS(nx, ny, t);
		}
	}
}

void Init()
{
	scanf("%d%d%d", &N, &M, &K);
	memset(a, -1 ,sizeof(a));
	for(int i = 1; i <= N; ++ i) {
		getchar();
		for(int j = 1; j <= M; ++ j)
			a[i][j] = getchar() - '0';
	}

	DFS(0, 0, tot);
	for (int i = 1; i <= N; ++ i)
		for(int j = 1; j <= M; ++ j)    
			if (! flag[i][j]) {
				++ tot;
				DFS(i, j, tot);
			}

	for(int i = 0; i <= N + 1; ++ i) {
		for(int j = 0; j <= M + 1; ++ j) {
			a[i][j] = flag[i][j];
			//printf("%3ld", a[i][j]);
		}
		//printf("\n");
	}
}

inline bool Check1(int ci, int cj, int cs) {
	if (ci < 0 || ci > N + 1) return false;
	if (cj < 0 || cj > M + 1) return false;
	int ni = ci, nj = cj;
	if (cs) ++ nj;  else  ++ ni;
	if (ni < 0 || ni > N + 1) return false;
	if (nj < 0 || nj > M + 1) return false;
	if (a[ci][cj] == a[ni][nj] && w[a[ni][nj]] >= K) return false;
	return true;
}

inline bool Check2(int ci, int cj, int ps, int o1, int o2)
{
	if (ps == 0) -- cj;
	else if(ps == 2) -- ci;

	int pi, pj, qi, qj;

	if (o1) {
		pi = ci;
		pj = cj + 1;
		qi = ci + 1;
		qj = cj;
		if (a[pi][pj] == a[qi][qj] && w[a[pi][pj]] >= K) return false;
	}

	if (o2) {
		pi = ci;
		pj = cj;
		qi = ci + 1;
		qj = cj + 1;
		if (a[pi][pj] == a[qi][qj] && w[a[pi][pj]] >= K) return false;
	}

	return true;
}

void Solve()
{
	int top(1), bom(0), ni, nj, ns;
	int    ci, cj, cs;
	w[1] = 0;
	qi[1] = 0;
	qj[1] = 0;
	qs[1] = 0;
	vis[0][0][0] = 1;

	while (bom < top) {
		++ bom;
		ni = qi[bom];
		nj = qj[bom];
		ns = qs[bom];
		if (ns) {
			for(int k = 0; k < 6; ++ k) {
				ci = ni + ii1[k];
				cj = nj + jj1[k];
				cs = s1[k];
				if ((! vis[ci][cj][cs]) && Check1(ci, cj, cs)) {
					if (Check2(ni, nj, pp1[k], st11[k], st12[k])) {
						++ top;
						vis[ci][cj][cs] = 1;
						qi[top] = ci;
						qj[top] = cj;
						qs[top] = cs;
					}
				}
			}
		} else {
			for(int k = 0; k < 6; ++ k) {
				ci = ni + ii0[k];
				cj = nj + jj0[k];
				cs = s0[k];
				if ((! vis[ci][cj][cs]) && Check1(ci, cj, cs)) {
					if (Check2(ni, nj, pp0[k], st01[k], st02[k])) {
						++ top;
						vis[ci][cj][cs] = 1;
						qi[top] = ci;
						qj[top] = cj;
						qs[top] = cs;
					}
				}
			}
		}
	}

	for(int i = 0; i <= N + 1; ++ i)
		for(int j = 0; j <= M + 1; ++ j) {
			if (! vis[i][j][0]) {
				add[a[i][j]] = 1;
				add[a[i + 1][j]] = 1;
			}
			if (! vis[i][j][1]) {
				add[a[i][j]] = 1;
				add[a[i][j + 1]] = 1;
			}
		}

	int ans(0);
	for(int i = 2; i <= tot; ++ i)
		ans += (add[i] || w[i] >= K) * w[i];

	printf("%d\n", ans);
	//system("pause");
}

int main()
{
	freopen("t.in", "r", stdin);
	//freopen("320.out", "w", stdout);

	Init();
	Solve();

	return 0;
}
