#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[10010];
int sum[10010];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	int n = strlen(str);
	for(int i = 1; i <= n; i ++)
		sum[i] = sum[i - 1] + (str[i] == '(' ? 1 : -1);
	for(int i = n; i >= 3; i --)
		if(str[i - 1] == ')' && str[i - 2] == '(')
			if(sum[i - 2] > 0)
			{
				swap(str[i - 1], str[i - 2]);
				for(int j = n; j > i; j --)
					if(str[j - 1] == '(' && str[j - 2] == ')')
						swap(str[j - 1], str[j - 2]);
				printf("%s", str);
				return 0;
			}
	printf("No solution\n");
}
