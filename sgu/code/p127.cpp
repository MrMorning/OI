#include <cstdio>
#include <algorithm>
using namespace std;

int n, k;
int a[8000];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &k);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	int ans = 2, acc = 0;
	for(int i = 0; i < n; i ++, acc ++)
		if(acc >= k ||  i == 0 || a[i] / 1000 != a[i - 1] / 1000)
			acc = 0, ans ++;
	printf("%d\n", ans);
}
