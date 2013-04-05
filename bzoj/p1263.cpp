#include <cstdio>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
const int FAC[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
struct bigInt_t
{
	int num[5001], len;
};
bigInt_t operator+ (const bigInt_t &a, const bigInt_t &b)
{
	bigInt_t c;
	c.len = MAX(a.len, b.len);
	memset(c.num, 0, sizeof(int) * c.len);
	for(int i = 0; i < c.len; i ++)
	{
		c.num[i] += a.num[i] + b.num[i];
		if(c.num[i] >= 100000000)
			c.num[i] -= 100000000, c.num[i + 1] ++;
	}
	if(c.num[c.len])
		c.len ++;
	return c;
}

int main()
{
	int n, times;
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	bigInt_t x;
	memset(x.num, 0, sizeof(x.num));
	x.len = 1;
	if(n % 3 == 0)
		times = n / 3 - 1, x.num[0] = 3;
	else if(n % 3 == 1)
		times = n / 3 - 1, x.num[0] = 4;
	else
		times = n / 3, x.num[0] = 2;
	for(int i = 0; i < times; i ++)
		x = x + x + x;
	int tmp = x.num[x.len - 1];
	int uppestCnt = 0;
	while(tmp)
		uppestCnt ++, tmp /= 10;
	printf("%d\n", 8 * (x.len - 1) + uppestCnt);
	int nPrint = ((100 - uppestCnt) / 8);
	int downlim = ((8 * (x.len - 1) + uppestCnt > 100) ? x.len - nPrint - 1 : 0);
	printf("%d", x.num[x.len - 1]);	
	for(int i = x.len - 2; i >= downlim; i --)
	{
		int tmp = x.num[i];
		int cnt = 0;
		while(tmp)
			cnt ++, tmp /= 10;
		for(int j = 0; j < 8 - cnt; j ++)
			printf("0");
		printf("%d", x.num[i]);	
	}
	if(downlim > 0)
	{
		tmp = x.num[downlim - 1];
		for(int i = 0; i < 100 - uppestCnt - 8 * nPrint; i ++)
			if(tmp >= FAC[7 - i])
				printf("%d", (tmp / FAC[7 - i]) % 10);
			else
				printf("0");
	}
	printf("\n");
}
