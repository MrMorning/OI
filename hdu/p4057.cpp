#include <iostream>
#include <cassert>
#include <cstdio>
#include <queue>
#include <vector>
#include <string>
#include <cstring>

const int N_ALPHA = 4;
const int N_NODE_MAX = 1020;
const int INF = 0x3f3f3f3f;

using namespace std;

struct Node{
	Node *fail, *go[N_ALPHA];
	int mask, idx;
} *root;
Node nodePool[N_NODE_MAX];
string pat[11];
int weight[11];
bool tooLong[11];
int conv[1024];
int val[1 << 10];
int nodeCnt;
int f[2][N_NODE_MAX][1 << 10];

inline Node *alloc(){
	Node *x = nodePool + nodeCnt;
	x->idx = nodeCnt ++;
	x->mask = 0;
	x->fail = 0;
	memset(x->go, 0, sizeof(x->go));
	return x;
}

inline void upd(int &x, int y){
	if(x < y)
		x = y;
}

void buildAC(int N){
	static queue<Node*> Q;

	root = alloc();
	for(int k = 0; k < N; k ++){
		if(tooLong[k])
			continue;
		const string &s = pat[k];
		Node *u = root;
		for(int i = 0; i < (int)s.size(); i ++){
			int ch = conv[s[i]];
			if(u->go[ch] == NULL)
				u->go[ch] = alloc();
			u = u->go[ch];
		}
		u->mask = 1 << k;
	}

	for(int z = 0; z < N_ALPHA; z ++)
		if(root->go[z]){
			root->go[z]->fail = root;
			Q.push(root->go[z]);
		}
		else
			root->go[z] = root;

	while(!Q.empty()){
		Node *u = Q.front(); Q.pop();
		for(int z = 0; z < N_ALPHA; z ++)
			if(u->go[z] == NULL)
				u->go[z] = u->fail->go[z];
			else{
				u->go[z]->fail = u->fail->go[z];
				u->go[z]->mask |= u->fail->go[z]->mask;
				Q.push(u->go[z]);
			}
	}

}

void solve(int N, int L){
	nodeCnt = 0;
	memset(tooLong, 0, sizeof(tooLong));
	for(int i = 0; i < N; i ++){
		cin >> pat[i] >> weight[i];
		if((int)pat[i].size() > L)
			tooLong[i] = true;
	}
	buildAC(N);
	int upperlim = 1 << N;
	memset(val, 0, sizeof(val));
	for(int s = 0; s < upperlim; s ++)
		for(int d = 0; d < N; d ++)
			if(s & (1 << d))
				val[s] += weight[d];
	memset(f, -0x3f, sizeof(f));
	f[0][root->idx][0] = 0;
	for(int i = 0; i < L; i ++){
		memset(f[(i + 1) & 1], -0x3f, sizeof(f[i]));
		for(int j = 0; j < nodeCnt; j ++)
			for(int s = 0; s < upperlim; s ++){
					Node *x = &nodePool[j];
					for(int z = 0; z < N_ALPHA; z ++){
						assert(x->go[z] != NULL);
						int diff = x->go[z]->mask ^ s;
						int more = diff & (~s);
						upd(f[(i + 1) & 1][x->go[z]->idx][s | x->go[z]->mask], 
								f[i & 1][j][s] + val[more]);
					}
				}
	}
	int ans = -INF;
	for(int j = 0; j < nodeCnt; j ++)
		for(int s = 0; s < upperlim; s ++)
			upd(ans, f[L & 1][j][s]);
	if(ans < 0)
		printf("No Rabbit after 2012!\n");
	else
		printf("%d\n", ans);
}

int main(){
	freopen("t.in", "r", stdin);
	conv['A'] = 0; conv['G'] = 1; conv['C'] = 2; conv['T'] = 3;
	int N, L;
	while(scanf("%d%d", &N, &L) != EOF)
		solve(N, L);
}
