#include <stdio.h>
#include <string.h>

int in[3000][3], bc[50010], rk[50010], n, m;
int k, ans, max;

int getfather(int i) {
	if(bc[i] == -1) return i;
	int t = getfather(bc[i]);
	rk[i] = (rk[i] + rk[bc[i]]) % 3;
	return bc[i] = t;
}

int hb(int a, int b, int c) {
	int i = getfather(a);
	int j = getfather(b);
	if(i == j) return (rk[a] + c) % 3 != rk[b];
	bc[i] = j;
	rk[i] = (6 + rk[b] - c - rk[a]) % 3;
	return 0;
}
/*
 * void print() {
 * for(int i = 1; i <= n; ++i) {
 *    printf("%d %d %d\n", i, bc[i], rk[i]);
 *    }
 *    }
 *    */

int solve(int x) {
	memset(bc, -1, sizeof(bc));
	memset(rk, 0, sizeof(rk));
	for(int i = 0; i < m; ++i) {
		if(in[i][0] == x || in[i][1] == x) continue;
		if(hb(in[i][0], in[i][1], in[i][2])) {
			if(max < i) max = i;
			return 0;
		}
	}
	return 1;
}
int main() {
	freopen("t.in","r",stdin);
	int a, b, c;
	char op;
	while(scanf("%d %d", &n, &m) != EOF) {
		ans = 0;
		k = 0;
		max = -1;
		for(int i = 0; i < m; ++i) {
			scanf("%d%c%d", &a, &op, &b);
			in[i][0] = a;
			in[i][1] = b;
			switch(op) {
				case '<':
					in[i][2] = 2;
					break;
				case '=':
					in[i][2] = 0;
					break;
				case '>':
					in[i][2] = 1;
					break;
			}
		}
		for(int i = 0; i < n; ++i) {
			if(solve(i)) {
				k++;
				ans = i;
			}
		}
		if(k == 0) {
			printf("Impossible\n");
		} else if(k == 1) {
			printf("Player %d can be determined to be the judge after %d lines\n", ans, max + 1);
		} else {
			printf("Can not determine\n");
		}
	}
	return 0;
}
