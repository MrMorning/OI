#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 50010;
const int inf = 0x3f3f3f3f;

int n, h[N_MAX], s[N_MAX], b[N_MAX], v[N_MAX];
int hi[N_MAX], si[N_MAX], bi[N_MAX];
ll ans[N_MAX], org_ans;
pair<int, int> dis[N_MAX];
int dis_cnt;

#define upd(x, y) \
	if (x > y) \
		x = y;

struct Event {
#define EVENT_ADD 1
#define EVENT_ASK 2
#define EVENT_DEL 3
	int idx, key, type;
	Event(){}
	Event(int _idx, int _key, int _type):
		idx(_idx), key(_key), type(_type){}
	bool operator< (const Event &t) const {
		return key < t.key || (key == t.key && type < t.type);
	}
} event[3 * N_MAX];

struct SGT {
	struct Node {
		int val, l, r;
	} node[N_MAX * 3];
#define update(i) \
		node[i].val = min(node[i * 2].val, node[i * 2 + 1].val);
	void build(int i, int l, int r) {
		Node &x = node[i];
		x.l = l, x.r = r;
		if (l < r) {
			int mid = (l + r) / 2;
			build(i * 2, l, mid);
			build(i * 2 + 1, mid + 1, r);
			update(i);
		}
		else {
			node[i].val = inf;
		}
	}
	void change(int pos, int new_val) {
		int cur = 1;
		while (1) {
			if (node[cur].l == node[cur].r) {
				node[cur].val = new_val;
				break;
			}
			int mid = (node[cur].l + node[cur].r) / 2;
			if (pos <= mid)
				cur = cur * 2;
			else
				cur = cur * 2 + 1;
		}
		while (1) {
			cur >>= 1;
			if (cur == 0)
				break;
			update(cur);
		}
	}
	int get_val(int pos) {
		int cur = 1;
		while (1) {
			if (node[cur].l == node[cur].r) {
				return node[cur].val;
			}
			int mid = (node[cur].l + node[cur].r) / 2;
			if (pos <= mid)
				cur = cur * 2;
			else
				cur = cur * 2 + 1;
		}
	}
	int ask(int i, int l, int r) {
		if (node[i].l > r || node[i].r < l)
			return inf;
		if (l <= node[i].l && node[i].r <= r)
			return node[i].val;
		return min(ask(i * 2, l, r), ask(i * 2 + 1, l, r));
	}
	int ask(int l, int r) {
		return ask(1, l, r);
	}
};

namespace special {
	void test_swap(int x, int y) {
		assert(x < y);
		swap(h[x], h[y]);
		ll tmp = org_ans + abs(h[x] - h[x + 1]) + abs(h[y] - h[y - 1]) - v[x] - v[y];
		if (x != 1)
			tmp += abs(h[x] - h[x - 1]);
		if (y != n)
			tmp += abs(h[y] - h[y + 1]);
		upd(ans[x], tmp);
		upd(ans[y], tmp);
		swap(h[x], h[y]);
	}
	void main() {
		test_swap(1, n);
		for (int i = 2; i <= n - 1; i ++) {
			test_swap(1, i);
			test_swap(i, n);
		}
		for (int i = 1; i <= n - 1; i ++)
			test_swap(i, i + 1);
	}
	void brute() {
		for (int i = 1; i <= n; i ++)
			for (int j = i + 1; j <= n; j ++)
				test_swap(i, j);
	}
}

#define SAVE \
	for (int j = 0; j < 3; j ++) {\
		if (u > 2)\
		backup[j][0] = sgt[j].get_val(hi[u - 1]);\
		backup[j][1] = sgt[j].get_val(hi[u]);\
		if (u < n - 1)\
		backup[j][2] = sgt[j].get_val(hi[u + 1]);\
		if (u > 2)\
		if (backup[j][0] != inf) \
		sgt[j].change(hi[u - 1], inf);\
		if (backup[j][1] != inf) \
		sgt[j].change(hi[u], inf);\
		if (u < n - 1)\
		if (backup[j][2] != inf) \
		sgt[j].change(hi[u + 1], inf);\
	}
#define LOAD \
	for (int j = 0; j < 3; j ++) {\
		if (u > 2)\
		if (backup[j][0] != inf) \
		sgt[j].change(hi[u - 1], backup[j][0]);\
		if (backup[j][1] != inf) \
		sgt[j].change(hi[u], backup[j][1]);\
		if (u < n - 1)\
		if (backup[j][2] != inf) \
		sgt[j].change(hi[u + 1], backup[j][2]);\
	}

namespace work1 {
	// h[x] <= s[y]
	SGT sgt[3];
	int backup[3][3];
	void main() {
		for (int i = 0; i < 3; i ++)
			sgt[i].build(1, 1, dis_cnt);
		int event_cnt = 0;
		for (int i = 2; i <= n - 1; i ++) { 
			sgt[0].change(hi[i], s[i] + b[i] - 2 * h[i] - v[i]);
			sgt[1].change(hi[i], s[i] + b[i] - v[i]);
			sgt[2].change(hi[i], s[i] + b[i] + 2 * h[i] - v[i]);
			event[++ event_cnt] = Event(i, si[i], EVENT_DEL);
			event[++ event_cnt] = Event(i, hi[i], EVENT_ASK);
		}
		sort(event + 1, event + event_cnt + 1);
		for (int i = 1; i <= event_cnt; i ++) {
			const Event &e = event[i];
			int u = e.idx;
			if (e.type == EVENT_DEL) {
				sgt[0].change(hi[u], inf);
				sgt[1].change(hi[u], inf);
				sgt[2].change(hi[u], inf);
			}
			else if (e.type == EVENT_ASK){
				SAVE
					upd(ans[u], org_ans + sgt[0].ask(1, si[u]) + s[u] + b[u] - 2 * h[u] - v[u]);
				upd(ans[u], org_ans + sgt[1].ask(si[u], bi[u]) + b[u] - s[u] - 2 * h[u] - v[u]);
				upd(ans[u], org_ans + sgt[2].ask(bi[u], dis_cnt) - s[u] - b[u] - 2 * h[u] - v[u]);
				LOAD
			}
		}
	}
}

