#include <cstdio>
typedef long long ll;
int a[1001];
int main()
{
	freopen("t.in", "r", stdin);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i ++)
			scanf("%d", &a[i]);
		int res = 1;
		for(int i = n - 1; i > 0; i --)
			res = ((ll)res * a[i] + 1) % 9;
		res = ((ll)res * a[0]) % 9;
		printf("%d\n", res ? res : 9);
	}
}
