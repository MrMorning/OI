#include <cstdio>
int a[4][4];
int fetch(int i)
{
	return a[i / 4][i % 4];
}
int main()
{
	freopen("t.in", "r", stdin);
	int cnt = 0;
	for(int i = 0; i < 4; i ++)
		for(int j = 0; j < 4; j ++)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j] == 0)
				cnt += 6 - i - j;
		}
	for(int i = 0; i < 16; i ++)
		for(int j = i + 1; j < 16; j ++)
			if(fetch(i) > fetch(j))
				cnt ++;
	if(cnt & 1)
		printf("YES\n");
	else
		printf("NO\n");
}
