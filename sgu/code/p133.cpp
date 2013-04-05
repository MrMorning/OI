#include <cstdio>
#include <algorithm>
using namespace std;
int n;
pair<int, int> a[16000];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d", &a[i].first, &a[i].second);
	sort(a, a + n);
	int b = -1, ans = 0;
	for(int i = 0; i < n; i ++)
	{
		if(a[i].second < b)
			ans ++;
		b = max(b, a[i].second);
	}
	printf("%d\n", ans);
}
