#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 1000000000000000LL;
const int kEleMax = 200010;
int n;
ll kth;
ll axis[kEleMax];
ll arr[kEleMax];
struct IndexTree {
	int tree[kEleMax];
	void add(int i) {
		i += 2;
		for ( ; i < kEleMax; i += i & -i )
			tree[i] ++;
	}
	int sum(int i) { 
		i += 2;
		int res = 0;
		for ( ; i; i -= i & -i )
			res += tree[i];
		return res;
	}
	void clear() {
		memset(tree, 0, sizeof(tree));
	}
} idt;
ll check(ll bound) {
	int axisCnt = 0;
	for ( int i = 1; i <= n; i ++ ) {
		axis[axisCnt++] = arr[i - 1];
		axis[axisCnt++] = arr[i] - bound;
	}
	sort(axis, axis + axisCnt);
	axisCnt = unique(axis, axis + axisCnt) - axis;
	idt.clear();
	idt.add(lower_bound(axis, axis + axisCnt, 0) - axis);
	ll res = 0;
	for ( int i = 1; i <= n; i ++ ) {
		int t = lower_bound(axis, axis + axisCnt, arr[i] - bound) - axis;
		res += idt.sum(t);
		t = lower_bound(axis, axis + axisCnt, arr[i]) - axis;
		idt.add(t);
	}
	return res;
}
int main() {
	cin >> n >> kth;
	for ( int i = 1; i <= n; i ++ ) {
		cin >> arr[i];
		arr[i] = arr[i - 1] + arr[i];
	}
	ll lb = -inf, rb = inf;
	for ( ll mid = (lb + rb) / 2;
			lb < rb - 1; mid = (lb + rb) / 2 ) 
		if ( check(mid) >= kth )
			lb = mid;
		else
			rb = mid;
	cout << lb;
}
