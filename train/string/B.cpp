#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int NODE_MAX = 400000;

struct Node {
	Node *go[28], *pre;
	vector<int> vec;
} node[NODE_MAX];
int free_pos;

Node *alloc() {
	Node *x = node + free_pos ++;
	memset(x->go, 0, sizeof(x->go));
	x->pre = NULL;
	x->vec.clear();
	return x;
}

int des[22], des_len;
vector<int> res;

int conv(char ch) {
	if ( 'a' <= ch && ch <= 'z' )
		return ch - 'a';
	else if ( ch == '?' )
		return 26;
	else
		return 27;
}

void dfs(Node *x, int i) {
	if ( i == des_len ) {
		if ( x->vec.size() ) {
			int sz = x->vec.size();
			for ( int k = 0; k < sz; k ++ )
				res.push_back(x->vec[k]);
		}
		return;
	}
	if ( x->pre != NULL && x == x->pre->go[conv('*')] )
		dfs(x, i + 1);
	if ( x->go[des[i]] )
		dfs(x->go[des[i]], i + 1);
	if ( x->go[conv('?')] )
		dfs(x->go[conv('?')], i + 1);
	if ( x->go[conv('*')] ) {
		dfs(x->go[conv('*')], i);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	int N, M;

	scanf("%d%d", &N, &M);
	Node *root = alloc();
	for ( int i = 0; i < N; i ++ ) {
		static char str[10];
		scanf("%s", str);
		int len = strlen(str);
		Node *cur = root;
		for ( int j = 0; j < len; j ++ ) {
			int t = conv(str[j]);
			if ( cur->go[t] == NULL) {
				cur->go[t] = alloc();
				cur->go[t]->pre = cur;
			}
			cur = cur->go[t];
		}
		cur->vec.push_back(i);
		while ( cur->pre && cur == cur->pre->go[conv('*')] ) {
			cur = cur->pre;
			cur->vec.push_back(i);
		}
	}
	for ( int i = 0; i < M; i ++ ) {
		static char str[22];
		scanf("%s", str);
		des_len = strlen(str);
		for ( int i = 0; i < des_len; i ++ )
			des[i] = conv(str[i]);
		res.clear();
		dfs(root, 0);
		if ( res.size() == 0 )
			printf("Not match\n");
		else {
			sort(res.begin(), res.end());
			res.resize(unique(res.begin(), res.end()) - res.begin());
			int sz = res.size();
			for ( int k = 0; k < sz; k ++ )
				printf("%d ", res[k]);
			puts("");
		}
	}
}
