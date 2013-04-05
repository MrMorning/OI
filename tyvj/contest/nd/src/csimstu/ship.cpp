#include <cstdio>
#include <algorithm>
using namespace std;
int a[201], tmp[201];
int aMax, tmpCnt;
int n;
int main()
{
	freopen("ship.in", "r", stdin);
	freopen("ship.out", "w", stdout);
	int _;
	scanf("%d", &_);
	while(_ --)
	{
		scanf("%d", &n);
		aMax = 0;
		for(int i = 0; i < n; i ++)
		{
			scanf("%d", &a[i]);
			aMax = max(aMax, a[i]);
		}
		tmpCnt = 0;
		for(int i = 0; i < n; i ++)
			if(a[i] == aMax)
				tmp[tmpCnt ++] = i;
		if(tmpCnt <= 2)
		{
			printf("T_T\n");
			continue;
		}
		tmp[tmpCnt] = tmp[0] + n;
		bool fail = false;
		for(int i = 0; i < tmpCnt; i ++)
			if(tmp[i + 1] - tmp[i] >= (n - 1) / 2 + 1)
			{
				printf("T_T\n");
				fail = true;
				break;
			}
		if(fail)
			continue;
		printf("Yeah!\n");
	}
}