namespace work2 {
	// s[y] <= h[x] <= b[y]
	SGT sgt[3];
	int backup[3][3];
	void main() {
		for (int i = 0; i < 3; i ++)
			sgt[i].build(1, 1, dis_cnt);
		int event_cnt = 0;
		for (int i = 2; i <= n - 1; i ++) { 
			event[++ event_cnt] = Event(i, si[i], EVENT_ADD);
			event[++ event_cnt] = Event(i, bi[i], EVENT_DEL);
			event[++ event_cnt] = Event(i, hi[i], EVENT_ASK);
		}
		sort(event + 1, event + event_cnt + 1);
		for (int i = 1; i <= event_cnt; i ++) {
			const Event &e = event[i];
			int u = e.idx;
			if (e.type == EVENT_ADD) {
				sgt[0].change(hi[u], b[u] - s[u] - 2 * h[u] - v[u]);
				sgt[1].change(hi[u], b[u] - s[u] - v[u]);
				sgt[2].change(hi[u], b[u] - s[u] + 2 * h[u] - v[u]);
			}
			else if (e.type == EVENT_DEL) {
				sgt[0].change(hi[u], inf);
				sgt[1].change(hi[u], inf);
				sgt[2].change(hi[u], inf);
			}
			else if (e.type == EVENT_ASK){
				SAVE
					upd(ans[u], org_ans + sgt[0].ask(1, si[u]) + s[u] + b[u] - v[u]);
				upd(ans[u], org_ans + sgt[1].ask(si[u], bi[u]) + b[u] - s[u] - v[u]);
				upd(ans[u], org_ans + sgt[2].ask(bi[u], dis_cnt) - s[u] - b[u] - v[u]);
				LOAD
			}
		}
	}
}
namespace work3 {
	// b[y] <= h[x]
	SGT sgt[3];
	int backup[3][3];
	void main() {
		for (int i = 0; i < 3; i ++)
			sgt[i].build(1, 1, dis_cnt);
		int event_cnt = 0;
		for (int i = 2; i <= n - 1; i ++) { 
			event[++ event_cnt] = Event(i, bi[i], EVENT_ADD);
			event[++ event_cnt] = Event(i, hi[i], EVENT_ASK);
		}
		sort(event + 1, event + event_cnt + 1);
		for (int i = 1; i <= event_cnt; i ++) {
			const Event &e = event[i];
			int u = e.idx;
			if (e.type == EVENT_ADD) {
				sgt[0].change(hi[u], - b[u] - s[u] - 2 * h[u] - v[u]);
				sgt[1].change(hi[u], - b[u] - s[u] - v[u]);
				sgt[2].change(hi[u], - b[u] - s[u] + 2 * h[u] - v[u]);
			}
			else if (e.type == EVENT_ASK){
				SAVE
					upd(ans[u], org_ans + sgt[0].ask(1, si[u]) + 2 * h[u] + s[u] + b[u] - v[u]);
				upd(ans[u], org_ans + sgt[1].ask(si[u], bi[u]) + 2 * h[u] + b[u] - s[u] - v[u]);
				upd(ans[u], org_ans + sgt[2].ask(bi[u], dis_cnt) + 2 * h[u] - s[u] - b[u] - v[u]);
				LOAD
			}
		}
	}
}

namespace solve {
	void main() {
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++)
			scanf("%d", &h[i]);
		for (int i = 1; i <= n - 1; i ++)
			org_ans += abs(h[i] - h[i + 1]);
		for (int i = 2; i <= n - 1; i ++) {
			v[i] = abs(h[i] - h[i - 1]) + abs(h[i] - h[i + 1]);
			s[i] = min(h[i - 1], h[i + 1]);
			b[i] = max(h[i - 1], h[i + 1]);
		}
		v[1] = abs(h[1] - h[2]);
		v[n] = abs(h[n] - h[n - 1]);

		for (int i = 1; i <= n; i ++)
			dis[++ dis_cnt] = make_pair(h[i], i);
		sort(dis + 1, dis + 1 + dis_cnt);
		for (int i = 1; i <= n; i ++)
			hi[dis[i].second] = i;
		for (int i = 2; i <= n - 1; i ++) {
			if (s[i] == h[i - 1])
				si[i] = hi[i - 1];
			else
				si[i] = hi[i + 1];
			if (b[i] == h[i - 1])
				bi[i] = hi[i - 1];
			else
				bi[i] = hi[i + 1];
		}

		for (int i = 1; i <= n; i ++)
			ans[i] = org_ans;
		if (n <= 0)
			special::brute();
		else {
			special::main();
			work1::main();
			work2::main();
			work3::main();
		}
		for (int i = 1; i <= n; i ++)
			printf("%lld\n", ans[i]);
	}
}

int main() {
	freopen("t.in", "r", stdin);
	solve::main();
}
