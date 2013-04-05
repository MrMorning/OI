#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using std::string;
using std::cin;

const int SCORE[5][5] = {{5, -1, -2, -1, -3},
						{-1, 5, -3, -2, -4},
						{-2, -3, 5, -2, -2},
						{-1, -2, -2, 5, -1},
						{-3, -4, -2, -1, -127}};
const int MAXN = 101;
string s1, s2;
int a[MAXN], b[MAXN];
int f[MAXN][MAXN];
int len1, len2;

inline int max(int a, int b)
{return a > b ? a: b;}

inline void Update(int &a, int b)
{a = max(a, b);}

int Map(char ch)
{
	switch(ch)
	{
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
	}
	return -1;
}

int main()
{
	freopen("t.in", "r", stdin);
	int testNum;
	scanf("%d\n", &testNum);
	while(testNum --)
	{
		cin >> len1 >> s1 >> len2 >> s2;
		for(int i = 0; i < s1.length(); i ++)
			a[i+1] = Map(s1[i]);
		for(int i = 0; i < s2.length(); i ++)
			b[i+1] = Map(s2[i]);
		memset(f, -0x3f, sizeof(f));
		f[0][0] = 0;
		for(int i = 1; i <= len1; i ++)
			f[i][0] = f[i-1][0] + SCORE[a[i]][4];
		for(int j = 1; j <= len2; j ++)
			f[0][j] = f[0][j-1] + SCORE[b[j]][4];
		for(int i = 1; i <= len1; i ++)
			for(int j = 1; j <= len2; j ++)
			{
				Update(f[i][j], f[i-1][j-1] + SCORE[a[i]][b[j]]);
				Update(f[i][j], f[i-1][j] + SCORE[4][a[i]]);
				Update(f[i][j], f[i][j-1] + SCORE[b[j]][4]);
			}
		printf("%d\n", f[len1][len2]);
	}
}
