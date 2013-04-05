#include <cstdlib>
#include <cstring>
const int N_MAX = 100;
int f[N_MAX][N_MAX];
char g[N_MAX][N_MAX][N_MAX], s[N_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%s", s);
	for(int i = 0; i < strlen(s); i ++)
		if(s[i] == '!')
		{
			s[i] = '?';
			insert(i, 2, '?');
		}
	memset(f, 0x3f, sizeof(f));
	int n = strlen(s);
	for(int i = 0; i < n; i ++)
	{
		f[1][i] = s[i] != '*';
		if(isalpha(s[i]))
			g[1][i][0] = s[i];
		else if(s[i] == '?')
			g[1][i][0] = 'a';
	}

	for(int i = 2; i <= n; i ++)
		for(int j = 0; j + i - 1 <= n; j ++)
		{
			char ch1 = s[j], ch2 = s[i + j - 1];
			if(isalpha(ch1) && isalpha(ch2))
			{
				if(ch1 == ch2)
				{
					f[i][j] = f[i - 2][j + 1] + 2;
					g[i][j][0] = ch1;
					memcpy(g[i][j] + 1, g[i - 2][j + 1], sizeof(char) * (i - 2));
					g[i][j][i - 1] = ch2;
				}
				else
					f[i][j] = oo;
			}
			else if(isalpha(ch1) && ch2 == '?')
			{
				f[i][j] = f[i - 2][j + 1] + 2;
				g[i][j][0] = ch1;
				memcpy(g[i][j] + 1, g[i - 2][j + 1], sizeof(char) * (i - 2));
				g[i][j][i - 1] = ch1;
			}
			else if(isalpha(ch1) && ch2 == '*')
			{
				memset(h, 0, sizeof(h));
				int t = 0;
				for(int k = 0; k <= i - 1; k ++)
				{
					if(f[i - k - 1][j + k] + t < f[i][j])
					{
						f[i][j] = f[i - k - 1][j + k] + t;
						for(int l = p + 1; l <= )
						p = k;
					}
				}
				if(s[j + k] != '*')
				{
					h[t ++] = (s[j + k] == '?' ? 'a' : s[j + k]);
				}
			}
		}
}
