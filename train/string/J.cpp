#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int BASE = 10007;
const int Z_MAX = 26;
const int NODE_MAX = 150010;
const int LEN_MAX = 33;
struct Node {
	int go[Z_MAX], dep;
	ll hash;
	bool end;
	Node() {
		memset(go, -1, sizeof(go));
		end = false;
	}
} node[NODE_MAX];
int root = -1, node_cnt = 0;

int fa[NODE_MAX];
int seq[NODE_MAX];
pair<int, int> arr[NODE_MAX];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void combine(int x, int y) {
	int p = find(x), q = find(y);
	if ( p == q )
		return;
	fa[p] = q;
}

void insert(char pat[LEN_MAX], int sz) {
	if ( root == -1 )
		root = node_cnt ++;
	int cur = root;
	for ( int i = 0; i < sz; i ++ ) {
		int &t = node[cur].go[pat[i] - 'a'];
		if ( t == -1 )
			t = node_cnt ++;
		cur = t;
	}
	node[cur].end = true;
}

void dfs(int x) {
	node[x].dep = 0;
	for ( int a = 0; a < Z_MAX; a ++ ) {
		int y = node[x].go[a];
		if ( y != -1 ) {
			dfs(y);
			node[x].dep = max(node[x].dep, node[y].dep + 1);
		}
	}
}

bool cmp_dep(int i, int j) {
	return node[i].dep < node[j].dep;
}

int main() {
	int n;
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) {
		static char str[LEN_MAX];
		scanf("%s", str);
		insert(str, strlen(str));
	}

	dfs(root);
	for ( int i = 0; i < node_cnt; i ++ ) {
		fa[i] = i;
		seq[i] = i;
	}
	sort(seq, seq + node_cnt, cmp_dep);
	int ans = node_cnt;
	for ( int i = 0; i < node_cnt; i ++ ) {
		int j = i;
		while ( i + 1 < node_cnt && node[seq[i + 1]].dep == node[seq[j]].dep )
			i ++;
		for ( int k = j; k <= i; k ++ ) {
			node[seq[k]].hash = 1;
			for ( int a = 0; a < Z_MAX; a ++ ) {
				int tmp = node[seq[k]].go[a] == -1 ? 1 : find(node[seq[k]].go[a]) + 2;
				node[seq[k]].hash = node[seq[k]].hash * BASE + tmp;
			}
			node[seq[k]].hash = node[seq[k]].hash * BASE + node[seq[k]].end + 1;
			arr[k] = make_pair(node[seq[k]].hash, seq[k]);
		}
		sort(arr + j, arr + i + 1);
		for ( int k = j; k <= i; k ++ ) {
			int s = k;
			while ( k + 1 <= i && arr[k + 1].first == arr[k].first )
				k ++;
			ans -= k - s;
			for ( int t = s + 1; t <= k; t ++ )
				combine(arr[t].second, arr[s].second);
		}
	}
	printf("%d\n", ans);
}
