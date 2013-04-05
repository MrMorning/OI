#include <cstdio>
#include <vector>
#include <algorithm>
#define foreach(I, C) for ( __typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++ )
using namespace std;

const int N_FOUNTAIN_MAX = 150000;
const int N_TRAIL_MAX = 150000;
const int N_GROUP_MAX = 2000;
const int N_VTX_MAX = 2 * N_FOUNTAIN_MAX;
const int N_EDGE_MAX = N_VTX_MAX;

int n_fount, n_trail, res_id, n_group;

struct Edge {
	int to;
	Edge *next;
} edge[N_EDGE_MAX], *begin[N_VTX_MAX];

struct Fountain {
	int beauty[2], vtx[2];
} fount[N_FOUNTAIN_MAX];

struct Trail {
	int u, v;
} trail[N_TRAIL_MAX];

struct Group {
	int g, ans;
} group[N_GROUP_MAX];

pair<int, int> dist[N_FOUNTAIN_MAX];
bool can_start[N_VTX_MAX];
vector<int> inv[N_VTX_MAX];
vector<pair<int, int> > query[N_VTX_MAX];
int in_dgr[N_VTX_MAX];
bool in_cycle[N_VTX_MAX];
int n_vtx, cycle_len, n_dist;

void add_edge(int u, int v) {
	static int edge_cnt = 0;
	in_dgr[v] ++;
	inv[v].push_back(u);
	Edge *e = edge + edge_cnt ++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void init() {
	scanf("%d%d%d", &n_fount, &n_trail, &res_id);
	for ( int i = 0; i < n_fount; i ++ )
		fount[i].beauty[0] = fount[i].beauty[1] = -1;
	for ( int i = 0; i < n_trail; i ++ ) {
		scanf("%d%d", &trail[i].u, &trail[i].v);
		if ( fount[trail[i].u].beauty[0] == -1 )
			fount[trail[i].u].beauty[0] = i;
		else if ( fount[trail[i].u].beauty[1] == -1 )
			fount[trail[i].u].beauty[1] = i;
		if ( fount[trail[i].v].beauty[0] == -1 )
			fount[trail[i].v].beauty[0] = i;
		else if ( fount[trail[i].v].beauty[1] == -1 )
			fount[trail[i].v].beauty[1] = i;
	}

	n_vtx = 0;

	for ( int i = 0; i < n_fount; i ++ ) {
		fount[i].vtx[0] = n_vtx ++;
		can_start[fount[i].vtx[0]] = true;
		if ( fount[i].beauty[1] != -1 ) {
			fount[i].vtx[1] = n_vtx ++;
			can_start[fount[i].vtx[1]] = false;
		}
		else
			fount[i].vtx[1] = -1;
	}

	for ( int i = 0; i < n_fount; i ++ ) {
		int j = fount[i].beauty[0],
			k = trail[j].u == i ? trail[j].v : trail[j].u;
		if ( j == fount[k].beauty[0] )
			add_edge(fount[i].vtx[0], fount[k].vtx[1] == -1 ? fount[k].vtx[0] : fount[k].vtx[1]);
		else
			add_edge(fount[i].vtx[0], fount[k].vtx[0]);

		if ( fount[i].beauty[1] != -1 ) {
			j = fount[i].beauty[1];
			k = trail[j].u == i ? trail[j].v : trail[j].u;
			if ( j == fount[k].beauty[0] )
				add_edge(fount[i].vtx[1], fount[k].vtx[1] == -1 ? fount[k].vtx[0] : fount[k].vtx[1]);
			else
				add_edge(fount[i].vtx[1], fount[k].vtx[0]);
		}
	}

	scanf("%d", &n_group);
	for ( int i = 0; i < n_group; i ++ ) 
		scanf("%d", &group[i].g);
}

void topsort() {
	static int stk[N_VTX_MAX];
	int top = 0;
	for ( int i = 0; i < n_vtx; i ++ ) {
		in_cycle[i] = true;
		if ( in_dgr[i] == 0 )
			stk[top ++] = i;
	}
	while ( top ) {
		int u = stk[-- top];
		in_cycle[u] = false;
		for ( Edge *e = begin[u]; e; e = e->next ) {
			int v = e->to;
			in_dgr[v] --;
			if ( in_dgr[v] == 0 )
				stk[top ++] = v;
		}
	}
}

void process_query() {
	for ( int i = 0; i < cycle_len; i ++ )
		query[i].clear();
	for ( int i = 0; i < n_group; i ++ ) 
		query[group[i].g % cycle_len].push_back(make_pair(group[i].g, i));
	for ( int i = 0; i < cycle_len; i ++ )
		sort(query[i].begin(), query[i].end());
}

void dfs(int now, int src, int acc) {
	if ( can_start[now] )
		dist[n_dist ++] = make_pair(acc % cycle_len, acc);
	foreach(it, inv[now]) 
		if ( *it != src )
			dfs(*it, src, acc + 1);
}

void solve(int src) {
	if ( in_cycle[src] ) {
		cycle_len = 0;
		int now = src;
		do {
			foreach(it, inv[now]) {
				if ( in_cycle[*it] ) {
					now = *it;
					cycle_len ++;
					break;
				}
			}
		} while ( now != src );
	} else
		cycle_len = 1;
	process_query();

	n_dist = 0;
	dfs(src, src, 0);
	sort(dist, dist + n_dist);
	for ( int i = 0; i < n_dist; i ++ ) {
		int j = i;
		while ( i + 1 < n_dist && dist[i + 1].first == dist[i].first )
			i ++;
		int t = dist[i].first;
		int p = j;

		if ( in_cycle[src] ) {
			for ( int q = 0, sz = query[t].size(); q < sz; q ++ ) {
				while ( p + 1 <= i && query[t][q].first >= dist[p + 1].second )
					p ++;
				if ( query[t][q].first >= dist[p].second )
					group[query[t][q].second].ans += p - j + 1;
			}
		} else {
			for ( int q = 0, sz = query[t].size(); q < sz; q ++ ) {
				while ( p + 1 <= i && query[t][q].first > dist[p].second )
					p ++;
				if ( query[t][q].first != dist[p].second )
					continue;
				int st = p;
				while ( p + 1 <= i && query[t][q].first == dist[p + 1].second )
					p ++;
				group[query[t][q].second].ans += p - st + 1;
				while ( q + 1 < sz && query[t][q + 1].first == dist[p].second ) {
					group[query[t][q + 1].second].ans += p - st + 1;
					q ++;
				}
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	init();
	topsort();
	solve(fount[res_id].vtx[0]);
	if ( fount[res_id].vtx[1] != -1 )
		solve(fount[res_id].vtx[1]);
	for ( int i = 0; i < n_group; i ++ )
		printf("%d\n", group[i].ans);
}
