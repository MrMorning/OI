#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <vector>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)
using namespace std;

const int kSgtNdMax = 1000010;
const int kNdMax = 100010;
const int kInf = 0x3f3f3f3f;

int val[kNdMax], ans[kNdMax];
int size[kNdMax], high[kNdMax], jump[kNdMax];
int father[kNdMax], hvst[kNdMax], pos[kNdMax], len[kNdMax];
vector<int> son[kNdMax];

struct heapCmp {
	bool operator() (int i, int j) const {
		return ans[i] < ans[j] || (ans[i] == ans[j] && i < j);
	}
};

set<int, heapCmp> heap[kNdMax];
int n;

struct Info {
	int val[2];
	bool e;
	Info(bool _e = true):e(_e){}
	Info(int val0, int val1){
		e = true;
		val[0] = val0, val[1] = val1;
	}
};

Info operator+ (const Info &A, const Info &B) {
	if ( !A.e ) return B;
	if ( !B.e ) return A;
	return Info(min(A.val[0],B.val[0]), min(A.val[1],B.val[1]));
}

int getHeapMin(int x) {
	if ( !heap[x].size() ) return kInf;
	return ans[*heap[x].begin()];
}

int getHeapMinExcept(int x, int exc) {
	if ( heap[x].size() == 1 ) return kInf;
	if ( *heap[x].begin() != exc ) 
		return ans[*heap[x].begin()];
	return ans[*(++heap[x].begin())];
}


struct sgtNode {
	int l, r;
	Info info;
	sgtNode *ch[2];

	void upd() {
		info= ch[0]->info + ch[1]->info;
	}
} sgtPool[kSgtNdMax], *sgt[kNdMax];

sgtNode *sgtAlloc() {
	static int freePos = 0;
	sgtNode *x = &sgtPool[freePos++];
	return x;
}

sgtNode *sgtBuild(int *buf, int l, int r) {
	sgtNode *x = sgtAlloc();
	x->l = l, x->r = r;
	if ( l == r ) {
		x->info.val[0] = val[buf[l]];
		x->info.val[1] = getHeapMin(buf[l]);
		x->ch[0] = x->ch[1] = NULL;
	} else {
		int mid = (l + r) / 2;
		x->ch[0] = sgtBuild(buf, l, mid);
		x->ch[1] = sgtBuild(buf, mid+1, r);
		x->upd();
	} 
	return x;
}

Info sgtAsk(sgtNode *x, int l, int r) {
	if ( l > x->r || r < x->l ) return Info(false);
	if ( l <= x->l && x->r <= r ) return x->info;
	return sgtAsk(x->ch[0], l, r) + sgtAsk(x->ch[1], l, r);
}

void sgtChange(sgtNode *x, int pos, Info newInfo) {
	if ( x->l > pos || x->r < pos ) return;
	if ( pos == x->l && x->r == pos ) {
		x->info = newInfo;
		return;
	}
	sgtChange(x->ch[0], pos, newInfo);
	sgtChange(x->ch[1], pos, newInfo);
	x->upd();
}

void init() {
	static int Q[kNdMax];
	int qt = 0;
	Q[qt++] = 1;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		foreach(it, son[u])
			Q[qt++] = *it;
	}
	for ( int i = qt-1; i >= 1; i -- ) {
		int x = Q[i];
		size[x]++;
		size[father[x]] += size[x];
		if ( !hvst[father[x]] || size[x] > size[hvst[father[x]]] )
			hvst[father[x]] = x;
	}

	for ( int i = 1; i <= n; i ++ ) ans[i] = val[i];
	for ( int i = qt-1; i >= 1; i -- ) {
		int x = Q[i];
		if ( father[x] ) {
			ans[father[x]] = min(ans[father[x]], ans[x]);
			if ( x != hvst[father[x]] )
				heap[father[x]].insert(x);
		}
	}
}

