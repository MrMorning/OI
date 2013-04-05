#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <set>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;

const int N_MAX = 100010;
const int inf = 0x3f3f3f3f;
const double EPS = 1e-8;

namespace sgt {
	struct Node {
		int l, r;
		int min_val, min_tag;
		bool tagged;
	} node[8 * N_MAX];

	void update(int i) {
		node[i].min_val = min(node[i * 2].min_val, node[i * 2 + 1].min_val);
	}

	void mark(int i, int min_tag) {
		node[i].min_val = min(node[i].min_val, min_tag);
		if ( !node[i].tagged || node[i].min_tag > min_tag ) {
			node[i].tagged = true;
			node[i].min_tag = min_tag;
		}
	}

	void push_down(int i) {
		if ( node[i].tagged ) {
			mark(i * 2, node[i].min_tag);
			mark(i * 2 + 1, node[i].min_tag);
			node[i].tagged = false;
		}
	}

	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		node[i].min_val = node[i].min_tag = inf;
		node[i].tagged = false;
		if ( l == r )
			return;
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
	}

	int ask_min(int i, int l, int r) {
		if ( node[i].l > r || node[i].r < l )
			return inf;
		if ( l <= node[i].l && node[i].r <= r )
			return node[i].min_val;
		push_down(i);
		int res = inf;
		res = min(res, ask_min(i * 2, l, r));
		res = min(res, ask_min(i * 2 + 1, l, r));
		update(i);
		return res;
	}

	int ask_min(int l, int r) {
		return ask_min(1, l, r);
	}

	void cover(int i, int l, int r, int val) {
		if ( node[i].l > r || node[i].r < l )
			return;
		if ( l <= node[i].l && node[i].r <= r ) {
			mark(i, val);
			return;
		}
		push_down(i);
		cover(i * 2, l, r, val);
		cover(i * 2 + 1, l, r, val);
		update(i);
	}

	//interfaces
	void build(int l, int r) {
		build(1, l, r);
	}
	void cover(int l, int r, int val) {
		cover(1, l, r, val);
	}
}

struct Stuff {
	int x1, y1, x2, y2;
	int l, r;
	ll a, b, c;
	void init() {
		if ( x1 > x2 ) {
			swap(x1, x2);
			swap(y1, y2);
		}
		a = y1 - y2;
		b = x2 - x1;
		c = -(a * x1 + b * y1);
	}
} stuff[N_MAX];
int n_stuff;

struct Command {
	int des, dir;
	bool on;
} cmd[N_MAX];
int max_axis;

namespace solve {
#define LEAVE 0
#define ENTER 1
	struct Event {
		int x, id, typ;
		Event(int _x, int _id, int _typ):
			x(_x), id(_id), typ(_typ){}
	};

	bool cmp_event(const Event &e1, const Event &e2) {
		//leave first
		return e1.x < e2.x || (e1.x == e2.x && e1.typ < e2.typ);
	}


	struct cmp_height {
		bool operator()(int i, int j) const{
			int x = max(stuff[i].x1, stuff[j].x1);
			double t1 = (double)stuff[j].b * (stuff[i].c + stuff[i].a * x),
			   t2 = (double)stuff[i].b * (stuff[j].c + stuff[j].a * x);
			return t1 > t2;
		}
	};
	typedef set<int, cmp_height> set_t;
	vector<Event> event;
	set_t box;
	stack<int> stk;
	vector<int> seq;
	int val[N_MAX];
	int dgr[N_MAX];
	vector<int> adj[N_MAX];
	int axis;

	void init() {
		event.clear();
		box.clear();
		seq.clear();
		memset(dgr, 0, sizeof(int) * n_stuff);
		memset(adj, 0, sizeof(adj));
	}

