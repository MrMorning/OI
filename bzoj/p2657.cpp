#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
const int N_MAX = 200010;
const int HASH_SIZE = 1 << 18;
const int ELE_SIZE = N_MAX;
typedef pair<int, int> key_t;
struct HashMap {
	
	int begin[HASH_SIZE], next[ELE_SIZE];
	pair<key_t, int> ele[ELE_SIZE];
	int size;

	HashMap() {
		memset(begin, -1, sizeof(begin));
		size = 0;
	}

	bool count(key_t p) {
		int code = (p.first ^ p.second) & (HASH_SIZE - 1);
		for ( int i = begin[code]; i != -1; i = next[i] )
			if ( ele[i].first == p )
				return true;
		return false;
	}

	int find(key_t p) {
		int code = (p.first ^ p.second) & (HASH_SIZE - 1);
		for ( int i = begin[code]; i != -1; i = next[i] )
			if ( ele[i].first == p )
				return ele[i].second;
		assert(0);
	}

	void insert(key_t p, int val) {
		int code = (p.first ^ p.second) & (HASH_SIZE - 1);
		next[size] = begin[code];
		ele[size] = make_pair(p, val);
		begin[code] = size;
		size ++;
	}
} HM;

int dist[N_MAX];
vector<int> adj[N_MAX];

void bfs(int src) {
	static int Q[N_MAX];
	memset(dist, -1, sizeof(dist));
	dist[src] = 0;
	int qh = 0, qt = 0;
	Q[qt ++] = src;
	while ( qh != qt ) {
		int u = Q[qh ++];
		FOREACH(it, adj[u]) {
			int v = *it;
			if ( dist[v] != -1 )
				continue;
			dist[v] = dist[u] + 1;
			Q[qt ++] = v;
		}
	}
}

void append(int a, int b, int i) {
	if ( a > b )
		swap(a, b);
	if ( HM.count(make_pair(a, b)) ) {
		int t = HM.find(make_pair(a, b));
		adj[t].push_back(i);
		adj[i].push_back(t);
	} else
		HM.insert(make_pair(a, b), i);
}
int main() {
	freopen("t.in", "r", stdin);
	int N;

	scanf("%d", &N);
	for ( int i = 0; i < N - 2; i ++ ) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		append(a, b, i);
		append(a, c, i);
		append(b, c, i);
	}

	bfs(0);
	int far = -1;
	for ( int i = 0; i < N - 2; i ++ )
		if ( far == -1 || (dist[far] < dist[i]) )
			far = i;
	bfs(far);
	int res = 0;
	for ( int i = 0; i < N - 2; i ++ )
		res = max(res, dist[i]);
	printf("%d\n", res + 1);
}
