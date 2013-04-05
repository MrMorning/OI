/*
 * $Date: Thu Oct 20 20:00:26 2011 +0800
 * $Author: csimstu
 * $Source: Codeforces Beta Round #88 Problem E Tree or not Tree
 * $Method: Chain-split
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)

using namespace std;

const int V_MAX = 100010;

int cycle[V_MAX];
int cycleLen;
vector<int> adj[V_MAX];
int nodeNum;

namespace findCycle{
	int dfn[V_MAX], low[V_MAX];
	int pre[V_MAX];
	bool vis[V_MAX];
	int found;

	void tarjan(int x, int p){
		if(found)
			return;
		static int timeStamp = 0;
		dfn[x] = low[x] = timeStamp ++;
		foreach(e, adj[x]){
			int y = *e;
			if(y == p)
				continue;
			if(!dfn[y]){
				tarjan(y, x);
				if(found)
					return;
				low[x] = min(low[x], low[y]);
				if(dfn[x] >= low[y]){
					found = x;
					return;
				}
			}
			else
				low[x] = min(low[x], dfn[y]);
		}
	}

	void dfs(int x, int p, int term){
		static bool done = false;
		if(done)
			return;
		vis[x] = true;
		foreach(e, adj[x]){
			int y = *e;
			if(y == p)
				continue;
			if(!vis[y]){
				pre[y] = x;
				vis[y] = true;
				dfs(y, x, term);
			}
			else if(y == term){
				pre[term] = x;
				done = true;
				return;
			}
		}
	}


	void main(){
		tarjan(1, 0);
		dfs(found, 0, found);
		cycle[++ cycleLen] = found;
		for(int x = pre[found]; x != found; x = pre[x])
			cycle[++ cycleLen] = x;
	}
}

namespace sgt{
	struct Node{
		Node *ch[2];
		int l, r, sum;
		bool isRev;
	} pool[V_MAX * 4];

	void update(Node *x){
		x->sum = 0;
		if(x->ch[0])
			x->sum += x->ch[0]->sum;
		if(x->ch[1])
			x->sum += x->ch[1]->sum;
	}

	Node *build(int l, int r){
		static int freePos = 0;
		Node *x = pool + (freePos ++);
		x->l = l, x->r = r;
		x->sum = 0;
		if(l < r){
			int mid = (l + r) / 2;
			x->ch[0] = build(l, mid);
			x->ch[1] = build(mid + 1, r);
		}
		return x;
	}

	void mark(Node *x){
		x->isRev ^= 1;
		x->sum = x->r - x->l + 1 - x->sum;
	}

	void pushDown(Node *x){
		if(x->isRev){
			x->isRev = false;
			for(int t = 0; t < 2; t ++)
				if(x->ch[t])
					mark(x->ch[t]);
		}
	}

	void reverse(Node *x, int l, int r){
		if(l > x->r || r < x->l)
			return;
		if(l <= x->l && x->r <= r){
			mark(x);	
			return;
		}
		pushDown(x);
		reverse(x->ch[0], l, r);
		reverse(x->ch[1], l, r);
		update(x);
	}

	int query(Node *x, int l, int r){
		if(l > x->r || r < x->l)
			return 0;
		if(l <= x->l && x->r <= r)
			return x->sum;
		pushDown(x);
		int res = query(x->ch[0], l, r) + query(x->ch[1], l, r);
		update(x);
		return res;
	}
}

namespace chainSplit{
	sgt::Node *tree[V_MAX], *treeC;
	int root[V_MAX];
	int seq[V_MAX], seqLen;
	int posInC[V_MAX];
	int depth[V_MAX], size[V_MAX], pre[V_MAX];
	int jump[V_MAX], heavy[V_MAX];
	int compTree, compCycle, forgotten;

	void getSeq(int r){
		static int Q[V_MAX];
		seqLen = 0;
		int qh = 0, qt = 0;
		Q[qt ++] = r;
		depth[r] = 0;
		pre[r] = 0;
		while(qh < qt){
			int u = Q[qh ++];
			root[u] = r;
			seq[++ seqLen] = u;
			foreach(e, adj[u])
				if(posInC[*e] == 0 && *e != pre[u]){
					depth[*e] = depth[u] + 1;
					pre[*e] = u;
					Q[qt ++] = *e;
				}
		}
	}

	void calcInfo(){
		for(int i = 1; i <= seqLen; i ++)
			size[seq[i]] = 0;
		for(int i = seqLen; i >= 1; i --){
			int x = seq[i];
			size[x] ++;
			int p = pre[x];
			if(p){
				size[p] += size[x];
				if(heavy[p] == 0 || size[heavy[p]] < size[x])
					heavy[p] = x;
			}
		}
	}

	void dealWith(int r){
		getSeq(r);
		calcInfo();
		for(int i = seqLen; i >= 2; i --){
			vector<int> buffer;
			int x = seq[i];
			if(tree[x] != NULL)
				continue;
			while(pre[x] && heavy[pre[x]] == x){
				buffer.push_back(x);
				x = pre[x];
			}
			if((int)buffer.size() == 0){
				tree[x] = sgt::build(depth[x], depth[x]);
				jump[x] = pre[x];
			}
			else{
				sgt::Node *t = sgt::build(depth[buffer.back()], depth[buffer[0]]);
				foreach(y, buffer){
					tree[*y] = t;
					jump[*y] = x;
				}
			}
		}
	}

	int lca(int x, int y){
		while(tree[x] != tree[y]){
			if(jump[x] == 0)
				swap(x, y);
			else if(jump[y] && depth[jump[x]] < depth[jump[y]])
				swap(x, y);
			x = jump[x];
		}
		if(depth[x] < depth[y])
			return x;
		else
			return y;
	}

	int countUpward(int x, int p){
		int res = 0;
		while(tree[x] != tree[p]){
			res += tree[x]->sum;
			x = jump[x];
		}
		if(x != p)
			res += sgt::query(tree[x], depth[p] + 1, depth[x]);
		return res;
	}

	void modifyUpward(int x, int p){
		while(tree[x] != tree[p]){
			sgt::reverse(tree[x], depth[jump[x]] + 1, depth[x]);
			x = jump[x];
		}
		if(x != p)
			sgt::reverse(tree[x], depth[p] + 1, depth[x]);
	}

	void process(int x, int y){ //from x to y
		if(root[x] == root[y]){
			int p = lca(x, y);
			int before = countUpward(x, p) + countUpward(y, p);
			modifyUpward(x, p), modifyUpward(y, p);
			int after = countUpward(x, p) + countUpward(y, p);
			compTree -= after - before;
		}
		else{
			int p = root[x], before, after;
			before = countUpward(x, p);
			modifyUpward(x, p);
			after = countUpward(x, p);
			compTree -= after - before;
			int q = root[y];
			before = countUpward(y, q);
			modifyUpward(y, q);
			after = countUpward(y, q);
			compTree -= after - before;

			int u = posInC[p], v = posInC[q];
			int dist = abs(u - v);

			if(!(cycleLen & 1) && dist == cycleLen / 2){
				int ul = cycle[(u - 2 + cycleLen) % cycleLen + 1],
					ur = cycle[(u + cycleLen) % cycleLen + 1];
				if(ul < ur){
					if(u < v){
						sgt::reverse(treeC, 1, u - 1);
						sgt::reverse(treeC, v, cycleLen - 1);
						forgotten ^= 1;
					}
					else
						sgt::reverse(treeC, v, u - 1);
				}
				else{
					if(u < v)
						sgt::reverse(treeC, u, v - 1);
					else{
						sgt::reverse(treeC, u, cycleLen - 1);
						sgt::reverse(treeC, 1, v - 1);
						forgotten ^= 1;
					}
				}
			}
			else if(dist <= cycleLen / 2)
				sgt::reverse(treeC, min(u, v), max(u, v) - 1);
			else{
				sgt::reverse(treeC, max(u, v), cycleLen - 1);
				sgt::reverse(treeC, 1, min(u, v) - 1);
				forgotten ^= 1;
			}
			after = sgt::query(treeC, 1, cycleLen - 1) + forgotten;
			if(after == cycleLen)
				compCycle = 1;
			else
				compCycle = cycleLen - after;
		}
	}

	void main(){
		compTree = nodeNum, compCycle = cycleLen;
		for(int i = 1; i <= cycleLen; i ++)
			posInC[cycle[i]] = i;
		for(int i = 1; i <= cycleLen; i ++)
			dealWith(cycle[i]);
		treeC = sgt::build(1, cycleLen - 1);
		forgotten = 0;
	}

	int getAnswer(){
		return compTree + compCycle - cycleLen;
	}
}

int main(){
	int M;
	scanf("%d%d", &nodeNum, &M);
	for(int i = 0; i < nodeNum; i ++){
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	findCycle::main();
	chainSplit::main();
	while(M --){
		int x, y;
		scanf("%d%d", &x, &y);
		chainSplit::process(x, y);
		printf("%d\n", chainSplit::getAnswer());
	}
}
