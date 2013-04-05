#include <iostream>
#include <algorithm>
using namespace std;

int a[100];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	int ret = 0, s = 0, t = n - 1;
	while (s < t) {
		++ret;
		--a[s];
		a[t - 1] += a[t];
		--t;
		if (a[s] == 0) ++s;
	}
	cout << ret << endl;
	return 0;
}

