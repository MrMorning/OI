#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define S_MAX 1000

using namespace std;

bool solFlag, tieFlag;
int val[S_MAX], strategy[4], ansStrategy[4];
bool used[S_MAX];
int ansDiff, ansCnt, ansMax;
int stampCnt;

void dfs(int i, int cnt, int begin)
{
	if(cnt == 0)
	{
		solFlag = true;
		int diff = 0, curMax = -1;
		memset(used, 0, sizeof(int) * stampCnt);
		for(int k = 0; k < i; k ++)
		{
			if(!used[strategy[k]])
				used[strategy[k]] = true, diff ++;
			curMax = max(curMax, val[strategy[k]]);
		}
		if(diff > ansDiff || (diff == ansDiff && i < ansCnt) || (diff == ansDiff && i == ansCnt && curMax > ansMax))
		{
			tieFlag = false;
			ansDiff = diff;
			ansCnt = i;
			ansMax = curMax;
			memcpy(ansStrategy, strategy, sizeof(strategy));
		}
		else if(diff == ansDiff && i == ansCnt && curMax == ansMax)
			tieFlag = true;
		return;
	}
	if(i == 4)
		return;
	for(int j = begin; j < stampCnt; j ++)
		if(cnt >= val[j])
		{
			strategy[i] = j;
			dfs(i + 1, cnt - val[j], j);
		}
}

void solve(int lim)
{
	ansDiff = ansCnt = ansMax = -1; 
	tieFlag = solFlag = false;
	dfs(0, lim, 0);
	if(!solFlag)
		printf("%d ---- none\n", lim);
	else if(tieFlag)
		printf("%d (%d): tie\n", lim, ansDiff);
	else
	{
		printf("%d (%d):", lim, ansDiff);
		for(int i = 0; i < ansCnt; i ++)
			printf(" %d", val[ansStrategy[i]]);
		printf("\n");
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int t;
	while (!cin.eof())
	{
		stampCnt = 0;
		cin >> t;
		while(t != 0)
			val[stampCnt ++] = t, cin >> t;
		sort(val, val + stampCnt);
		cin >> t;
		while(t != 0)
		{
			solve(t);
			cin >> t;
		}
	}
}
