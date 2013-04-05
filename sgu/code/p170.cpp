#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str1[5100], str2[5100];
int a[5100], b[5100], na, nb;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s%s", str1, str2);
	if(strlen(str1) != strlen(str2))
	{
		printf("-1\n");
		return 0;
	}
	int n = strlen(str1);
	for(int i = 0; i < n; i ++)
		if(str1[i] == '-')
			a[na ++] = i; 
	for(int i = 0; i < n; i ++)
		if(str2[i] == '-')
			b[nb ++] = i; 
	if(na != nb)
	{
		printf("-1\n");
		return 0;
	}
	int ans = 0;
	for(int i = 0; i < n; i ++)
		ans += abs(a[i] - b[i]);
	printf("%d\n", ans);
}
