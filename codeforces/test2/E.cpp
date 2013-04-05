#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int V_MAX = 5555, E_MAX = 111111;
const int INF = 0x3f3f3f3f;

struct Edge{
	int to, idx, w;
	bool used;
	Edge *next, *inv;
	int getIdx();
} edge[E_MAX * 2], *begin[V_MAX];

int edge_cnt;
vector<int> visited;
bool vis[V_MAX];
int f[V_MAX];
Edge *g[V_MAX];
vector<int> comp[V_MAX];
struct Road{
	int x, y, z;
	int org;
	bool operator< (const Road &t) const{
		return z < t.z;
	}
} road[E_MAX];

struct DisjointSet{
	int fa[V_MAX];
	int find(int x){
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y){
		int p = find(x),
			q = find(y);
		if(p == q)
			return;
		fa[p] = q;
	}
	void init(int n){
		for(int i = 0; i < n; i ++)
			fa[i] = i;
	}
} DS;

int city_num, road_num, dgr_lim;

int Edge::getIdx(){
	return (this - edge) / 2;
}

Edge *makeEdge(int u, int v, int w){
	Edge *e = edge + (edge_cnt ++);
	e->to = v, e->next = begin[u], e->w = w;
	return begin[u] = e;
}

void addEdge(int u, int v, int w){
	Edge *e1 = makeEdge(u, v, w),
		 *e2 = makeEdge(v, u, w);
	e1->inv = e2, e2->inv = e1;
}

void dfs(int x, int forbid){
	visited.push_back(x);
	vis[x] = true;
	for(Edge *e = begin[x]; e; e = e->next)
		if(e->to != forbid && !vis[e->to])
			dfs(e->to, forbid);
}

void dp(int x, int depth, Edge *to_fa){
	if(depth <= 1)
		f[x] = -INF;
	else
		if(to_fa->w > f[x]){
			f[x] = to_fa->w;
			g[x] = to_fa;
		}
	for(Edge *e = begin[x]; e; e = e->next)
		if(e != to_fa && e->used){
			f[e->to] = f[x];
			g[e->to] = g[x];
			dp(e->to, depth + 1, e->inv);
		}
}

int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &city_num, &road_num, &dgr_lim);
	for(int i = 0; i < road_num; i ++){
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		x --, y --;
		addEdge(x, y, z);
		road[i].x = x, road[i].y = y, road[i].z = z;
		road[i].org = i;
	}
	{
		int cnt = 0;
		for(Edge *e = begin[0]; e; e = e->next)
			cnt ++;
		if(cnt < dgr_lim){
			printf("-1\n");
			return 0;
		}
	}

	dfs(0, -1);
	if((int)visited.size() != city_num){
		printf("-1\n");
		return 0;
	}
	sort(road, road + road_num);
	int ans = 0, comp_cnt = city_num;
	DS.init(city_num);
	for(int i = 0; i < road_num; i ++){
		if(road[i].x == 0 || road[i].y == 0)
			continue;
		if(DS.find(road[i].x) != DS.find(road[i].y)){
			DS.merge(road[i].x, road[i].y);
			ans += road[i].z;
			comp_cnt --;
			edge[2 * road[i].org].used = edge[2 * road[i].org + 1].used = true;
		}
	}
	if(comp_cnt - 1 > dgr_lim){
		printf("-1\n");
		return 0;
	}
	comp_cnt = 0;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i < city_num; i ++)
		if(!vis[i]){
			visited.clear();
			dfs(i, 0);
			comp[comp_cnt ++] = visited;
		}
	for(int i = 0; i < comp_cnt; i ++){
		int min_w = INF, best = -1;
		for(int j = 0; j < (int)comp[i].size(); j ++){
			int x = comp[i][j];
			for(Edge *e = begin[x]; e; e = e->next)
				if(e->to == 0){
					if(e->w < min_w)
						min_w = e->w, best = e->getIdx();
					break;
				}
		}
		ans += min_w;
		edge[2 * best].used = edge[2 * best + 1].used = true;
	}

	for(int i = comp_cnt; i < dgr_lim; i ++){
		dp(0, 0, NULL);
		int min_inc = INF;
		for(Edge *e = begin[0]; e; e = e->next)
			if(!e->used)
				min_inc = min(min_inc, e->w - f[e->to]);
		//assert(min_inc >= 0);
		for(Edge *e = begin[0]; e; e = e->next)
			if(!e->used)
				if(min_inc == e->w - f[e->to]){
					e->used = e->inv->used = true;
					g[e->to]->used = g[e->to]->inv->used = false;
					ans += min_inc;
					break;
				}
	}
	int res_cnt = 0;
	for(int i = 0; i < edge_cnt; i += 2)
		if(edge[i].used)
			res_cnt ++;
	printf("%d\n", res_cnt);
	for(int i = 0; i < edge_cnt; i += 2)
		if(edge[i].used)
			printf("%d ", i / 2 + 1);
}
