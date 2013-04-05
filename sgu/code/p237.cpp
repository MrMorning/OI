#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;
const int N_MAX = 1010;
const int oo = 0x3f3f3f3f;
int f[3][N_MAX];
char g[3][N_MAX][N_MAX];
char input[N_MAX], s[N_MAX], ts[N_MAX];

int main()
{
	scanf("%s", input);
	int n = 0;
	for(int i = 0; i < (int)strlen(input); i ++)
		if(input[i] == '!')
		{
			s[n ++] = '?';
			s[n ++] = '?';
			s[n ++] = '?';
		}
		else
			s[n ++] = input[i];

	memset(f, 0x3f, sizeof(f));
	memset(f[0], 0, sizeof(f[0]));
	for(int i = 0; i < n; i ++)
		if(s[i] != '*')
		{
			f[1][i] = 1;
			g[1][i][0] = s[i] == '?' ? 'a' : s[i];
		}
		else
			f[1][i] = 0;
		

	for(int i = 2; i <= n; i ++)
		for(int j = 0; j + i - 1 < n; j ++)
		{
			f[i % 3][j] = oo;
			memset(g[i % 3][j], 0, sizeof(g[i % 3][j]));
			char ch1 = s[j], ch2 = s[i + j - 1];
			if(isalpha(ch1) && (isalpha(ch2) || ch2 == '?'))
			{
				if(ch2 == '?')
					ch2 = ch1;
				if(ch1 == ch2)
				{
					if(f[(i - 2) % 3][j + 1] >= oo)
						continue;
					f[i % 3][j] = f[(i - 2) % 3][j + 1] + 2;
					g[i % 3][j][0] = ch1;
					strncpy(g[i % 3][j] + 1, g[(i - 2) % 3][j + 1], f[(i - 2) % 3][j + 1]);
					g[i % 3][j][f[(i - 2) % 3][j + 1] + 1] = ch1;
				}
			}
			else if((isalpha(ch1) || ch1 == '?') && ch2 == '*')
			{
				if(ch1 == '?')
					ch1 = 'a';
				f[i % 3][j] = f[(i - 1) % 3][j];
				strcpy(g[i % 3][j], g[(i - 1) % 3][j]);
				if(f[(i - 1) % 3][j + 1] >= oo)
					continue;
				memset(ts, 0, sizeof(ts));
				ts[0] = ch1;
				strncpy(ts + 1, g[(i - 1) % 3][j + 1], f[(i - 1) % 3][j + 1]);
				ts[f[(i - 1) % 3][j + 1] + 1] = ch1;
				int tmp = f[(i - 1) % 3][j + 1] + 2;
				if(f[i % 3][j] > tmp || (f[i % 3][j] == tmp && strcmp(ts, g[i % 3][j]) < 0))
					f[i % 3][j] = tmp, strcpy(g[i % 3][j], ts);
			}
			else if(ch1 == '?' && (isalpha(ch2) || ch2 == '?'))
			{
				if(f[(i - 2) % 3][j + 1] >= oo)
					continue;
				if(ch2 == '?')
					ch2 = 'a';
				ch1 = ch2;
				f[i % 3][j] = f[(i - 2) % 3][j + 1] + 2;
				g[i % 3][j][0] = ch2;
				strncpy(g[i % 3][j] + 1, g[(i - 2) % 3][j + 1], f[(i - 2) % 3][j + 1]);
				g[i % 3][j][f[(i - 2) % 3][j + 1] + 1] = ch2;
			}
			else if(ch1 == '*' && (isalpha(ch2) || ch2 == '?'))
			{
				if(ch2 == '?')
					ch2 = 'a';
				f[i % 3][j] = f[(i - 1) % 3][j + 1];
				strcpy(g[i % 3][j], g[(i - 1) % 3][j + 1]);
				if(f[(i - 1) % 3][j] >= oo)
					continue;
				memset(ts, 0, sizeof(ts));
				ts[0] = ch2;
				strncpy(ts + 1, g[(i - 1) % 3][j], f[(i - 1) % 3][j]);
				ts[f[(i - 1) % 3][j] + 1] = ch2;
				int tmp = f[(i - 1) % 3][j] + 2;
				if(f[i % 3][j] > tmp || (f[i % 3][j] == tmp && strcmp(ts, g[i % 3][j]) < 0))
					f[i % 3][j] = tmp, strcpy(g[i % 3][j], ts);
			}
			else if(ch1 == '*' && ch2 == '*')
			{
				f[i % 3][j] = f[(i - 1) % 3][j], strcpy(g[i % 3][j], g[(i - 1) % 3][j]);
				if(f[(i - 1) % 3][j + 1] < f[i % 3][j] || (f[(i - 1) % 3][j + 1] == f[i % 3][j] && strcmp(g[(i - 1) % 3][j + 1], g[i % 3][j]) < 0))
					f[i % 3][j] = f[(i - 1) % 3][j + 1], strcpy(g[i % 3][j], g[(i - 1) % 3][j + 1]);
			}
			else
				assert(0);
		}
	if(f[n % 3][0] >= oo)
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	printf("%s\n", g[n % 3][0]);
}
