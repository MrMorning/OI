#include <cstdio>
#include <queue>
#define FOR(i,s,t) for(int i = s; i <= t;i++)
#define INF 0x3fffffff
#define MAXN 1010
#define MAXV MAXN * MAXN * 2
#define MAXE 6 * MAXN * MAXN

using std::priority_queue;
using std::vector;

int n,m;
int node[MAXN][MAXN][2];
int count = 0, next[MAXE], begin[MAXV], end[MAXE], weight[MAXE];
int dist[MAXV];
int st,en;

void add_edge(int s,int t,int w)
{
	count++;
	next[count] = begin[s];
	begin[s] = count;	
	end[count] = t;
	weight[count] = w;

	count++;
	next[count] = begin[t];
	begin[t] = count;	
	end[count] = s;
	weight[count] = w;
}

void init()
{

	scanf("%d%d",&n,&m);
	int vNum = 0;
	FOR(i,1,n-1) FOR(j,1,m-1) FOR(k,0,1) node[i][j][k] = ++vNum;
	st = vNum + 1;
	en = vNum + 2;
	FOR(i,1,n)
		FOR(j,1,m-1)
		{
			int t;
			scanf("%d",&t);
			if(i == 1)
			{
				if(n == 1)
					add_edge(st,en,t);
				else
					add_edge(node[i][j][1],en,t);
			}
			else if(i == n)
				add_edge(node[i-1][j][0],st,t);
			else
				add_edge(node[i][j][1],node[i-1][j][0],t);
		}
	FOR(i,1,n-1)
		FOR(j,1,m)
		{
			int t;
			scanf("%d",&t);
			if(j == 1)
			{
				if(m == 1)
					add_edge(st,en,t);
				else
					add_edge(st,node[i][j][0],t);
			}
			else if(j == m)
				add_edge(en,node[i][j-1][1],t);
			else
				add_edge(node[i][j-1][1],node[i][j][0],t);
		}
	FOR(i,1,n-1)
		FOR(j,1,m-1)
		{
			int t;
			scanf("%d",&t);
			add_edge(node[i][j][0],node[i][j][1],t);
		}
}

struct State
{
	int idx, val;
	State(int _idx,int _val):idx(_idx),val(_val){}
};
struct cmp
{
	bool operator()(State a,State b)
	{return a.val>b.val;}
};

int solve()
{
	priority_queue<State,vector<State>,cmp> q;
	q.push(State(st,0));
	FOR(i,0,en) dist[i] = INF;
	dist[st] = 0;
	while(q.size())
	{
		State u = q.top(); q.pop();
		if(u.val > dist[u.idx]) continue;
		if(u.idx == en) return dist[u.idx];
		for(int now = begin[u.idx]; now; now = next[now])
		{
			int v = end[now];
			int tmp = u.val + weight[now];
			if(tmp < dist[v])
			{
				dist[v] = tmp;
				q.push(State(v,tmp));
			}
		}
	}
	return 0;
}

int main()
{
	freopen("t.in","r",stdin);
	init();
	printf("%d\n",solve());
}
