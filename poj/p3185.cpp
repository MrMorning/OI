/*
 * Date: Sat Jan 29 16:52:42 CST 2011
 * Author: csimstu
 * Problem: poj3185
 * Algorithm: Greedy
 */
#include <cstdio>
#include <cstring>
int a[22], b[22], ans;

int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 1; i <= 20; i ++)
		scanf("%d", &a[i]);
	memcpy(b, a, sizeof(a));
	//1.do not turn a[1]
	int cnt = 0;
	for(int i = 2; i <= 20; i ++)
		if(a[i - 1])
		{
			cnt ++;
			a[i - 1] ^= 1;
			a[i] ^= 1;
			a[i + 1] ^= 1;
		}
	ans = cnt;
	memcpy(a, b, sizeof(a));
	//2. turn a[1]
	cnt = 1;
	a[1] ^= 1;
	a[2] ^= 1;
	for(int i = 2; i <= 20; i ++)
		if(a[i - 1])
		{
			cnt ++;
			a[i - 1] ^= 1;
			a[i] ^= 1;
			a[i + 1] ^= 1;
		}
	ans = ans < cnt ? ans : cnt;
	printf("%d\n", ans);
}
