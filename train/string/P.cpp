#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int NODE_MAX = 100010;
const int LEN_MAX = 100010;

struct Node {
	Node *go[26], *fail;
	vector<int> l;
} node[NODE_MAX];
int free_pos;

string tex, pat;

Node *alloc() {
	Node *x = node + free_pos ++;
	memset(x->go, 0, sizeof(x->go));
	x->fail = NULL;
	x->l.clear();
	return x;
}

void doit(vector<int> &res, string pat) {
	free_pos = 0;
	Node *root = alloc();
	int n_seg = 0;
	int pat_len = pat.size();

	int suf_mask = 0;
	while ( suf_mask < pat_len && pat[pat_len - suf_mask - 1] == '?' )
		suf_mask ++;

	if ( suf_mask == pat_len ) {
		int m = tex.size();
		for ( int x = 0; x < m - pat_len + 1; x ++ )
			res.push_back(x);
		return;
	}

	pat = pat.substr(0, pat_len - suf_mask);
	pat_len = pat.size();

	Node *cur = root;
	for ( int i = 0; i < pat_len; i ++ ) 
		if ( pat[i] == '?' ) {
			if ( cur == root )
				continue;
			n_seg ++;
			cur->l.push_back(i - 1);
			cur = root;
			while ( i + 1 < pat_len && pat[i + 1] == '?' )
				i ++;
			continue;
		} else {
			if ( cur->go[pat[i] - 'a'] == NULL )
				cur->go[pat[i] - 'a'] = alloc();
			cur = cur->go[pat[i] - 'a'];
		}
	n_seg ++;
	cur->l.push_back(pat_len - 1);

	static Node* Q[NODE_MAX];
	int qh = 0, qt = 0;
	for ( int a = 0; a < 26; a ++ ) 
		if ( root->go[a] ) {
			root->go[a]->fail = root;
			Q[qt ++] = root->go[a];
		}
		else
			root->go[a] = root;

	while ( qh != qt ) {
		Node *u = Q[qh ++];
		for ( int a = 0; a < 26; a ++ ) {
			Node *v = u->go[a], 
				 *f = u->fail;
			if ( v == NULL )
				u->go[a] = f->go[a];
			else {
				v->fail = f->go[a];
				for ( int i = 0, sz = v->fail->l.size(); i < sz; i ++ )
					v->l.push_back(v->fail->l[i]);
				Q[qt ++] = v;
			}
		}
	}

	static int C[LEN_MAX];
	memset(C, 0, sizeof(C));
	cur = root;
	for ( int i = 0; i < tex.size() - suf_mask; i ++ ) {
		cur = cur->go[tex[i] - 'a'];
		for ( int k = 0, sz = cur->l.size(); k < sz; k ++ )
			C[i - cur->l[k]] ++;
	}
	for ( int i = 0; i < tex.size() - suf_mask; i ++ )
		if ( C[i] == n_seg )
			res.push_back(i);
}

vector<string> pat_vec;
vector<int> res[LEN_MAX];

bool solve() {
	pat_vec.clear();
	memset(res, 0, sizeof(res));

	int n = (int)pat.size();
	int st = 0;
	while ( st < n && pat[st] == '*' ) st ++;
	if ( st == n ) {
		return true;
	}
	int suf_mask = 0;

	while ( pat[n - suf_mask - 1] == '*' ) suf_mask ++;
	pat = pat.substr(0, n - suf_mask);
	n -= suf_mask;

	string acc;
	for ( int i = st; i < n; i ++ ) {
		if ( pat[i] == '*' ) {
			pat_vec.push_back(acc);
			acc = "";
			while ( i + 1 < n && pat[i + 1] == '*' )
				i ++;
		} else
			acc += pat[i];
	}
	pat_vec.push_back(acc);
	

	int sz = pat_vec.size();
	for ( int i = 0; i < sz; i ++ )
		doit(res[i], pat_vec[i]);

	if ( st > 0 || (res[0].size() && res[0][0] == 0 ) ) 
		if ( suf_mask > 0 || 
				(res[sz - 1].size() 
				 && res[sz - 1].back() + (int)pat_vec[sz - 1].size() == (int)tex.size()) ) {

			for ( int pre = -1, i = 0; i < sz; i ++ ) {
				int t;
				int upper = res[i].size();
				if ( upper == 0 )
					return false;
				for ( t = 0; t < upper; t ++ )
					if ( res[i][t] > pre )
						break;
				if ( t == upper )
					return false;
				pre = res[i][t] + (int)pat_vec[i].size() - 1;
			}
			return true;
		}

	return false;
}

int main() {
	freopen("t.in", "r", stdin);
	while ( cin >> tex >> pat ) {
		if ( solve() )
			puts("YES");	
		else
			puts("NO");
	}
}
