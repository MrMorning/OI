#include <stdio.h>
#include <string.h>
 
const int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
 
int a[202][202], fx[202][202], fy[202][202], v[202][202];
int n, m;
 
int i, j, k = 0, ans = 0;
 
char search(const int x, const int y) {
	int i, p, q;
	for (i = 0; i < 4; ++i) {
		p = x + DIR[i][0], q = y + DIR[i][1];
		if (v[p][q] != k && a[p][q]) {
			v[p][q] = k;
			if (!fx[p][q] || search(fx[p][q], fy[p][q])) {
				fx[x][y] = p, fy[x][y] = q;
				fx[p][q] = x, fy[p][q] = y;
				return 1;
			}
		}
	}
	return 0;
}
 
void erase(const int x, const int y) {
	if (v[x][y]) return ;
	int i, p, q;
	v[x][y] = 1, a[x][y] = 2;
	for (i = 0; i < 4; ++i) {
		p = x + DIR[i][0], q = y + DIR[i][1];
		if (!v[p][q]) {
			v[p][q] = 1;
			if (fx[p][q]) erase(fx[p][q], fy[p][q]);
		}
	}
}
 
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	memset(a, 0, sizeof a);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j) {
			scanf("%d", a[i] + j);
			ans += a[i][j];
		}
 
	memset(fx, 0, sizeof fx);
	memset(v, 0, sizeof v);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
			if (!((i + j) & 1) && a[i][j])
				if (++k, search(i, j)) --ans;
 
	memset(v, 1, sizeof v);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j) v[i][j] = a[i][j] ^ 1;
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= m; ++j)
			if (!fx[i][j]) erase(i, j);
 
	printf("%d\n", ans);
	for (i = 1; i <= n; ++i, printf("\n"))
		for (j = 1; j <= m; ++j)
			if (!a[i][j]) putchar('#');
			else putchar(a[i][j] == 2 || (!((i + j) & 1) && !v[i][j]) ? 'G' : '.');
	return 0;
}