void chainSplit() {
	static bool vis[kNdMax];
	static int buf[kNdMax];
	for ( int i = 1; i <= n; i ++ )
		if ( !vis[i] && hvst[i] ) {
			int nBuf = 0;
			int cur = i;
			while ( !vis[cur] && hvst[cur] ) {
				buf[++nBuf] = cur;
				cur = hvst[cur];
			}
			buf[++nBuf] = cur;
			sgtNode *nd = sgtBuild(buf, 1, nBuf);
			for ( int k = 1; k <= nBuf; k ++ ) {
				vis[buf[k]] = true;
				sgt[buf[k]] = nd;
				pos[buf[k]] = k;
				high[buf[k]] = buf[1];
				jump[buf[k]] = father[buf[1]];
				len[buf[k]] = nBuf;
			}
		}
	for ( int i = 1; i <= n; i ++ ) 
		if ( !vis[i] ) {
			buf[1] = i;
			pos[i] = 1;
			len[i] = 1;
			high[i] = i;
			sgt[i] = sgtBuild(buf, 1, 1);
			jump[i] = father[i];
		}
}

int calcAns(int x) {
	int res = val[x];
	Info tmp = sgtAsk(sgt[x], pos[x], len[x]);
	res = min(res, min(tmp.val[0], tmp.val[1]));
	res = min(res, getHeapMin(x));
	return res;
}

void changeVal(int x, int newVal) {
	val[x] = newVal;
	int cur = x;
	while ( cur ) {
		sgtChange(sgt[cur], pos[cur], Info(val[cur], getHeapMin(cur)));
		int pre = high[cur];
		cur = jump[cur];
		if ( !cur ) break;
		heap[cur].erase(heap[cur].lower_bound(pre));
		ans[pre] = calcAns(pre);
		heap[cur].insert(pre);
	}
}

int curRoot;

int askExceptSubtree(int x) {
	if ( x == 1 ) return kInf;
	int y = father[x];
	int res = kInf;
	if ( x == hvst[y] ) {
		Info tmp = sgtAsk(sgt[y], 1, pos[y]);
		res = min(res, min(tmp.val[0], tmp.val[1]));
		res = min(res, askExceptSubtree(high[y]));
		return res;
	} else {
		Info tmp = sgtAsk(sgt[y], pos[y], len[y]);
		int res = min(tmp.val[0], tmp.val[1]);
		res = min(res, getHeapMinExcept(y, x));
		res = min(res, askExceptSubtree(y));
		return res;
	}
}

bool isAncestor(int a, int b) {
	if ( a == b ) return false;
	while ( b && sgt[b] != sgt[a] )
		b = jump[b];
	if ( !b ) return false;
	return pos[b] >= pos[a];
}

int askMin(int x) {
	if ( curRoot == x ) 
		return calcAns(1);
	else if ( !isAncestor(x, curRoot) )
		return calcAns(x);
	else {
		int now = curRoot, pre = -1;
		if ( sgt[now] == sgt[x] ) 
			pre = hvst[x];
		while ( sgt[now] != sgt[x] ) {
			pre = high[now];
			now = jump[now];
		}
		int res = askExceptSubtree(x);
		if ( pos[now] > pos[x] ) {
			return min(min(val[x], getHeapMin(x)), res);
		}
		if ( pos[x] != len[x] ) {
			Info tmp = sgtAsk(sgt[x], pos[x]+1, len[x]);
			res = min(res, min(tmp.val[0],tmp.val[1]));
		}
		res = min(res, getHeapMinExcept(x, pre));
		return res;
	}
}

int main() {
	freopen("t.in", "r", stdin);
	int Q;
	scanf("%d%d", &n, &Q);
	for ( int i = 1; i <= n; i ++ ) {
		scanf("%d%d", &father[i], &val[i]);
		if ( father[i] )
			son[father[i]].push_back(i);
	}
	init();
	chainSplit();
	curRoot = 1;
	while ( Q -- ) {
		static char cmd[3];
		scanf("%s", cmd);
		if ( cmd[0] == 'V' ) {
			int x, y;
			scanf("%d%d", &x, &y);
			changeVal(x, y);
		} else if ( cmd[0] == 'E' ) {
			int x;
			scanf("%d", &x);
			curRoot = x;
		} else {
			int x;
			scanf("%d", &x);
			printf("%d\n", askMin(x));
		}
	}
}
