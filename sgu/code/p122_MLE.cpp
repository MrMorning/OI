#include <cstdio>
#include <iostream>
#include <sstream>
#include <deque>
#include <cassert>
using namespace std;

const int V_MAX = 1000;

int nv;
bool linked[V_MAX][V_MAX];
deque<int> DQ;
int backup[V_MAX];
bool vis[V_MAX];

void extend(int u, bool flag)
{
	vis[u] = true;
	for(int v = 0; v < nv; v ++)
		if(linked[u][v] && !vis[v])
		{
			if(flag)
				DQ.push_front(v);
			else
				DQ.push_back(v);
			extend(v, flag);
			break;
		}
}

void saveDQ()
{
	for(int i = 0; i < (int)DQ.size(); i ++)
		backup[i] = DQ[i];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &nv);
	for(int i = 0; i < nv; i ++)
	{
		static string str;
		static stringstream stream;
		stream.clear();
		getline(cin, str);
		stream << str;
		int u;
		while(stream >> u)
			linked[i][u - 1] = linked[u - 1][i] = true;
	}

	DQ.push_back(0);
	extend(0, 0);
	extend(0, 1);
	while(1)
	{
		int m = (int)DQ.size();
		if(!linked[DQ[0]][DQ[m - 1]])
		{
			for(int k = 1; k < m - 1; k ++)
				if(linked[DQ[0]][DQ[k]])
					if(linked[DQ[k - 1]][DQ[m - 1]])
					{
						saveDQ();
						DQ.clear();
						for(int i = 0; i <= k - 1; i ++)
							DQ.push_back(backup[i]);
						DQ.push_back(backup[m - 1]);
						for(int i = m - 2; i >= k; i --)
							DQ.push_back(backup[i]);
						assert(DQ.size() == m);
						break;
					}
		}
		if(m == nv)
			break;
		int r, s;
		for(r = 0; r < nv; r ++)
			if(!vis[r])
			{
				bool suc = false;
				for(s = 1; s < m - 1; s ++)
					if(linked[r][DQ[s]])
					{
						suc = true;
						break;
					}
				if(suc)
					break;
			}
		vis[r] = true;
		assert(DQ.size() == m);
		saveDQ();
		DQ.clear();
		DQ.push_back(r);
		for(int i = s; i <= m - 1; i ++)
			DQ.push_back(backup[i]);
		for(int i = 0; i < s; i ++)
			DQ.push_back(backup[i]);
	}

	int i;
	for(i = 0; i < (int)DQ.size(); i ++)
		if(DQ[i] == 0)
			break;
	int m = DQ.size();
	for(int j = i; j < m; j ++)
		printf("%d ", DQ[j] + 1);
	for(int j = 0; j < i; j ++)
		printf("%d ", DQ[j] + 1);
	printf("1\n");
}
