#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int oo = 0x3f3f3f3f;
struct Piece
{
	int fig[5][5];
	int topleft, compress;
	char symbol;
} pieceArr[100];
int pieceCnt;
int len;
char board[20][20];

void readData()
{
	scanf("%d", &len);
	for(int i = 0; i < 20; i ++)
	{
		static char str[25];
		scanf("%s", str);
		for(int j = 0; j < 20; j ++)
			board[i][j] = str[j];
	}
}

void scratchFigures()
{
	static bool vis[20][20];
	static int tmp[25][2];
	for(int i = 0; i < 20; i ++)
		for(int j = 0; j < 20; j ++)
			if(isalpha(board[i][j]) && !vis[i][j])
			{
				char ch = board[i][j];
				Piece &now = pieceArr[pieceCnt ++];
				int left = oo;
				int tmpCnt = 0;
				for(int k = i; k < 20; k ++)
					for(int l = 0; l < 20; l ++)
						if(board[k][l] == ch)
						{
							vis[k][l] = true;
							tmp[tmpCnt][0] = k;
							tmp[tmpCnt][1] = l;
							tmpCnt ++;
							left = min(left, l);
						}
				for(int k = 0; k < tmpCnt; k ++)
					now.fig[tmp[k][0] - i][tmp[k][1] - left] = true;
				now.topleft = j - left;
				now.symbol = ch;
			}
}

void rotatePieces()
{
	static int tmp[5][5], now[5][5];
	int block = pieceCnt;
	for(int i = 0; i < block; i ++)
	{
		memcpy(now, pieceArr[i].fig, sizeof(now));
		for(int rot = 0; rot < 3; rot ++)
		{
			int left = oo, top = oo;
			for(int j = 0; j < len; j ++)
				for(int k = 0; k < len; k ++)
					if(now[j][k])
					{
						left = min(left, len - 1 - j);
						top = min(top, k);
					}
			memset(tmp, 0, sizeof(tmp));
			for(int j = 0; j < len; j ++)
				for(int k = 0; k < len; k ++)
					if(now[j][k])
						tmp[k - top][len - 1 - j - left] = true;
			Piece &cur = pieceArr[pieceCnt ++];
			memcpy(cur.fig, tmp, sizeof(tmp));
			for(int k = 0; k < len; k ++)
				if(cur.fig[0][k])
				{
					cur.topleft = k;
					break;
				}
			cur.symbol = pieceArr[i].symbol;
			memcpy(now, tmp, sizeof(now));
		}
	}
}

bool compareByCompress(const Piece &a, const Piece &b)
{
	return a.symbol < b.symbol || (a.symbol == b.symbol && a.compress < b.compress);
}

bool equalByCompress(const Piece &a, const Piece &b)
{
	return a.symbol == b.symbol && a.compress == b.compress;
}

void eliminatePieces()
{
	for(int i = 0; i < pieceCnt; i ++)
	{
		int res = 0;
		for(int j = 0; j < len; j ++)
			for(int k = 0; k < len; k ++)
				if(pieceArr[i].fig[j][k])
					res |= 1 << (j * len + k);
		pieceArr[i].compress = res;
	}
	sort(pieceArr, pieceArr + pieceCnt, compareByCompress);
	pieceCnt = unique(pieceArr, pieceArr + pieceCnt, equalByCompress) - pieceArr;
}

char occupied[5][5];
bool used[26];

bool fit(int i, int j, int k)
{
	const Piece &now = pieceArr[i];
	for(int n = 0; n < len; n ++)
		for(int m = 0; m < len; m ++)
			if(now.fig[n][m])
			{
				int x = j + n, y = k + m - now.topleft;
				if(!(0 <= x && x < len && 0 <= y && y < len))
					return false;
				if(occupied[x][y] != '.')
					return false;
			}
	return true;
}

void place(int i, int j, int k)
{
	const Piece &now = pieceArr[i];
	for(int n = 0; n < len; n ++)
		for(int m = 0; m < len; m ++)
			if(now.fig[n][m])
			{
				int x = j + n, y = k + m - now.topleft;
				occupied[x][y] = now.symbol;
			}
}

void unplace(int i, int j, int k)
{
	const Piece &now = pieceArr[i];
	for(int n = 0; n < len; n ++)
		for(int m = 0; m < len; m ++)
			if(now.fig[n][m])
			{
				int x = j + n, y = k + m - now.topleft;
				occupied[x][y] = '.';
			}
}

void dfs(int i, int j)
{
	if(j == len)
	{
		dfs(i + 1, 0);
		return;
	}
	if(i == len)
	{
		for(int k = 0; k < len; k ++, printf("\n"))
			for(int l = 0; l < len; l ++)
				printf("%c", occupied[k][l]);
		exit(0);
	}
	if(occupied[i][j] != '.')
	{
		dfs(i, j + 1);
		return;
	}
	for(int k = 0; k < pieceCnt; k ++)
		if(!used[pieceArr[k].symbol - 'A'] && fit(k, i, j))
		{
			used[pieceArr[k].symbol - 'A'] = true;
			place(k, i, j);
			dfs(i, j + 1);
			unplace(k, i, j);
			used[pieceArr[k].symbol - 'A'] = false;
		}
}

int main()
{
	readData();
	scratchFigures();
	rotatePieces();
	eliminatePieces();
	for(int i = 0; i < len; i ++)
		for(int j = 0; j < len; j ++)
			occupied[i][j] = '.';
	dfs(0, 0);
	assert(0);
}
