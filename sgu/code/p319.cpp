#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#define foreach(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;

typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int RECTANGLE_MAX = 60010;

#define LEAVE 0
#define QUERY 1
#define ENTER 2

struct Rectangle {
	int x1, y1, x2, y2;
	ll area, delta;
	void createEvent();
} rec[RECTANGLE_MAX];

struct Event {
	int x, y, id, type;
	Event(int _x, int _y, int _id, int _type):
		x(_x), y(_y), id(_id), type(_type){}
	bool operator< (const Event &T) const {
		return x < T.x || (x == T.x && type < T.type);
	}
};

vector<Event> event;

void Rectangle::createEvent() {
	event.push_back(Event(x1, y1, (this - rec), QUERY));
	event.push_back(Event(x1, y1, (this - rec), ENTER));
	event.push_back(Event(x1, y2, (this - rec), ENTER));
	event.push_back(Event(x2, y1, (this - rec), LEAVE));
	event.push_back(Event(x2, y2, (this - rec), LEAVE));
}

set<pair<int, int> > st; //(y, id)
int nRec = 0;
int depth[RECTANGLE_MAX];
int parent[RECTANGLE_MAX];
int dgr[RECTANGLE_MAX];
int stk[RECTANGLE_MAX];
vector<ll> ans;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &nRec);
	scanf("%d%d", &rec[nRec].x2, &rec[nRec].y2);
	rec[nRec].x1 = rec[nRec].y1 = 0;
	for ( int i = 0; i < nRec; i ++ ) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if ( x1 > x2 ) swap(x1, x2);
		if ( y1 > y2 ) swap(y1, y2);
		rec[i].x1 = x1, rec[i].y1 = y1;
		rec[i].x2 = x2, rec[i].y2 = y2;
	}
	nRec++;
	for ( int i = 0; i < nRec; i ++ )
		rec[i].createEvent();
	sort(event.begin(), event.end());
	foreach(ev, event) {
		typedef set<pair<int, int> >::iterator itr_t;
		if ( ev->type == QUERY ) {
			itr_t it = st.lower_bound(make_pair(ev->y, -1));
			if ( it == st.end() ) {
				parent[ev->id] = -1;
				depth[ev->id] = 0;
			} else {
				itr_t high = it, low = it;
				low --;
				if ( high->second == low->second )
					parent[ev->id] = low->second;
				else {
					if ( depth[low->second] >= depth[high->second] )
						parent[ev->id] = parent[low->second];
					else
						parent[ev->id] = parent[high->second];
				}
				depth[ev->id] = depth[parent[ev->id]] + 1;
			}
		} else if ( ev->type == ENTER ) {
			st.insert(make_pair(ev->y, ev->id));
		} else {
			itr_t it = st.lower_bound(make_pair(ev->y, ev->id));
			st.erase(it);
		}
	}

	for ( int i = 0; i < nRec; i ++ ) {
		rec[i].area = (ll)(rec[i].x2 - rec[i].x1) * (rec[i].y2 - rec[i].y1);
		rec[i].delta = 0;
		if ( parent[i] != -1 )
			dgr[parent[i]] ++;
	}

	int top = 0;

	for ( int i = 0; i < nRec; i ++ )
		if ( dgr[i] == 0 )
			stk[top++] = i;
	while ( top ) {
		int u = stk[--top];
		ans.push_back(rec[u].area - rec[u].delta);
		int p = parent[u];
		if ( p != -1 ) {
			rec[p].delta += rec[u].area;
			dgr[p] --;
			if ( dgr[p] == 0 )
				stk[top ++] = p;
		}
	}
	sort(ans.begin(), ans.end());
	foreach(it, ans)
		printf(LL_FMT " ", *it);
}
