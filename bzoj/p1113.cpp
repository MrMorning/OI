#include <cstdio>
const int N_MAX = 250000;
int n, stack[N_MAX], top;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	int ans = 0;
	for(int i = 0, w, h; i < n; i ++)
	{
		scanf("%d%d", &w, &h);
		ans ++;
		while(top && stack[top - 1] > h)
			top --;
		if(top && stack[top - 1] == h)
			ans --;
		stack[top ++] = h;
	}
	printf("%d\n", ans);
}
