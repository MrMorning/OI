#include <cstdio>
const int N_MAX = 50010;
int meet[N_MAX];
int a[2 * N_MAX], idt[2 * N_MAX];
int n, ans;
int sum(int i) {
	int res = 0;
	for (; i; i -= i & -i)
		res += idt[i];
	return res;
}
void add(int i, int x) {
	for (; i < 2 * n; i += i & -i)
		idt[i] += x;
}
int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; i ++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= 2 * n; i ++) 
		if (!meet[a[i]]) {
			meet[a[i]] = i;
			add(i, 1);
		}
		else {
			int l = meet[a[i]] + 1, r = i - 1;
			int res = sum(r) - sum(l - 1);
			ans += res;
			add(meet[a[i]], -1);
		}
	printf("%d\n", ans);
}
