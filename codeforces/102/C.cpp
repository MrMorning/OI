#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <algorithm>
#define IN_RANGE(x, y) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
using namespace std;

const int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const bool base[1][3][3] = {
	{	
		{1, 1, 1},
		{0, 1, 0},
		{0, 1, 0}
	}
};

char board[10][10];
bool used[12];
bool hash[1 << 17];

struct Pattern
{
	bool figure[3][3];
	char symbol;
	int upleft[2];//the coordinate of one black point
	int hash;
	Pattern(){}
	Pattern(bool _figure[3][3], char _symbol)
		:symbol(_symbol)
	{
		static bool tmp[3][3];
		memcpy(figure, _figure, sizeof(figure));
		int low_left = 0, low_down = 0;
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(figure[i][j])
				{
					low_left = max(low_left, i);
					low_down = max(low_down, j);
				}
		memcpy(tmp, figure, sizeof(figure));
		memset(figure, 0, sizeof(figure));
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
			{
				int p = i - (2 - low_left),
					q = j - (2 - low_down);
				if(0 <= p && p <= 2 && 0 <= q && q <= 2)
					figure[i][j] = tmp[p][q];
			}
		hash = 0;
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(figure[i][j])
					hash |= 1 << (i * 3 + j); 
		bool flag = false;
		for(int i = 0; !flag && i < 3; i ++)
			for(int j = 0; !flag && j < 3; j ++)
				if(figure[i][j])
				{
					upleft[0] = i, upleft[1] = j;
					flag = true;
				}
	}

	bool operator< (const Pattern &t) const
	{return hash > t.hash;}
	bool operator== (const Pattern &t) const
	{return hash == t.hash;}

	bool can_place(int x, int y)
	{
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(figure[i][j])
				{
					int p = i - upleft[0] + x,
						q = j - upleft[1] + y;
					if(!IN_RANGE(p, q))
						return false;
					if(board[p][q] != '.')
						return false;
				}
		return true;
	}
	void place(int x, int y)
	{
		assert(can_place(x, y));
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(figure[i][j])
				{
					int p = i - upleft[0] + x,
						q = j - upleft[1] + y;
					board[p][q] = symbol;
				}
	}
	void clear(int x, int y)
	{
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 3; j ++)
				if(figure[i][j])
				{
					int p = i - upleft[0] + x,
						q = j - upleft[1] + y;
					board[p][q] = '.';
				}
	}
} pattern[200];
int n_pattern;

void generate()
{
	static bool tmp[3][3], cur[3][3];
	for(int i = 0; i < 1; i ++)
	{
		memcpy(cur, base[i], sizeof(cur));
		for(int j = 0; j < 4; j ++)
		{
			pattern[n_pattern ++] = Pattern(cur, (char)(i + 'A'));

			memset(tmp, 0, sizeof(tmp));
			for(int p = 0; p < 3; p ++)
				for(int q = 0; q < 3; q ++)
					tmp[2 - p][q] = cur[p][q];
			pattern[n_pattern ++] = Pattern(tmp, (char)(i + 'A'));

			memset(tmp, 0, sizeof(tmp));
			for(int p = 0; p < 3; p ++)
				for(int q = 0; q < 3; q ++)
					tmp[p][2 - q] = cur[p][q];
			pattern[n_pattern ++] = Pattern(tmp, (char)(i + 'A'));

			memset(tmp, 0, sizeof(tmp));
			for(int p = 0; p < 3; p ++)
				for(int q = 0; q < 3; q ++)
					tmp[2 - p][2 - q] = cur[p][q];
			pattern[n_pattern ++] = Pattern(tmp, (char)(i + 'A'));

			memset(tmp, 0, sizeof(tmp));
			for(int p = 0; p < 3; p ++)
				for(int q = 0; q < 3; q ++)
					tmp[q][2 - p] = cur[p][q];
			memcpy(cur, tmp, sizeof(tmp));
		}
	}
}

int calc_adj(int i, int j)//find the number of empty blocks close to (i, j)
{
	assert(board[i][j] == '.');
	int res = 0;
	for(int d = 0; d < 4; d ++)
	{
		int ni = i + offset[d][0],
			nj = j + offset[d][1];
		if(IN_RANGE(ni, nj))
			if(board[ni][nj] == '.')
				res ++;
	}
	return res;
}

void search(int x, int y, int res)
{
	if(x == n)
	{
	//	for(int i = 0; i < 12; i ++)
	//		assert(used[i]);
		printf("%d\n", res);
		for(int i = 0; i < n; i ++, printf("\n"))
			for(int j = 0; j < m; j ++)
				printf("%c", board[i][j]);
		exit(0);
	}
	if(y >= m)
	{
		search(x + 1, 0, res);
		return;
	}
	if(board[x][y] == '.')
	{
		for(int k = 0; k < n_pattern; k ++)
			if(!used[pattern[k].symbol - 'A'])
				if(pattern[k].can_place(x, y))
				{
					pattern[k].place(x, y);
					used[pattern[k].symbol - 'A'] = true;
					search(x, y + 1, res + 1);
					used[pattern[k].symbol - 'A'] = false;
					pattern[k].clear(x, y);
				}
	}
	else
		search(x, y + 1, res);
}

int main()
{
	freopen("t.in", "r", stdin);
	generate();
	sort(pattern, pattern + n_pattern);
	n_pattern = unique(pattern, pattern + n_pattern) - pattern;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			board[i][j] = '.';
	search(0, 0);
}
