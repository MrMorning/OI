#include <cstdio>
#include <cstring>
#define M (200 + 5)
#define N (2000 + 10)
int cost[M][M];
int map[256], asize, l1, l2;
int s1[N], s2[N];
struct KEY {
	int cc, ch;
};
KEY s1p[M], s2p[M];
char str[N], alpha[N];
void prepare() {
	int i, j;
	scanf("%s", alpha);
	asize = strlen(alpha);
	for (i = 0; i < asize; i++)
		map[alpha[i]] = i;

	scanf("%s", str + 1);
	l1 = strlen(str + 1);
	for (i = 1; i <= l1; i++)
		s1[i] = map[str[i]];

	scanf("%s", str + 1);
	l2 = strlen(str + 1);
	for (i = 1; i <= l2; i++)
		s2[i] = map[str[i]];

	for (i = 0; i < asize; i++)
		for (j = 0; j < asize; j++)
			scanf("%d", &cost[i][j]);

	for (i = 0; i < asize; i++) {
		s1p[i].cc = cost[i][0], s1p[i].ch = 0;
		for (j = 1; j < asize; j++)
			if (cost[i][j] < s1p[i].cc)
				s1p[i].ch = j, s1p[i].cc = cost[i][j];
	}

	for (i = 0; i < asize; i++) {
		s2p[i].cc = cost[0][i], s2p[i].ch = 0;
		for (j = 1; j < asize; j++)
			if (cost[j][i] < s2p[i].cc)
				s2p[i].ch = j, s2p[i].cc = cost[j][i];
	}
}

int dp[N][N];
short trans[N][N][2];
short a1[N*2], a2[N*2];
void print() {
	int x = l1, y = l2, px, py, len = 0, k;
	do {
		px = trans[x][y][0], py = trans[x][y][1];
		if (x == px + 1 && y == py + 1)
			a1[len] = s1[x], a2[len] = s2[y];
		else if (y == py)
			a1[len] = s1[x], a2[len] = s1p[s1[x]].ch;
		else
			a1[len] = s2p[s2[y]].ch, a2[len] = s2[y];
		x = px, y = py, len++;
	} while (x != 0 || y != 0);
	printf("%d\n", dp[l1][l2]);
	/*for (k = len - 1; k >= 0; k--)
		putchar(alpha[a1[k]]);
	putchar('\n');
	for (k = len - 1; k >= 0; k--)
		putchar(alpha[a2[k]]);
	putchar('\n');*/
}
int main() {
	freopen("t.in", "r", stdin);
	prepare();
	int i, j, x1, x2, x3;
	dp[0][0] = 0;
	for (i = 1; i <= l1; i++)
		dp[i][0] = dp[i - 1][0] + s1p[s1[i]].cc, trans[i][0][0] = i - 1, trans[i][0][1] = 0;
	for (i = 1; i <= l2; i++)
		dp[0][i] = dp[0][i - 1] + s2p[s2[i]].cc, trans[0][i][0] = 0, trans[0][i][1] = i - 1;
	for (i = 1; i <= l1; i++)
		for (j = 1; j <= l2; j++) {

			x1 = dp[i - 1][j - 1] + cost[s1[i]][s2[j]];
			x2 = dp[i][j - 1] + s2p[s2[j]].cc, x3 = dp[i - 1][j] + s1p[s1[i]].cc;
			if (x1 <= x2 && x1 <= x3)
				trans[i][j][0] = i - 1, trans[i][j][1] = j - 1, dp[i][j] = x1;
			else if (x2 <= x1 && x2 <= x3)
				trans[i][j][0] = i, trans[i][j][1] = j - 1, dp[i][j] = x2;
			else
				trans[i][j][0] = i - 1, trans[i][j][1] = j, dp[i][j] = x3;
		}
	print();
	return 0;
}
