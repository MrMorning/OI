#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int V_MAX = 2000;
const int E_MAX = 10000;
const double EPS = 10e-8;

struct Edge{
	double cap;
	int to, lab;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];

struct DataEdge{
	int u, v, c;
} ed[E_MAX];

int edgeCnt;
int level[V_MAX];
int nv, ne;
bool vis[V_MAX];
vector<int> out;

Edge *makeEdge(int u, int v, double cap){
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}

void addEdge(int u, int v, double cap, int lab){
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
	e1->lab = lab, e2->lab = -1;
}

bool preLable(){
	static int Q[V_MAX];
	memset(level, -1, sizeof(level));
	level[1] = 0;
	int qh = 0, qt = 0;
	Q[qt ++] = 1;
	while(qh < qt){
		int u = Q[qh ++];
		for(Edge *e = begin[u]; e; e = e->next)
			if(e->cap > EPS){
				int v = e->to;
				if(level[v] == -1){
					level[v] = level[u] + 1;
					Q[qt ++] = v;
				}
			}
	}
	return level[nv] != -1;
}

double findAug(int u, double flow){
	if(u == nv)
		return flow;
	double res = 0;
	Edge *e;
	for(e = begin[u]; e; e = e->next)
		if(e->cap > EPS){
			int v = e->to;
			if(level[v] == level[u] + 1){
				double tmp = findAug(v, min(flow, e->cap));
				e->cap -= tmp;
				e->inv->cap += tmp;
				flow -= tmp;
				res += tmp;
				if(flow < EPS)
					break;
			}
		}
	if(!e)
		level[u] = -1;
	return res;
}

double dinic(){
	double res = 0;
	while(preLable())
		res += findAug(1, 10e100);
	return res;
}

double calc(double lamda){
	memset(begin, 0, sizeof(begin));
	edgeCnt = 0;
	double res = 0;
	for(int i = 1; i <= ne; i ++){
		if(ed[i].c - lamda <= 0){
			res += ed[i].c - lamda;
			continue;
		}
		addEdge(ed[i].u, ed[i].v, ed[i].c - lamda, i);
		addEdge(ed[i].v, ed[i].u, ed[i].c - lamda, i);
	}
	return res + dinic();
}

void dfs(int x){
	vis[x] = true;
	for(Edge *e = begin[x]; e; e = e->next)
		if(!vis[e->to] && e->cap > EPS)
			dfs(e->to);
}

void solve(int n, int m){
	nv = n, ne = m;
	int uplim = 0;
	for(int i = 1; i <= m; i ++){
		scanf("%d%d%d", &ed[i].u, &ed[i].v, &ed[i].c);
		uplim += ed[i].c;
	}
	double lb = 0, rb = uplim;
	for(int rep = 0; rep < 51; rep ++){
		double mid = (lb + rb) / 2;
		if(calc(mid) < 0)
			rb = mid;
		else
			lb = mid;
	}
	memset(begin, 0, sizeof(begin));
	edgeCnt = 0;
	out.clear();
	for(int i = 1; i <= m; i ++){
		if(ed[i].c - lb <= 0){
			out.push_back(i);
			continue;
		}
		addEdge(ed[i].u, ed[i].v, ed[i].c - lb, i);
		addEdge(ed[i].v, ed[i].u, ed[i].c - lb, i);
	}
	dinic();

	memset(vis, 0, sizeof(vis));
	dfs(1);
	for(int i = 0; i < edgeCnt; i ++){
		Edge *it = edge + i;
		if(it->lab != -1 && it->cap < EPS 
				&& vis[it->inv->to] && !vis[it->to])
			out.push_back(it->lab);
	}

	printf("%d\n", (int)out.size());
	for(int i = 0; i < (int)out.size(); i ++)
		printf("%d ", out[i]);
	printf("\n\n");
}

int main(){
	freopen("t.in", "r", stdin);
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF)
		solve(n, m);
}
