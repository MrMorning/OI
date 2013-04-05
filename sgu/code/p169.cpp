#include <cstdio>
int main()
{
//	freopen("t.in", "r", stdin);
	int K;
	scanf("%d", &K);
	if(K == 1)
		printf("%d\n", 8);
	else
	{
		int cnt = 1;
		if((K - 1) % 3 == 0)
		{
			cnt += 2;
			if((K - 1) % 6 == 0)
				cnt ++;
		}
		printf("%d\n", cnt);
	}
}
