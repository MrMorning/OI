#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;
const int N_MAX = 1010;
const int oo = 0x3f3f3f3f;
int f[N_MAX][N_MAX];
int g[N_MAX][N_MAX];
char input[N_MAX], s[N_MAX];

string out(int i, int j)
{
	if(i == 0)
		return "";
	else if(i == 1)
	{
		if(s[j] == '*')
			return "";
		else if(s[j] == '?')
			return "a";
		return (string() + s[j]);
	}
	char ch1 = s[j], ch2 = s[i + j - 1];
	if(isalpha(ch1) && isalpha(ch2))
	{
		assert(ch1 == ch2);
		return ch1 + out(i - 2, j + 1) + ch2;
	}
	else if(isalpha(ch1) && ch2 == '?')
		return ch1 + out(i - 2, j + 1) + ch1;
	else if((isalpha(ch1) || ch1 == '?') && ch2 == '*')
	{
		int k = g[i][j];
		assert(k != -1);
		string res = out(i - k - 1, j + k);
		for(int l = j + k - 1; l >= j; l --)
			if(s[l] != '*')
				res = (s[l] == '?' ? 'a' : s[l]) + res + (s[l] == '?' ? 'a' : s[l]);
		return res;
	}
	else if(ch1 == '?' && isalpha(ch2))
		return ch2 + out(i - 2, j + 1) + ch2;
	else if(ch1 == '?' && ch2 == '?')
		return 'a' + out(i - 2, j + 1) + 'a';
	else if(ch1 == '*' && (ch2 == '?' || isalpha(ch2)))
	{
		int k = g[i][j];
		string res = out(i - k - 1, j + 1);
		for(int l = i + j - k; l <= i + j - 1; l ++)
			if(s[l] != '*')
				res = (s[l] == '?' ? 'a' : s[l]) + res + (s[l] == '?' ? 'a' : s[l]);
		return res;
	}
	else if(ch1 == '*' && ch2 == '*')
	{
		if(g[i][j] == 0)
			return out(i - 1, j);
		else
			return out(i - 1, j + 1);
	}
	else
		assert(0);
}

int main()
{
	freopen("t.in", "r", stdin);
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
	memset(g, -1, sizeof(g));
	memset(f[0], 0, sizeof(f[0]));
	for(int i = 0; i < n; i ++)
		f[1][i] = s[i] != '*';

	for(int i = 2; i <= n; i ++)
		for(int j = 0; j + i - 1 < n; j ++)
		{
			char ch1 = s[j], ch2 = s[i + j - 1];
			if(isalpha(ch1) && isalpha(ch2))
			{
				if(ch1 == ch2)
					f[i][j] = f[i - 2][j + 1] + 2;
				else
					f[i][j] = oo;
			}
			else if(isalpha(ch1) && ch2 == '?')
				f[i][j] = f[i - 2][j + 1] + 2;
			else if((isalpha(ch1) || ch1 == '?') && ch2 == '*')
			{
				int t = 0;
				for(int k = 0; k <= i - 1; k ++)
				{
					int tmp = f[i - k - 1][j + k] + 2 * t;
					if(tmp < f[i][j])
					{
						f[i][j] = tmp;
						g[i][j] = k;
					}
					if(s[j + k] != '*')
						t ++;
				}
			}
			else if(ch1 == '?' && isalpha(ch2))
				f[i][j] = f[i - 2][j + 1] + 2;
			else if(ch1 == '?' && ch2 == '?')
				f[i][j] = f[i - 2][j + 1] + 2;
			else if(ch1 == '*' && (isalpha(ch2) || ch2 == '?'))
			{
				int t = 0;
				for(int k = 0; k <= i - 1; k ++)
				{
					int tmp = f[i - k - 1][j + 1] + 2 * t;
					if(tmp < f[i][j])
					{
						f[i][j] = tmp;
						g[i][j] = k;
					}
					if(s[i + j - 1 - k] != '*')
						t ++;
				}
			}
			else if(ch1 == '*' && ch2 == '*')
			{
				f[i][j] = f[i - 1][j], g[i][j] = 0;
				if(f[i - 1][j + 1] < f[i][j])
					f[i][j] = f[i - 1][j + 1], g[i][j] = 1;
			}
			else
				assert(0);
		}
	if(f[n][0] >= oo)
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
//	assert((int)out(n, 0).size() == f[n][0]);
	printf("%s\n", out(n, 0).c_str());
}
