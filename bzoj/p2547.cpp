#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define JUMP 0
#define CLIMB 1

const int INF = 0x3f3f3f3f;
const int K_MAX = 55;
const int N_MAX = 111;
const int V_MAX = 4 * K_MAX;
const int E_MAX = V_MAX * V_MAX;
const int offset[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

int N, M, K, T;
int height[N_MAX][N_MAX];
int sv, tv;

struct Edge{
	int to, cap;
	Edge *next, *inv;
} edge[E_MAX], *begin[V_MAX];

int edge_cnt;
int dist[V_MAX];
Edge *make_edge(int u, int v, int w){
	Edge *e = edge + edge_cnt++;
	e->to = v, e->next = begin[u], e->cap = w;
	return begin[u] = e;
}

void add_edge(int u, int v, int w){
	Edge *e1 = make_edge(u, v, w),
		 *e2 = make_edge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool pre_lable(){
	static int Q[V_MAX];
	memset(dist, -1, sizeof(dist));
	int qh = 0, qt = 0;
	Q[qt ++] = sv;
	dist[sv] = 0;
	while(qh < qt){
		int u = Q[qh ++];
		for(Edge *e = begin[u]; e; e= e->next)
			if(e->cap){
				int v = e->to;
				if(dist[v] == -1){
					dist[v] = dist[u] + 1;
					Q[qt ++] = v;
				}
			}
	}
	return dist[tv] != -1;
}

int find_aug(int u, int flow){
	if(u == tv)
		return flow;
	Edge *e;
	int res = 0;
	for(e = begin[u]; e; e = e->next)
		if(e->cap){
			int v = e->to;
			if(dist[v] != dist[u] + 1)
				continue;
			int tmp = find_aug(v, min(e->cap, flow));
			e->cap -= tmp;
			e->inv->cap += tmp;
			res += tmp;
			flow -= tmp;
			if(!flow)
				break;
		}
	if(!e)
		dist[u] = -1;
	return res;
}

int dinic(){
	int res = 0;
	while(pre_lable())
		res += find_aug(sv, INF);
	return res;
}

bool satisfy(int s, int h, int h2){
	if(s == JUMP)
		return h2 <= h;
	else
		return h2 >= h;
}

struct State{
	int x, y, d;
	State(){}
	State(int _x, int _y, int _d):
		x(_x), y(_y), d(_d){}
} target[K_MAX * 2];
int n_target;

struct Warrior{
	 int x, y;
	 int dist[N_MAX][N_MAX];
	 void bfs(int init_s){
		 static State queue[N_MAX * N_MAX];
		 memset(dist, 0x3f, sizeof(dist));
		 int qh = 0, qt = 0;
		 queue[qt ++] = State(x, y, 0);
		 dist[x][y] = 0;
		 int cur_s = init_s;
		 while(1){
			 qh = 0;
			 while(qh < qt){
				 State &u = queue[qh ++];
				 for(int d = 0; d < 4; d ++){
				 	int nx = u.x + offset[d][0],
						ny = u.y + offset[d][1];
					if(1 <= nx && nx <= N)
						if(1 <= ny && ny <= M)
							if(dist[nx][ny] == INF)
								if(satisfy(cur_s, height[u.x][u.y], height[nx][ny])){
									State v = State(nx, ny, u.d);
									dist[nx][ny] = u.d;
									queue[qt ++] = v;
								}
				 }
			 }
			 bool flag = false;
			 for(int i = 1; !flag && i <= N; i ++)
				 for(int j = 1; !flag && j <= M; j ++)
					 if(dist[i][j] == INF)
						 flag = true;
			 if(!flag)
				 break;
			 for(int i = 0; i < qt; i ++)
				 queue[i].d ++;
			 cur_s ^= 1;
		 }
	 }
} warrior[2 * K_MAX];

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &K, &T);
	for(int i = 1; i <= 2 * K + 1; i ++)
		scanf("%d%d", &warrior[i].x, &warrior[i].y);
	for(int i = 1; i <= T; i ++){
		int x, y, sz;
		scanf("%d%d%d", &x, &y, &sz);
		while(sz --)
			target[++ n_target] = State(x, y, -1);
	}
	for(int i = 1; i <= N; i ++)
		for(int j = 1; j <= M; j ++)
			scanf("%d", &height[i][j]);

	for(int i = 1; i <= 2 * K; i ++)
		if(i <= K)
			warrior[i].bfs(CLIMB);
		else
			warrior[i].bfs(JUMP);

	sv = 4 * K + 2, tv = 4 * K + 3;
	for(int i = 1; i <= 2 * K; i ++)
		add_edge(sv, i, 1);
	for(int i = 2 * K + 1; i <= 4 * K + 1; i ++)
		add_edge(i, tv, 1);
	for(int ans = 0, pre_flow = 0; ans <= 2 * K; ans ++){
		for(int i = 1; i <= 2 * K; i ++)
			for(int j = 1; j <= 2 * K + 1; j ++){
				State &t = target[j];
				if(warrior[i].dist[t.x][t.y] == ans)
					add_edge(i, 2 * K + j, 1);
			}
		int max_flow = dinic() + pre_flow;
		if(max_flow + ans >= 2 * K){
			printf("%d\n", ans);
			break;
		}
		pre_flow = max_flow;
	}
}
