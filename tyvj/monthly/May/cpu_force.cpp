#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N_ELE_MAX = 110000;
const int INFINITY = 0x3f3f3f3f;
int data[N_ELE_MAX];
int past[N_ELE_MAX];
int n_data, n_cmd;

int main()
{
	freopen("t.in", "r", stdin);
	//freopen("t.out", "w", stdout);
	scanf("%d", &n_data);
	for(int i = 1; i <= n_data; i ++)
		scanf("%d", &data[i]);
	memcpy(past, data, sizeof(data));
	scanf("%d", &n_cmd);
	while(n_cmd --)
	{
		static char cmd[5];
		int x, y, z;
		scanf("%s%d%d", cmd, &x, &y);
		if(cmd[0] == 'Q')
		{
			int ret = -INFINITY;
			for(int i = x; i <= y; i ++)
				ret = max(ret, data[i]);
			printf("%d\n", ret);
		}
		else if(cmd[0] == 'A')
		{
			int ret = -INFINITY;
			for(int i = x; i <= y; i ++)
				ret = max(ret, past[i]);
			printf("%d\n", ret);
		}
		else
		{
			scanf("%d", &z);
			if(cmd[0] == 'P')
			{
				for(int i = x; i <= y; i ++)
				{
					data[i] += z;
					past[i] = max(past[i], data[i]);
				}
			}
			else
			{
				for(int i = x; i <= y; i ++)
				{
					data[i] = z;
					past[i] = max(past[i], data[i]);
				}
			}
		}
	}
}
