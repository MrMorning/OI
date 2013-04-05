#include <cstdio>
#include <cstring>
#include <cstdlib>
#define TEST_TIMES 100
char func[1000], buffer[1000];
int n_buffer;
double ans[2];
int ans_cnt, ans_type;
double solve(double x, int len)
{
	if(len == 0)
		return 0;

	int times = 1, fac_pos = len;
	bool x_found = false;
	for(int i = 0; i < len; i ++)
		if(buffer[i] == '^')
		{
			times = buffer[i + 1] - '0';
			fac_pos = i;
			break;
		}
		else if(buffer[i] == 'x')
			x_found = true;
	double ret = 1;
	if(x_found)
		for(int i = 0; i < times; i ++)
			ret *= x;
	else
		fac_pos = len + 1;
	int tmp = 0;
	for(int i = 0; i < fac_pos - 1; i ++)
		tmp = tmp * 10 + buffer[i] - '0';
	if(fac_pos == 1)
		tmp = 1;
	return ret * tmp;
}
double calc(double x)
{
	double ret = 0;
	int pre_flag = 1;
	for(int i = 0; i <= (int) strlen(func); i ++)
	{
		if(func[i] == '+' || func[i] == '-' || i == (int) strlen(func))
		{
			ret += pre_flag * solve(x, n_buffer);
			n_buffer = 0;
			pre_flag = func[i] == '+' ? 1 : -1;
		}
		else
			buffer[n_buffer ++] = func[i];
	}
	return ret;
}
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 0; i < 5; i ++)
		getchar();
	scanf("%s", func);
	for(int mid = -10; mid <= 10; mid += 1)
	{
		bool failed = false;
		for(int i = 1; i <= TEST_TIMES; i ++)
		{
			int x1 = (rand() % 2000 - 1000) / 100;
			int x2 = mid * 2 - x1;
			if(calc(x1) != calc(x2))
				failed = true;
		}
		if(! failed)
		{
			ans[0] = mid;
			ans_type = 1;
			ans_cnt ++;
		}
	}
	for(int mid = -10, height; mid <= 10; mid += 1)
	{
		bool failed = false;
		for(int i = 1; i <= TEST_TIMES; i ++)
		{
			int x1 = (rand() % 2000 - 1000) / 100;
			int x2 = mid * 2 - x1;
			if(i == 1)
				height = (calc(x1) + calc(x2)) / 2;
			else
				if((calc(x1) + calc(x2)) / 2 != height)
					failed = true;
		}
		if(! failed)
		{
			ans[0] = mid;
			ans[1] = height;
			ans_type = 2;
			ans_cnt ++;
		}
	}
	if(ans_cnt > 1)
		printf("all\n");
	else if(ans_type == 1)
		printf("%.0f\n", ans[0]);
	else
		printf("%.0f %.0f\n", ans[0], ans[1]);
}
