#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <utility>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

const int MAX_N = 100000 + 100;

struct Segment {
	int l, r, value;
	bool operator<(const Segment&s) const {
		if (r != s.r)
			return r < s.r;
		return l < s.l;
	}
	bool operator==(const Segment&s) const {
		return l == s.l && r == s.r;
	}
	void check() {
		int size = r - l + 1;
		if (value > size)
			value = size;
	}
};
int n;
int oldN;

Segment segments[MAX_N];
int dp[MAX_N];

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	cin >> n;
	oldN = n;

	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		int A, B;
		scanf("%d%d", &A, &B);
		if (A + B >= n)
			continue;
		int L = A, R = n - B - 1;
		segments[cnt].l = L, segments[cnt].r = R;
		cnt++;
	}

	n = cnt;
	sort(segments, segments + n);
	cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (cnt > 0 && segments[i] == segments[cnt - 1]) {
			segments[cnt - 1].value++;
		} else {
			segments[cnt] = segments[i];
			segments[cnt++].value = 1;
		}
	}

	n = cnt;

	for (int i = 0; i < n; ++i) {
		segments[i].check();
	}

	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		Segment&cur = segments[i - 1];
		dp[i] = max(dp[i], dp[i - 1]);
		int l = -1, r = i;
		while (l + 1 < r) {
			int m = (l + r) >> 1;
			if (segments[m].r < cur.l)
				l = m;
			else
				r = m;
		}
		dp[i] = max(dp[i], dp[l + 1] + cur.value);
	}

	cout << oldN - dp[n] << endl;
}
