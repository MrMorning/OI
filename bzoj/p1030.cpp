#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#define DEBUG
namespace Solve
{
	const int MAXN = 71,
		  MAXM = 120,
		  NODE_MAX = 7000;

	struct Node
	{
		int vtx[26], fail;	
		bool isPattern;
	} trie[NODE_MAX];
	int queue[NODE_MAX];
	int nTrie, nPattern;
	int pattern[MAXN][MAXM], lPattern[MAXN];
	int f[MAXM][NODE_MAX][2];
	bool vis[NODE_MAX];
	void dfs(int, int);
	void buildAutoMaton();
	void solve();
	void debug(int);
}

void Solve::buildAutoMaton()
{
	memset(trie, 0, sizeof(trie));
	nTrie = 1;
	for(int i = 0; i < nPattern; i ++)
	{
		int u = 0;
		for(int j = 0; j < lPattern[i]; j ++)
			if(int v = trie[u].vtx[pattern[i][j]])
				u = v;
			else
				u = trie[u].vtx[pattern[i][j]] = nTrie ++;
		trie[u].isPattern = true;
	}
	int qh = 0, qt = 0;
	for(int a = 0; a < 26; a ++)
		if(int u = trie[0].vtx[a])
			queue[qt ++] = u;
	for(;qh != qt; qh ++)
	{
		int u = queue[qh];
		for(int a = 0; a < 26; a ++)
		{
			int v = trie[u].vtx[a];
			if(v)
			{
				queue[qt ++] = v;
				trie[v].fail = trie[trie[u].fail].vtx[a];
			}
			else
				trie[u].vtx[a] = trie[trie[u].fail].vtx[a];
			trie[v].isPattern |= trie[trie[v].fail].isPattern;//very important
		}
	}
}

inline void increase(int &a, int b)
{
	a = (a + b) % 10007;
}

void Solve::solve()
{
	int m;
	scanf("%d %d\n", &nPattern, &m);
	for(int i = 0; i < nPattern; i ++)
	{
		std::string str;
		std::cin >> str;
		lPattern[i] = str.size();
		for(int j = 0; j < lPattern[i]; j ++)
			pattern[i][j] = str[j] - 'A';
	}
	buildAutoMaton();
	f[0][0][0] = 1;
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < nTrie; j ++)
			for(int k = 0; k < 26; k ++)
			{
				int l = trie[j].vtx[k];
				if(trie[l].isPattern)
					increase(f[i + 1][l][1], f[i][j][0]);
				else
					increase(f[i + 1][l][0], f[i][j][0]);
				increase(f[i + 1][l][1], f[i][j][1]);
			}
	int ans = 0;
	for(int j = 0; j < nTrie; j ++)
		increase(ans, f[m][j][1]);
	printf("%d\n", ans);
}

int main()
{
#ifdef DEBUG
	freopen("t.in", "r", stdin);
#endif
	Solve::solve();
}
