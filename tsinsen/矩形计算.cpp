#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>
using namespace std;
const int N_MAX = 205, Q_MAX = 100010, E_MAX = 5000010;
const int LIM = 100;
#define INSERT 0
#define QUERY 1

struct Query {
	int x1, y1, x2, y2;
	int ans;
} que[Q_MAX];

struct Event {
	int x1, y1, x2, y2, type, id;
	bool operator< (const Event &e) const {
		return x1 > e.x1 || (x1 == e.x1 && type < e.type);
	}
} ev[E_MAX];

int n_row, n_col;
int n_que, n_ev, axis_cnt;
vector<pair<int, int> > vec[N_MAX * N_MAX];
map<int, int> axis;

int ele[N_MAX][N_MAX];

int tree[N_MAX][N_MAX][N_MAX];

void add(int i, int j, int k) {
	assert(i < N_MAX && j < N_MAX && k < N_MAX);
	for ( int ii = i; ii < N_MAX; ii += ii & -ii )
		for ( int jj = j; jj < N_MAX; jj += jj & -jj )
			for ( int kk = k; kk < N_MAX; kk += kk & -kk )
				tree[ii][jj][kk] ++;
}	

int sum(int i, int j, int k) {
	assert(i < N_MAX && j < N_MAX && k < N_MAX);
	int res = 0;
	for ( int ii = i; ii; ii -= ii & -ii )
		for ( int jj = j; jj; jj -= jj & -jj )
			for ( int kk = k; kk; kk -= kk & -kk )
				res += tree[ii][jj][kk];
	return res;
}

void brute_work(int val) {
	int f[N_MAX][N_MAX];	
	memset(f, 0, sizeof(f));
	for ( int i = 1; i <= n_row; i ++ )
		for ( int j = 1; j <= n_col; j ++ )
			f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + (ele[i][j] == val);
	for ( int i = 1; i <= n_que; i ++ ) {
		int x1 = que[i].x1, y1 = que[i].y1, x2 = que[i].x2, y2 = que[i].y2;
		int cnt = f[x2][y2] - f[x1 - 1][y2] - f[x2][y1 - 1] + f[x1 - 1][y1 - 1];
		que[i].ans += cnt * cnt;
	}
}

void add_pairs(int val) {
	assert(val < N_MAX * N_MAX);
	int sz = vec[val].size();
	for ( int i = 0; i < sz; i ++ )
		for ( int j = 0; j < sz; j ++ ) {
			int x1 = vec[val][i].first, y1 = vec[val][i].second;
			int x2 = vec[val][j].first, y2 = vec[val][j].second;
			if ( x1 > x2 )
				swap(x1, x2);
			if ( y1 > y2 )
				swap(y1, y2);
			Event &e = ev[n_ev ++];
			e.type = INSERT, e.x1 = x1, e.x2 = x2, e.y1 = y1, e.y2 = y2;
		}
}

int main() {
	scanf("%d%d", &n_row, &n_col);
	for ( int i = 1; i <= n_row; i ++ )
		for ( int j = 1; j <= n_col; j ++ ) {
			scanf("%d", &ele[i][j]);
			if ( axis.count(ele[i][j]) == 0 )
				axis[ele[i][j]] = ++ axis_cnt;
			ele[i][j] = axis[ele[i][j]];
			vec[ele[i][j]].push_back(make_pair(i, j));
		}
	scanf("%d", &n_que);
	for ( int i = 1; i <= n_que; i ++ ) {
		scanf("%d%d%d%d", &que[i].x1, &que[i].y1, &que[i].x2, &que[i].y2);
		if ( que[i].x1 > que[i].x2 )
			swap(que[i].x1, que[i].x2);
		if ( que[i].y1 > que[i].y2 )
			swap(que[i].y1, que[i].y2);
	}

	for ( int i = 1; i <= axis_cnt; i ++ ) {
		if ( (int)vec[i].size() >= LIM ) 
			brute_work(i);
		else 
			add_pairs(i);
	}

	for ( int i = 1; i <= n_que; i ++ ) {
		Event &e = ev[n_ev ++];
		e.x1 = que[i].x1, e.y1 = que[i].y1;
		e.x2 = que[i].x2, e.y2 = que[i].y2;
		e.type = QUERY;
		e.id = i;
	}
	sort(ev, ev + n_ev);

	for ( int i = 0; i < n_ev; i ++ ) {
		Event &e = ev[i];
		if ( e.type == INSERT ) 
			add(e.y1, e.x2, e.y2);
		else 
			que[ev[i].id].ans += sum(N_MAX - 1, e.x2, e.y2) - sum(e.y1 - 1, e.x2, e.y2);
	}

	for ( int i = 1; i <= n_que; i ++ )
		printf("%d\n", que[i].ans);
}
