#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo = 0x3f3f3f3f;
int n, m;
int board[150][150];
int left[150], right[150];
char str[200];
int res;

int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
	{
		scanf("%s", str);
		for(int j = 0; j < m; j ++)
			board[i][j] = str[j] == 'W';
	}
	board[0][0] = 1;
	memset(left, -1, sizeof(left));
	memset(right, -1, sizeof(right));
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
		if(board[i][j])
		{
			if(left[i] == -1)
				left[i] = j;
		}
	for(int i = n - 1; i >= 0 && left[i] == -1; i --)
		n --;
	for(int i = 0; i < n; i ++)
		for(int j = m - 1; j >= 0; j --)
			if(board[i][j])
			{
				if(right[i] == -1)
					right[i] = j;
			}
	int now = 1, pos = 0;
	for(int i = 0; i < n; i ++, now ^= 1)
	{
		if(i < n && left[i + 1] == -1)
		{
			if(now == 0)
				left[i + 1] = right[i + 1] = left[i];
			else
				left[i + 1] = right[i + 1] = right[i];
		}
		if(now == 0)
		{
			res += pos - min(left[i], (i < n - 1) ? left[i + 1] : oo);
			pos = min(left[i], (i < n - 1) ? left[i + 1] : oo);
		}
		else
		{
			res += max(right[i], (i < n - 1) ? right[i + 1] : -oo) - pos;
			pos = max(right[i], (i < n - 1) ? right[i + 1] : -oo);
		}
	}
	printf("%d\n", res + n - 1);
}
