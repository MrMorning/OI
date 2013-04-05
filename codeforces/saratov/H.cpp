/*
 * $Date: Wed Oct 19 10:40:25 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem H
 * $Method: Bipartite Matching + string processing
 */
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int N_MAX = 200, K_MAX = 300;

int toStr[N_MAX * K_MAX];
int hash[531442];
int ans[N_MAX];
int N;
int strIdx;

const int V_MAX = 500000;
const int E_MAX = 2000000;
const int oo = 0x3f3f3f3f;

struct Edge
{
	int to, cap;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];

int nv, sv, tv;
int dist[V_MAX];
int edgeCnt;

Edge *makeEdge(int u, int v, int w)
{
	Edge *e = &edge[edgeCnt ++];
	e->to = v, e->next = begin[u], begin[u] = e;
	e->cap = w;
	return e;
}

void addEdge(int u, int v, int w)
{
	Edge *e1 = makeEdge(u, v, w),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool preLable()
{
	static int queue[V_MAX];

	int qh = 0, qt = 0;
	queue[qt ++] = sv;
	memset(dist, -1, sizeof(dist));
	dist[sv] = 0;
	while(qh < qt)
	{
		int u = queue[qh ++];
		for(Edge *e = begin[u]; e; e =e->next)
			if(e->cap)
			{
				int v = e->to;
				if(dist[v] == -1)
				{
					dist[v] = dist[u] + 1;
					queue[qt ++] = v;
				}
			}
	}
	return dist[tv] != -1;
}

int findAug(int u, int flow)
{
	if(u == tv)
		return flow;
	int res = 0;
	Edge *e;
	for(e = begin[u]; e; e = e->next)
		if(e->cap)
		{
			int v = e->to;
			if(dist[v] != dist[u] + 1)
				continue;
			int tmp = findAug(v, min(flow, e->cap));
			if(tmp)
			{
				flow -= tmp;
				e->cap -= tmp, e->inv->cap += tmp;
				res += tmp;
			}
			if(!flow)
				break;
		}
	if(!e)
		dist[u] = -1;
	return res;
}

int dinic()
{
	int res = 0;
	while(preLable())
		res += findAug(sv, oo);
	return res;
}

int countBits(int x){
	int res = 0;
	while(x)
		res += x & 1, x >>= 1;
	return res;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	memset(hash, -1, sizeof(hash));
	scanf("%d", &N);
	for(int i = 0; i < N; i ++){
		string str;
		cin >> str;
		int upperlim = str.size();
		for(int s = 0; s < 1 << upperlim; s ++)
			if(1 <= countBits(s) && countBits(s) <= 4){
				int tmp = 0;
				for(int d = 0; d < (int)str.size(); d ++)
					if(s & (1 << d))
						tmp = tmp * 27 + (str[d] - 'a' + 1);
				if(hash[tmp] == -1){
					hash[tmp] = strIdx;
					toStr[strIdx] = tmp;
					strIdx ++;
				}
				addEdge(i, N + hash[tmp], 1);
			}
	}
	nv = N + strIdx + 2;
	sv = nv - 2, tv = nv - 1;
	for(int i = 0; i < N; i ++)
		addEdge(sv, i, 1);
	for(int i = N; i < N + strIdx; i ++)
		addEdge(i, tv, 1);
	int maxFlow = dinic();
	if(maxFlow != N){
		printf("-1\n");
		return 0;
	}
	for(int i = 0; i < N; i ++)
		for(Edge *e = begin[i]; e; e = e->next)
			if(e->to != sv)
				if(e->cap == 0){
					ans[i] = toStr[e->to - N];
					break;
				}
	for(int i = 0; i < N; i ++){
		string ts("");
		while(ans[i])
			ts += (char)(ans[i] % 27 + 'a' - 1), ans[i] /= 27; 
		string os("");
		for(int i = 0; i < (int)ts.size(); i ++)
			os += ts[(int)ts.size() - i - 1];
		printf("%s\n", os.c_str());
	}
}
