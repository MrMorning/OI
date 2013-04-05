#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <cassert>
using namespace std;

const int LEN_MAX = 300010;
const int NODE_MAX = 300010;
const int STR_MAX = 20010;

int n_str;
char str[LEN_MAX];
int start[STR_MAX], len[STR_MAX], weight[STR_MAX];

namespace SGT {
	struct Node {
		int l, r;
		int ever_max;
	} node[NODE_MAX * 4];

	void mark(int i, int val) {
		if ( val > node[i].ever_max )
			node[i].ever_max = val;
	}

	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		node[i].ever_max = 0;
		if ( l == r )
			return;
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
	}

	void build(int n) {
		build(1, 0, n - 1);
	}

	void change(int i, int l, int r, int val) {
		if ( node[i].l > r || node[i].r < l )
			return;
		if ( l <= node[i].l && node[i].r <= r ) {
			mark(i, val);
			return;
		}
		change(i * 2, l, r, val);
		change(i * 2 + 1, l, r, val);
	}

	void change(int l, int r, int val) {
		change(1, l, r, val);
	}

	int ask(int pos) {
		int cur = 1, res = 0;
		while ( 1 ) {
			res = max(res, node[cur].ever_max);
			if ( node[cur].l == node[cur].r ) {
				//assert(node[cur].l == pos);
				break;
			}
			int mid = (node[cur].l + node[cur].r) / 2;
			if ( pos <= mid )
				cur = cur * 2;
			else
				cur = cur * 2 + 1;
		}
		return res;
	}
}

namespace AC {
	struct Node {
		Node *go[26], *fail;
	} node[NODE_MAX], *root, *Q[NODE_MAX];
	vector<int> son[NODE_MAX];
	int seq_cnt;
	int seq_st[NODE_MAX], seq_en[NODE_MAX];
	int node_cnt;

	Node *alloc() {
		Node *x = node + node_cnt++;
		memset(x->go, 0, sizeof(x->go));
		x->fail = NULL;
		return x;
	}

	void build() {
		node_cnt = 0;
		root = alloc();
		for ( int i = 0; i < n_str; i ++ ) {
			Node *cur = root;
			for ( int j = start[i]; j < start[i] + len[i]; j ++ ) {
				int ch = str[j] - 'a';
				if ( !cur->go[ch] ) 
					cur->go[ch] = alloc();
				cur = cur->go[ch];
			}
		}

		int qt = 0;
		for ( int a = 0; a < 26; a ++ )
			if ( root->go[a] ) {
				root->go[a]->fail = root;
				Q[qt ++] = root->go[a];
			} else {
				root->go[a] = root;
			}

		for ( int qh = 0; qh < qt; qh ++ ) {
			Node *x = Q[qh];
			for ( int a = 0; a < 26; a ++ ) {
				Node *&y = x->go[a];
				if ( y == NULL )
					y = x->fail->go[a];
				else {
					y->fail = x->fail->go[a];
					Q[qt ++] = y;
				}
			}
		}

	}

	void get_seq() {
		memset(son, 0, sizeof(son));
		for ( int i = 1; i < node_cnt; i ++ ) {
			int j = node[i].fail - node;
			son[j].push_back(i);
		}

		//stk.clear();
		static int next[NODE_MAX];
		static stack<int> stk;
		//assert(stk.empty());
		memset(next, 0, sizeof(next));
		seq_cnt = 0;
		stk.push(0);
		seq_st[0] = seq_cnt ++;
		while ( !stk.empty() ) {
			int u = stk.top();
			if ( next[u] == (int)son[u].size() ) {
				seq_en[u] = seq_cnt - 1;
				stk.pop();
			} else {
				int v = son[u][next[u]];
				stk.push(v);
				seq_st[v] = seq_cnt ++;
				next[u] ++;
			}
		}
	}

	int main();
	void debug();
}

void solve() {
	scanf("%d", &n_str);
	int tot_len = 0;
	for ( int i = 0; i < n_str; i ++ ) {
		scanf("%s%d", str + tot_len, &weight[i]);
		len[i] = strlen(str + tot_len);
		start[i] = tot_len;
		tot_len += len[i];
	}

	AC::build();
	AC::get_seq();
	SGT::build(AC::seq_cnt);
	printf("%d\n", AC::main());
}

int AC::main() {
	int res = 0;
	for ( int i = 0; i < n_str; i ++ ) {
		Node *cur = root;
		int best = 0;
		for ( int j = start[i]; j < start[i] + len[i]; j ++ ) {
			int ch = str[j] - 'a';
			cur = cur->go[ch];
			//if(!cur)
			//	assert(0);
			best = max(best, SGT::ask(seq_st[cur - node]));
		}
		SGT::change(seq_st[cur - node], seq_en[cur - node], best + weight[i]);
		res = max(res, best + weight[i]);
	}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d", &TST);
	for ( int i = 1; i <= TST; i ++ ) {
		printf("Case #%d: ", i);
		solve();
	}
}