	void build_graph() {
		for ( int i = 0; i < n_stuff; i ++ ) {
			event.push_back(Event(stuff[i].x1, i, ENTER));
			event.push_back(Event(stuff[i].x2, i, LEAVE));
		}
		sort(event.begin(), event.end(), cmp_event);
		axis = 0;
		for ( int i = 0; i < 2 * n_stuff; i ++ ) {
			int st = i;
			while ( i + 1 < 2 * n_stuff &&
					event[i + 1].x == event[i].x )
				i ++;
			for ( int k = st; k <= i; k ++ ) {
				int t = event[k].id;
				if ( event[k].typ == ENTER )
					stuff[t].l = axis;
				else
					stuff[t].r = axis;
			}
			axis ++;
		}

		for ( vector<Event>::iterator ev = event.begin();
				ev != event.end(); ev ++ ) {
			if ( ev->typ == ENTER ) {
				pair<set_t::iterator, bool> res = box.insert(ev->id);
				set_t::iterator it = res.first;
				it ++;
				if ( it != box.end() ) {
					dgr[*it] ++;
					adj[ev->id].push_back(*it);
				}
				it --;
				if ( it != box.begin() ) {
					it --;		
					dgr[ev->id] ++;
					adj[*it].push_back(ev->id);
				}
			} else {
				set_t::iterator it = box.lower_bound(ev->id);
				box.erase(it);
			}
		}
	}
	void topsort() {
		for ( int i = 0; i < n_stuff; i ++ )
			if ( dgr[i] == 0 )
				stk.push(i);
		while ( !stk.empty() ) {
			int u = stk.top(); stk.pop();
			seq.push_back(u);
			for ( vector<int>::iterator it = adj[u].begin();
					it != adj[u].end(); it ++ ) {
				int v = *it;
				dgr[v] --;
				if ( dgr[v] == 0 )
					stk.push(v);
			}
		}

		for ( int i = 0; i < n_stuff; i ++ )
			val[seq[i]] = i;
	}

	int main() {
		init();
		build_graph();
		topsort();
		sgt::build(0, axis - 1);
		int res = inf;
		for ( int i = n_stuff - 1; i >= 0; i -- ) {
			int t = cmd[i].des;
			if ( cmd[i].on ) {
				int l = stuff[t].l, r = stuff[t].r - 1;
				if ( l <= r ) {
					int tmp = sgt::ask_min(l, r);
					if ( tmp < val[t] )
						res = i;
				}
			}
			if ( stuff[t].r > stuff[t].l )
				sgt::cover(stuff[t].l, stuff[t].r - 1, val[t]);
		}
		return res;
	}
}

int main() {
	static int x1[N_MAX], y1[N_MAX], x2[N_MAX], y2[N_MAX];
	scanf("%d", &n_stuff);
	for ( int i = 0; i < n_stuff; i ++ )
		scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
	for ( int i = 0; i < n_stuff; i ++ ) {
		scanf("%d%d", &cmd[i].des, &cmd[i].dir);
		cmd[i].des --;
	}

	int ans = inf;

	//dir=0
	for ( int i = 0; i < n_stuff; i ++ ) {
		stuff[i].x1 = - y1[i];
		stuff[i].x2 = - y2[i];
		stuff[i].y1 = x1[i];
		stuff[i].y2 = x2[i];
		stuff[i].init();
	}
	for ( int i = 0; i < n_stuff; i ++ )
		cmd[i].on = cmd[i].dir == 0;
	ans = min(ans, solve::main());

	//dir=1
	for ( int i = 0; i < n_stuff; i ++ ) {
		stuff[i].x1 = - x1[i];
		stuff[i].x2 = - x2[i];
		stuff[i].y1 = - y1[i];
		stuff[i].y2 = - y2[i];
		stuff[i].init();
	}
	for ( int i = 0; i < n_stuff; i ++ )
		cmd[i].on = cmd[i].dir == 1;
	ans = min(ans, solve::main());

	//dir=2
	for ( int i = 0; i < n_stuff; i ++ ) {
		stuff[i].x1 = y1[i];
		stuff[i].x2 = y2[i];
		stuff[i].y1 = - x1[i];
		stuff[i].y2 = - x2[i];
		stuff[i].init();
	}
	for ( int i = 0; i < n_stuff; i ++ )
		cmd[i].on = cmd[i].dir == 2;
	ans = min(ans, solve::main());

	//dir=3
	for ( int i = 0; i < n_stuff; i ++ ) {
		stuff[i].x1 = x1[i];
		stuff[i].x2 = x2[i];
		stuff[i].y1 = y1[i];
		stuff[i].y2 = y2[i];
		stuff[i].init();
	}
	for ( int i = 0; i < n_stuff; i ++ )
		cmd[i].on = cmd[i].dir == 3;
	ans = min(ans, solve::main());
	printf("%d\n", ans + 1);

	for ( int i = 0; i < n_stuff; i ++ )
		printf("%d %d\n", solve::seq[i] + 1, 3);
}
