#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<pair<int, int> > stuff_t;

map<stuff_t, double> memo;
/*
struct Stuff {
	vector<pair<int, int> > vec;
	int get_hash() const{ 
		int sz = vec.size();
		sort(vec.begin(), vec.end());
		int res = 0;
		for ( int i = 0; i < sz; i ++ ) 
			res ^= vec[i].first + vec[i].second;
		return res;
	}
	bool operator< (const Stuff)
};*/
/*
struct HashMap {
	Stuff msk[MASK_MAX];
	int begin[HASH_MAX], next[MASK_MAX];
	int msk_cnt;

	HashMap() {
		memset(begin, -1, sizeof(begin));
		msk_cnt = 0;
	}

	pair<bool, Stuff> operator[] (const Stuff &new_msk) {
		int code = new_msk.get_hash();
		for ( int i = begin[code]; i != -1; i = next[i] ) {
			if ( msk[i] == new_msk )
				return make_pair(true, new_msk);
		}
	}
};*/

double dp(stuff_t cur) {
	if ( cur.size() && cur[0].second == 1 )
		return 0.0;
	if ( memo.count(cur) )
		return memo[cur];
	double res = 1.0;
	int sz = cur.size();
	for ( int i = 0; i < sz; i ++ )
		for ( int j = i + 1; j < sz; j ++ ) {
			stuff_t nxt = cur;
			nxt[i].second --, nxt[j].second --;
			int n1 = nxt[i].first, n2 = nxt[j].first;
			for ( int k = 0; k < sz; k ++ )
				if ( nxt[k].second == 0 ) {
					swap(nxt[k], nxt.back());
					nxt.pop_back();
					sz --;
				}
			bool found = false;
			for ( int k = 0; k < sz; k ++ )
				if ( nxt[k].first == n1 + n2 ) {
					found = true;
					nxt[k].second ++;
					break;
				}
			if ( !found )
				nxt.push_back(make_pair(n1 + n2, 1));
			sort(nxt.begin(), nxt.end());
			res += dp(nxt);
		}
	memo[cur] = res;
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n;

	scanf("%d", &n);
	stuff_t init(1);
	init[0] = make_pair(1, n);
	printf("%.3lf\n", dp(init));
}
