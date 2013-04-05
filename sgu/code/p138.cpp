#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

struct Info
{
	int idx, cnt;
	bool operator<(const Info &t) const
	{
		return cnt > t.cnt;
	}
} a[110];
int ans[110000][2];
int n;

int main()
{
	freopen("t.in", "r", stdin);
	memset(ans, -1, sizeof(ans));
	scanf("%d", &n);
	int sum = 0;
	for(int i = 0; i < n; i ++)
	{
		scanf("%d", &a[i].cnt);
		a[i].idx = i + 1;
		sum += a[i].cnt;
	}
	sum /= 2;
	printf("%d\n", sum);
	sort(a, a + n);
	int tot = 0;
	for(int i = 0; i < n; i ++)
	{
		while(tot < sum && a[i].cnt > 1)
			ans[tot ++][0] = a[i].idx, a[i].cnt --;
		if(tot < sum)
		{
			ans[tot][0] = a[i + 1].idx, a[i + 1].cnt --;
			ans[tot ++][1] = a[i].idx, a[i].cnt --;
		}
	}

	assert(tot == sum);
	int top = 0;
	while(n - 1 && a[top].cnt == 0) top ++;
	for(int i = 0; i < sum; i ++)
	{
		printf("%d ", ans[i][0]);
		if(ans[i][1] != -1)
			printf("%d\n", ans[i][1]);
		else
		{
			printf("%d\n", a[top].idx);
			a[top].cnt --;
			while(top < n - 1 && a[top].cnt == 0) top ++;
		}
	}
}
