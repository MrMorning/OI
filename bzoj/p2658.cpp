#include <cstdio>
#include <vector>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
typedef long long ll;

const int N_MAX = 100010, R_MAX = 40010;

struct Node {
	vector<Node*> son;
	int H, len, l, r;
	ll S; //sum of sons' contributes

	void update() {
		len = r - l + 1;
		FOREACH(it, son) {
			S += (*it)->S;
			S += (ll)(*it)->len * ((*it)->len + 1) / 2 * (H - (*it)->H);
		}
	}
} node[N_MAX];

vector<int> row[R_MAX];
vector<Node*> roots;

Node *alloc(int H, int l, int r) {
	static int free_pos = 0;
	Node *x = node + free_pos ++;
	x->l = l, x->r = r, x->H = H;
	x->son.clear();
	return x;
}

pair<Node*, Node*> split(Node *cur, int mid) {
	Node *lpart = NULL, *rpart = NULL;
	if ( cur->l < mid ) 
		lpart = alloc(cur->H, cur->l, mid - 1);
	if ( mid < cur->r ) 
		rpart = alloc(cur->H, mid + 1, cur->r);

	FOREACH(it, cur->son) {
		if ( (*it)->r < mid )
			lpart->son.push_back(*it);
		else if ( (*it)->l > mid )
			rpart->son.push_back(*it);
		else {
			pair<Node*, Node*> tmp = split(*it, mid);
			if ( tmp.first != NULL )
				lpart->son.push_back(tmp.first);
			if ( tmp.second != NULL )
				rpart->son.push_back(tmp.second);
		}
	}

	if ( lpart != NULL ) lpart->update();
	if ( rpart != NULL ) rpart->update();

	return make_pair(lpart, rpart);
}

int main() {
	freopen("t.in", "r", stdin);

	int R, C, N;
	scanf("%d%d%d", &R, &C, &N);
	for ( int i = 0; i < N; i ++ ) {
		int x, y;
		scanf("%d%d", &x, &y);
		row[x].push_back(y);
	}

	ll res = 0;

	for ( int i = 1; i <= R; i ++ ) {
		Node *cur = alloc(i, 1, C);
		FOREACH(it, roots) 
			cur->son.push_back(*it);
		cur->update();
		roots.clear();
		roots.push_back(cur);
		FOREACH(it, row[i]) {
			for ( int id = 0, sz = roots.size(); id < sz; id ++ ) {
				Node *rt = roots[id];
				if ( rt->l <= *it && *it <= rt->r ) {
					roots.erase(roots.begin() + id);
					pair<Node*, Node*> tmp = split(rt, *it);
					if ( tmp.first != NULL )
						roots.push_back(tmp.first);
					if ( tmp.second != NULL )
						roots.push_back(tmp.second);
					break;
				}
			}
		}

		FOREACH(rt, roots) {
			res += (*rt)->S;
			res += (ll)(i - (*rt)->H + 1) * ((ll)(*rt)->len * ((*rt)->len + 1) / 2);
		}
	}

	ll tot = (ll)C * (C + 1) / 2 * R * (R + 1) / 2;
	printf("%lld\n", tot - res);
}
