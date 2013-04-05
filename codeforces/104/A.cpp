#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char sa[111111], sb[111111];

int main() {
//	freopen("t.in", "r", stdin);
	scanf("%s", sa);
	scanf("%s", sb);
	int n = strlen(sa);
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < n; i ++) {
		if (sa[i] == '4' && sb[i] == '7')
			cnt1 ++;
		if (sa[i] == '7' && sb[i] == '4')
			cnt2 ++;
	}
	printf("%d\n", max(cnt1, cnt2));
}
