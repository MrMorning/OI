#include <cstdio>
int a, b, x, l, r;

int main()
{
	freopen("t.in", "r", stdin);
	int res = 0;
	scanf("%d%d%d%d%d", &a, &b, &x, &l, &r);
	for(int t = a; t <= b; t ++)
		if(t % x == 0)
		{
			int tmp = t;
			int cnt = 0;
			while(tmp)
				cnt += tmp % 10, tmp /= 10;
			if(l <= cnt && cnt <= r)
				res ++;
		}
	printf("%d\n", res);
}
