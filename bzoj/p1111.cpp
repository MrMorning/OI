#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MOD = 1000000000;
int f[11111][2], g[11111][2];

string convert(const string &num) {
	string cs = num, ts, res;
	while (cs.size()) {
		ts = "";
		int n = cs.size();
		int acc = 0;
		for (int i = 0; i < n; i ++) {
			acc = acc * 10 + (int)(cs[i] - '0');
			if (!(i == 0 && acc < 4))
				ts += (char)('0' + (acc / 4));
			acc %= 4;
		}
		res += (char)('0' + acc);
	//	fprintf(stderr, "%s\n", ts.c_str());
		cs = ts;
	}
	return res;
}

void upd(int i2, int j2, int i1, int j1, int del) {
	if (f[i2][j2] > f[i1][j1] + del)
		f[i2][j2] = f[i1][j1] + del, g[i2][j2] = g[i1][j1];
	else if (f[i2][j2] == f[i1][j1] + del)
		g[i2][j2] = (g[i2][j2] + g[i1][j1]) % MOD;
}

int solve(const string &num) {
	static int a[11111];
	memset(f, 0x3f, sizeof(f));
	memset(g, 0, sizeof(g));
	f[0][0] = 0, g[0][0] = 1;
	int n = num.size();
	for (int i = 1; i <= n; i ++)
		a[i] = (num[i - 1] - '0');
	for (int i = 0; i <= n; i ++) {
		upd(i + 1, 0, i, 0, a[i + 1]);
		upd(i + 1, 1, i, 0, 4 - a[i + 1]);
		upd(i + 1, 0, i, 1, a[i + 1] + 1);
		upd(i + 1, 1, i, 1, 3 - a[i + 1]);
	}
	int res1 = f[n + 1][0], res2 = g[n + 1][0];
//	fprintf(stderr, "smallest length = %d\n", res1);
	return res2;
}
string str;
int main() {
	freopen("t.in", "r", stdin);
	cin >> str;
	printf("%d\n", solve(convert(str)));
}
