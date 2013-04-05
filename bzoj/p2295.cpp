#include <cstdio>
#include <cstring>

const char PTRN[9] = {'l', 'u', 'v', 'l', 'e', 't', 't', 'e', 'r'};
char str[100001];

void solve()
{
	char ch;
	int len = 0;
	for(; (ch = getchar()) != '\n'; )
		str[len ++] = ch;
	int ans = 0;
	for(int i = 0, j = 0; i < len; i ++)
		if(str[i] == PTRN[j])
		{
			if(j == 8)
				j = 0, ans ++;
			else
				j ++;
			continue;
		}
	printf("%d\n", ans);
}
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int n_test;
	scanf("%d\n", &n_test);
	while(n_test --)
		solve();
}
