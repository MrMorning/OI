#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

const int N_MAX = 100010;

struct Stuff {
	int x1, y1, x2, y2, id;
	double k, b;
	void init() {
		k = (double)(y2 - y1) / (x2 - x1);
		b = y1 - k * x1;
	}
	double func(int x0) {
		return k * x0 + b;
	}
} stuff[N_MAX];
int n_stuff;

struct Command {
	int des, dir;
} cmd[N_MAX];

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
		return e1.x < e2.x || (e1.x == e2.x && e1.typ <= e2.typ);
	}


	struct cmp_height {
		bool operator()(int i, int j) const{
			int lb = max(stuff[i].x1, stuff[j].x1);
			return stuff[i].func(lb) < stuff[j].func(lb);
		}
	};

	void solve1() {
	}

	void solve2() {
		typedef set<int, cmp_height> set_t;
		static vector<Event> event;
		static set_t box;
		static stack<int> stk;
		static vector<int> seq;
		static int dgr[N_MAX];
		static vector<int> adj[N_MAX];

		for ( int i = 0; i < n_stuff; i ++ ) {
			event.push_back(Event(stuff[i].x1, i, ENTER));
			event.push_back(Event(stuff[i].x2, i, LEAVE));
		}
		sort(event.begin(), event.end(), cmp_event);
		for ( vector<Event>::iterator ev = event.begin();
				ev != event.end(); ev ++ ) {
			if ( ev->typ == ENTER ) {
				pair<set_t::iterator, bool> res = box.insert(ev->id);
				set_t::iterator it = res.first;
				it ++;
				if ( it != box.end() ) {
					dgr[*it] ++;
					adj[ev->id].push_back(*it);
					//fprintf(stderr, "%d->%d\n", ev->id, *it);
				}
				it --;
				if ( it != box.begin() ) {
					it --;		
					dgr[ev->id] ++;
					adj[*it].push_back(ev->id);
					//fprintf(stderr, "%d->%d\n", *it, ev->id);
				}
			} else 
				box.erase(box.lower_bound(ev->id));
		}

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

		assert((int)seq.size() == n_stuff);
		for ( int i = 0; i < n_stuff; i ++ )
			printf("%d %d\n", seq[i] + 1, 3);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n_stuff);
	for ( int i = 0; i < n_stuff; i ++ ) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if ( x1 > x2 ) {
			swap(x1, x2);
			swap(y1, y2);
		}
		stuff[i].x1 = x1, stuff[i].x2 = x2;
		stuff[i].y1 = y1, stuff[i].y2 = y2;
		stuff[i].id = i;
	}
	for ( int i = 0; i < n_stuff; i ++ ) {
		scanf("%d%d", &cmd[i].des, &cmd[i].dir);
		cmd[i].des --;
	}
}
