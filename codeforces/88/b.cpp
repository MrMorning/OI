#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
int main()
{
	//freopen("t.in", "r", stdin);
	int a, b, m;
	scanf("%d%d%d", &a, &b, &m);
	if(b >= m)
		printf("2\n");
	else
	{
		for(int t = 0; t <= min(a, m - 1); t ++)
			if((ll)ceil((double)((ll)t * 1000000000LL) / m) > (ll)floor((double)((ll)t * 1000000000LL + b) / m))
			{
				printf("1 ");
				int tmp = t, cnt = t == 0;
				while(tmp)
					cnt ++, tmp /= 10;
				for(int i = 0; i < 9 - cnt; i ++)
					printf("0");
				printf("%d\n", t);
				return 0;
			}
		printf("2\n");
	}
}
