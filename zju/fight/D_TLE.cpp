#include <cstring>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
using namespace std;
typedef set<int>::iterator itr_t;

const int N_MAX = 30010;

set<int> my_set[2];
map<int, int> my_map[2];
int idx[2];
int idt[N_MAX];
pair<int, int> ele[N_MAX];
int lb, rb;


void add(int i, int x) {
	for (; i < N_MAX; i += i & -i )
		idt[i] += x;
}

int sum(int i) {
	int res = 0;
	for (; i; i -= i & -i )
		res += idt[i];
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d", &lb, &rb) != EOF ) {
		my_set[0].clear();
		my_set[1].clear();
		idx[0] = idx[1] = 0;
		my_map[0].clear();
		my_map[1].clear();
		memset(idt, 0, sizeof(idt));

		int n;
		scanf("%d", &n);
		for ( int i = 0; i < n; i ++ ) {
			int k, b;
			scanf("%d%d", &k, &b);
			int y1 = lb * k + b,
				y2 = rb * k + b;
			ele[i].first = y1, ele[i].second = y2;
			my_set[0].insert(y1);
			my_set[1].insert(y2);
		}
		for ( itr_t it = my_set[0].begin();
				it != my_set[0].end(); it ++ )
			my_map[0][*it] = ++ idx[0];
		for ( itr_t it = my_set[1].begin();
				it != my_set[1].end(); it ++ )
			my_map[1][*it] = ++ idx[1];
		for ( int i = 0; i < n; i ++ ) {
			ele[i].first = my_map[0][ele[i].first];
			ele[i].second = my_map[1][ele[i].second];
		}
		sort(ele, ele + n);
		int res = 1;
		for ( int i = 0; i < n; i ++ ) {
			res += sum(N_MAX - 1) - sum(ele[i].second) + 1;
			add(ele[i].second, 1);
		}
		printf("%d\n", res);
	}
}
