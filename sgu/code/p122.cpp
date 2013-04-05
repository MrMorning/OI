#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int V_MAX = 1000;

int nv;
bool linked[V_MAX][V_MAX];
int backup[V_MAX];
bool vis[V_MAX];

struct DoubleQueue
{
	int ele[V_MAX], qh, qt;
	inline int size()
	{
		if(qt == qh)
			return nv;
		else
			return (qt - qh + nv) % nv;
	}
	void push_back(int x)
	{
		ele[qt] = x;
		qt = (qt + 1) % nv;
	}
	void push_front(int x)
	{
		qh = (qh - 1 + nv) % nv;
		ele[qh] = x;
	}
	int &operator[] (const int &i)
	{
		return ele[(qh + i) % nv];
	}
	void clear()
	{
		qh = qt = 0;
	}
} DQ;

void extend(int u, bool flag)
{
	while(1)
	{
		vis[u] = true;
		bool suc = false;
		for(int v = 0; v < nv; v ++)
			if(linked[u][v] && !vis[v])
			{
				if(flag)
					DQ.push_front(v);
				else
					DQ.push_back(v);
				u = v;
				suc = true;
				break;
			}
		if(!suc)
			break;
	}
}

void saveDQ()
{
	for(int i = 0; i < (int)DQ.size(); i ++)
		backup[i] = DQ[i];
}
string str;
void readData()
{
	scanf("%d\n", &nv);
	int x = 0;
	for(int i = 0; i < nv; i ++)
	{
		getline(cin, str);
		for(int j = 0; j < str.length(); j ++)
		{
			char ch = str[j];
			if('0' <= ch && ch <= '9')
				x = x * 10 + ch - '0';
			if(ch == ' ' || j == str.length() - 1)
			{
				if(x)
					linked[i][x - 1] = linked[x - 1][i] = true;
				x = 0;
			}
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	readData();

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
