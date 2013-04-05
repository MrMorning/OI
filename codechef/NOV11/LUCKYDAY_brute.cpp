#include <cstdio>
#include <cstring>
const int LEN_MAX = 1000000;
int idt[LEN_MAX + 1];
int S[LEN_MAX + 1];

void add(int i, int v) {
	for ( ; i <= LEN_MAX; i += i & -i )
		idt[i] += v;
}

int sum(int i) {
	int res = 0;
	for ( ; i; i -= i & -i )
		res += idt[i];
	return res;
}

void solve() {
	FILE *ftmp = fopen("t.err", "w");
	memset(idt, 0, sizeof(idt));
	int A, B, X, Y, Z, P, C, Q;
	scanf("%d%d%d%d%d%d%d%d", &A, &B, &X, &Y, &Z, &P, &C, &Q);
	S[1] = A, S[2] = B;
	if ( S[1] == C )
		add(1, 1);
	if ( S[2] == C )
		add(2, 1);
	for ( int i = 3; i <= LEN_MAX; i ++ ) {
		S[i] = (X * S[i - 1] + Y * S[i - 2] + Z) % P;
		if ( S[i] == C )
			add(i, 1);
	}

	while ( Q -- ) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", sum(r) - sum(l - 1));
	}

	for ( int i = 1; i <= 50; i ++ ) {
		fprintf(ftmp, "%d %d\n", i, S[i]);
	}

}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	while ( TST -- )
		solve();
}
