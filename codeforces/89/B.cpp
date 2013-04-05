#include <cstdio>
#include <algorithm>
using namespace std;
int res[20][20];
char out[20][40];
int stop[20];
int main()
{
//	freopen("t.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 0; i < 2 * n + 1; i ++)
		for(int j = 0; j < 2 * n + 1; j ++)
			if(abs(i - n) + abs(j - n) > n)
				res[i][j] = -1;
			else
				res[i][j] = n - (abs(i - n) + abs(j - n));
	for(int i = 0; i < 2 * n + 1; i ++)
		for(int j = 0; j < 2 * n + 1; j ++)
			if(res[i][j] == -1)
				out[i][j * 2] = ' ', out[i][j * 2 + 1] = ' ';
			else
				out[i][j * 2] = (char)('0' + res[i][j]), out[i][j * 2 + 1] = ' ';
	for(int i = 0; i < 2 * n + 1; i ++)
		for(int j = 4 * n; j >= 0; j --)
			if('0' <= out[i][j] && out[i][j] <= '9')
			{
				stop[i] = j;
				break;
			}
	for(int i = 0; i < 2 * n + 1; i ++, printf("\n"))
		for(int j = 0; j <= stop[i]; j ++)
			printf("%c", out[i][j]);
}
