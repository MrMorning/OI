#include <cstdio>
#include <cstring>

struct BigInt
{
	int num[2000];
	void read()
	{
		static char str[3000];
		scanf("%s", str);
		int len = strlen(str);
		for(int i = 0; i < len; i ++)
			num[len - i - 1] = str[i] - '0';
	}
	void print()
	{
		for(int i = 1999; i >= 0; i --)
			if(num[i] != 0)
			{
				for(int j = i; j >= 0; j --)
					printf("%d", num[j]);
				return;
			}
	}
	void div2()
	{
		for(int i = 1999, r = 0; i >= 0; i --)
			if(num[i] != 0)
			{
				for(int j = i; j >= 0; j --)
				{
					r += num[j];
					num[j] = r >> 1;
					r = (r - num[j] * 2) * 10;
				}
				return;
			}
	}
	void minus1()
	{
		for(int i = 1999; i >= 0; i --)
			if(num[i] != 0)
			{
				num[0] -= 1;
				for(int j = 0; j < i; j ++)
				{
					if(num[j] < 0)
					{
						num[j + 1] --;
						num[j] += 10;
					}
				}
				return;
			}
	}
};
BigInt x;
int main()
{
	freopen("t.in", "r", stdin);
	x.read();
	if(x.num[0] & 1)
		x.minus1(), x.div2();
	else
	{
		x.div2();
		x.minus1();
		if((x.num[0] & 1) == 0)
			x.minus1();
	}
	x.print();
}
