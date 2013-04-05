#include <cstdio>
#include <cstring>

const int LEN_MAX = 1010;
const int NODE_MAX = 1010;
const int inf = 0x3f3f3f3f;

struct Node {
	Node *go[4], *fail;
	bool ill;
} node[NODE_MAX], *root;
int node_cnt;

int f[LEN_MAX][NODE_MAX];

Node *alloc() {
	Node *x = node + node_cnt ++;
	memset(x->go, 0, sizeof(x->go));
	x->fail = NULL;
	x->ill = false;
	return x;
}
char pat[22], des[LEN_MAX];
int MATCH[256];
Node *Q[NODE_MAX];
int TST;

int main() {
	freopen("t.in", "r", stdin);
	MATCH['A'] = 0;
	MATCH['G'] = 1;
	MATCH['C'] = 2;
	MATCH['T'] = 3;
	while ( 1 ) {
		TST ++;
		node_cnt = 0;
		root = alloc();
		int n_pat;
		scanf("%d", &n_pat);
		if ( n_pat == 0 )
			break;
		printf("Case %d: ", TST);
		for ( int i = 0; i < n_pat; i ++ ) {
			scanf("%s", pat);
			Node *cur = root;
			int len = strlen(pat);
			for ( int j = 0; j < len; j ++ ) {
				int t = MATCH[pat[j]];
				Node *&nxt = cur->go[t];
				if ( nxt == NULL )
					nxt = alloc();
				cur = nxt;
			}
			cur->ill = true;
		}

		int qh = 0, qt = 0;

		for ( int a = 0; a < 4; a ++ )
			if ( root->go[a] ) {
				root->go[a]->fail = root;
				Q[qt++] = root->go[a];
			} else {
				root->go[a] = root;
			}

		while ( qh != qt ) {
			Node *u = Q[qh ++];
			u->ill |= u->fail->ill;
			for ( int a = 0; a < 4; a ++ ) {
				Node *v = u->go[a],
					 *f = u->fail;
				if ( v ) {
					v->fail = f->go[a];
					Q[qt ++] = v;
				} else {
					u->go[a] = f->go[a];
				}
			}
		}

		scanf("%s", des);
		int len = strlen(des);

		memset(f, 0x3f, sizeof(f));
		f[0][0] = 0;
		for ( int i = 0; i < len; i ++ )
			for ( int j = 0; j < node_cnt; j ++ )
				if ( f[i][j] != inf ) {
					Node *u = node + j;
					for ( int a = 0; a < 4; a ++ ) 
						if ( !u->go[a]->ill ) {
							int k = u->go[a] - node;
							int tmp = f[i][j];
							if ( a != MATCH[des[i]] )
								tmp ++;
							if ( tmp < f[i + 1][k] )
								f[i + 1][k] = tmp;
						}
				}		
		int res = inf;
		for ( int i = 0; i < node_cnt; i ++ )
			if ( f[len][i] < res )
				res = f[len][i];
		if ( res == inf )
			res = -1;
		printf("%d\n", res);
	}
}
