#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, a[100010];

int find_lower(int x)
{
	int lb = 1, rb = n + 1, mid = (lb + rb) >> 1;
	//[lb, rb)
	while(lb < rb - 1)
	{
		if(a[mid] <= x)
			lb = mid;
		else
			rb = mid;
		mid = (lb + rb) >> 1;
	}
	return a[lb];
}

int find_upper(int x)
{
	int lb = 0, rb = n, mid = (lb + rb) >> 1;
	//(lb, rb]
	while(lb < rb - 1)
	{
		if(a[mid] >= x)
			rb = mid;
		else
			lb = mid;
		mid = (lb + rb) >> 1;
	}
	return a[rb];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	int ans = 0;
	for(int i = 1, x; i <= m; i ++)
	{
		scanf("%d", &x);
		ans += min(abs(x - find_lower(x)), abs(find_upper(x) - x));
	}
	printf("%d\n", ans);
}
