#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#define foreach(I, C) for ( __typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++ )
using namespace std;
typedef long long ll;

const int N_MAX = 100010;

struct Element {
	int n, id;
	ll sum;
};

struct MonoQueue {
	Element ele[N_MAX];
	int qh, qt;
	MonoQueue() {
		qh = qt = 0;
	}
	int size() { return qt - qh; }
	void push(const Element &tmp) {
		if ( qh < qt && ele[qt - 1].n == tmp.n && ele[qt - 1].sum >= tmp.sum )
			return;
		while ( qh < qt 
				&& ele[qt - 1].n == tmp.n && ele[qt - 1].sum <= tmp.sum )
			qt --;
		ele[qt ++] = tmp;
	}
} MQ;

int n_cube, n_col;
vector<pair<int, int> > col_vec[N_MAX], arr;
map<int, int> col_map;
ll best_val = 0;
int best_id[2];

int main() {
	ios::sync_with_stdio(false);
//	freopen("t.in", "r", stdin);
	cin >> n_cube;
	for ( int i = 1; i <= n_cube; i ++ ) {
		int c, s;
		cin >> c >> s;
		if ( col_map.count(c) == 0 )
			col_map[c] = n_col ++;
		col_vec[col_map[c]].push_back(make_pair(s, i));
	}
	for ( int i = 0; i < n_col; i ++ ) {
		sort(col_vec[i].begin(), col_vec[i].end(), greater<pair<int, int> >());
		arr.push_back(make_pair(col_vec[i].size(), i));
	}
	sort(arr.begin(), arr.end());
	foreach(it, arr) {
		int t = it->second, n = it->first;
		static ll pre_sum[N_MAX];
		pre_sum[1] = col_vec[t][0].first;
		for ( int i = 1; i < n; i ++ )
			pre_sum[i + 1] = pre_sum[i] + col_vec[t][i].first;
		pre_sum[n + 1] = pre_sum[n];
		for ( int i = MQ.qh; i < MQ.qt; i ++ ) {
			ll val = MQ.ele[i].sum + pre_sum[MQ.ele[i].n + 1];
			if ( val > best_val ) {
				best_val = val;
				best_id[0] = MQ.ele[i].id, best_id[1] = t;
			}
		}
		Element cur;
		cur.id = t, cur.n = n, cur.sum = pre_sum[n];
		MQ.push(cur);
	}
	cout << best_val << '\n';
	int tot_cnt = (int)col_vec[best_id[0]].size() * 2 + 1;
	if ( col_vec[best_id[0]].size() == col_vec[best_id[1]].size() ) 
		tot_cnt --;
	cout << tot_cnt << '\n';
	for ( int i = 0, p0 = 0, p1 = 0; i < tot_cnt; i ++ ) {
		if ( i & 1 ) 
			cout << col_vec[best_id[0]][p0 ++].second << ' ';
		else
			cout << col_vec[best_id[1]][p1 ++].second << ' ';
	}
}
