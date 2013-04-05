// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}
#ifdef unix
#define LL_FMT "%lld"
#else 
#define LL_FMT "%I64d"
#endif

const int LEN_MAX = 1000010;
const int NODE_MAX = 1000010;
const int STR_MAX = 1000010;

int n_str;
char str[LEN_MAX], ts[LEN_MAX];
int start[STR_MAX], len[STR_MAX];

namespace idt {
	ll tree[NODE_MAX];
	ll sum(int i) {
		ll res = 0;
		for (; i; i -= i & -i )
			res += tree[i];
		return res;
	}
	void add(int i, int val) {
		for (; i < NODE_MAX; i += i & -i )
			tree[i] += val;
	}
	void add(int l, int r, int val) {
		l ++, r ++;
		add(l, val);
		add(r + 1, -val);
	}
	ll get(int pos) {
		pos ++;
		return sum(pos);
	}
}

namespace AC {
	struct Node {
		Node *go[26], *fail;
	} node[NODE_MAX], *root, *Q[NODE_MAX], *id2ptr[STR_MAX];
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
			id2ptr[i] = cur;
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

	void cover(int i, int val) {
		int k = id2ptr[i] - node;
		idt::add(seq_st[k], seq_en[k], val);
	}

	ll query();
}

ll AC::query() {
	int sz = strlen(ts);
	Node *cur = root;
	ll res = 0;
	for ( int i = 0; i < sz; i ++ ) {
		int ch = ts[i] - 'a';
		cur = cur->go[ch];
		res += idt::get(seq_st[cur - node]);
	}
	return res;
}
bool is_on[STR_MAX];
int n_query;
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%d%d", &n_query, &n_str);
	int tot_len = 0;
	for ( int i = 0; i < n_str; i ++ ) {
		scanf("%s", str + tot_len);
		len[i] = strlen(str + tot_len);
		start[i] = tot_len;
		tot_len += len[i];
	}

	AC::build();
	AC::get_seq();

	for ( int i = 0; i < n_str; i ++ ) {
		is_on[i] = true;
		AC::cover(i, 1);
	}

	while ( n_query -- ) {
		char ch = getchar();
		while ( ch != '-' && ch != '+' && ch != '?' )
			ch = getchar();
		if ( ch == '?' ) {
			scanf("%s", ts);
			printf(LL_FMT "\n", AC::query());
		} else if ( ch == '-' ) {
			int x;
			scanf("%d", &x);
			x --;
			if ( !is_on[x] )
				continue;
			is_on[x] = false;
			AC::cover(x, -1);
		} else {
			int x;
			scanf("%d", &x);
			x --;
			if ( is_on[x] )
				continue;
			is_on[x] = true;
			AC::cover(x, 1);
		}
	}
}
