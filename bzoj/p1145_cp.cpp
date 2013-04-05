#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N_MAX = 200010;
const int MOD = 16777215;

#define LOWBIT(x) ((x) & -(x)) 

namespace stat1 {
	//pattern: 1234

	struct IndexTree {
		int ele[N_MAX];
		int sum(int i) {
			i ++;
			int res = 0;
			for (; i; i -= LOWBIT(i) )
				res = (res + ele[i]) & MOD;
			return res;
		}
		void add(int i, int val) {
			i ++;
			for (; i < N_MAX; i += LOWBIT(i) )
				ele[i] = (ele[i] + val) & MOD;
		}
		void clear() {
			memset(ele, 0, sizeof(ele));
		}
	} idt[3];

	int arr[N_MAX];
	int arr_size;

	int solve() {
		idt[0].clear();
		idt[1].clear();
		idt[2].clear();
		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ ) {
			idt[0].add(arr[i], 1);
			idt[1].add(arr[i], idt[0].sum(arr[i] - 1));
			idt[2].add(arr[i], idt[1].sum(arr[i] - 1));
			res = (res + idt[2].sum(arr[i] - 1)) & MOD;
		}
		return res;
	}

	int brute() {
		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ )
			for ( int j = i + 1; j <= arr_size; j ++ )
				for ( int k = j + 1; k <= arr_size; k ++ )
					for ( int l = k + 1; l <= arr_size; l ++ )
						if ( arr[i] < arr[j] && arr[j] < arr[k] && arr[k] < arr[l] )
							res ++;
		return res & MOD;
	}

	void debug() {
		arr_size = 100;
		for ( int i = 1; i <= arr_size; i ++ )
			arr[i] = i;
		random_shuffle(arr + 1, arr + 1 + arr_size);
		assert(solve() == brute());
	}
}

namespace stat2 {
	//pattern: 1XXX
	struct IndexTree {
		int ele[N_MAX];
		int sum(int i) {
			i = N_MAX - i - 1;
			int res = 0;
			for (; i; i -= LOWBIT(i) )
				res = (res + ele[i]) & MOD;
			return res;
		}
		void add(int i, int val) {
			i = N_MAX - i - 1;
			for (; i < N_MAX; i += LOWBIT(i) )
				ele[i] = (ele[i] + val) & MOD;
		}
		void clear() {
			memset(ele, 0, sizeof(ele));
		}
	} idt;

	int arr[N_MAX];
	int arr_size;

	int solve() {
		idt.clear();
		int res = 0;
		for ( int i = arr_size; i >= 1; i -- ) {
			idt.add(arr[i], 1);
			int tmp = idt.sum(arr[i] + 1);
			if ( tmp >= 3 ) {
				tmp = ((ll)tmp * (tmp - 1) * (tmp - 2) / 6) & MOD;
				res = (res + tmp) & MOD;
			}
		}
		return res;
	}

	int brute() {
		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ )
			for ( int j = i + 1; j <= arr_size; j ++ )
				for ( int k = j + 1; k <= arr_size; k ++ )
					for ( int l = k + 1; l <= arr_size; l ++ )
						if ( arr[i] < arr[j] && arr[i] < arr[k] && arr[i] < arr[l] )
							res ++;
		return res & MOD;
	}

	void debug() {
		arr_size = 100;
		for ( int i = 1; i <= arr_size; i ++ )
			arr[i] = i;
		random_shuffle(arr + 1, arr + 1 + arr_size);
		assert(solve() == brute());
	}

}

namespace stat3 {
	//pattern: 1X2X
	struct IndexTree1 {
		int ele[N_MAX];
		int sum(int i) {
			i ++;
			int res = 0;
			for (; i; i -= LOWBIT(i) )
				res = (res + ele[i]) & MOD;
			return res;
		}
		void add(int i, int val) {
			i ++;
			for (; i < N_MAX; i += LOWBIT(i) )
				ele[i] = (ele[i] + val) & MOD;
		}
		void clear() {
			memset(ele, 0, sizeof(ele));
		}
	} idt1;
	
	struct IndexTree2 {
		int ele[N_MAX];
		int sum(int i) {
			i = N_MAX - i - 1;
			int res = 0;
			for (; i; i -= LOWBIT(i) )
				res = (res + ele[i]) & MOD;
			return res;
		}
		void add(int i, int val) {
			i = N_MAX - i - 1;
			for (; i < N_MAX; i += LOWBIT(i) )
				ele[i] = (ele[i] + val) & MOD;
		}
		void clear() {
			memset(ele, 0, sizeof(ele));
		}
	} idt2[2];

	int arr[N_MAX];
	int arr_size;

	int solve() {
		idt2[0].clear(); idt2[1].clear();
		idt1.clear();

		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ )
			idt2[0].add(i, 1);
		for ( int i = 1; i <= arr_size; i ++ ) {
			idt1.add(arr[i], 1);
			idt2[0].add(arr[i], -1);
			idt2[1].add(arr[i], i);

			int k = idt1.sum(arr[i] - 1),
				s = idt2[1].sum(arr[i] + 1),
				w = idt2[0].sum(arr[i] + 1);

			int tmp = ((ll)(i - 1) * (i - 2) / 2) & MOD;
			tmp = (tmp - ((ll)(i - 1) * (i - 1 - k) - s ) ) & MOD;
			tmp = (tmp - (ll)k * (k - 1) / 2) & MOD;
			res = (res + (ll)tmp * w) & MOD;
		}
		return res;
	}

	int brute() {
		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ )
			for ( int j = i + 1; j <= arr_size; j ++ )
				for ( int k = j + 1; k <= arr_size; k ++ )
					for ( int l = k + 1; l <= arr_size; l ++ )
						if ( arr[i] < arr[k] && arr[j] > arr[k] && arr[l] > arr[k] )
							res ++;
		return res & MOD;
	}

	void debug() {
		arr_size = 100;
		for ( int i = 1; i <= arr_size; i ++ )
			arr[i] = i;
		random_shuffle(arr + 1, arr + 1 + arr_size);
		assert(solve() == brute());
	}

}

namespace stat4 {
	//pattern: 13XX
	
	struct Info {
		int f, s0, s1;
		bool e;
		Info(bool _e = true):
			e(_e){}
		void set(int val) {
			if ( val == 0 )
				s0 = 1;
			else
				s1 = 1;
			f = 0;
		}
	};

	Info operator+ (const Info &A, const Info &B) {
		if ( !A.e ) return B;
		if ( !B.e ) return A;
		Info res;
		res.s0 = A.s0 + B.s0;
		res.s1 = A.s1 + B.s1;
		res.f = (A.f + B.f + (((ll)A.s0 * B.s1) & MOD)) & MOD;
		return res;
	}

	struct Node {
		int l, r;
		Info info;
	} node[N_MAX * 4];

	void update(int i) {
		node[i].info = node[i * 2].info + node[i * 2 + 1].info;
	}

	void build(int i, int l, int r) {
		node[i].l = l, node[i].r = r;
		if ( l == r ) 
			node[i].info.set(0);
		else {
			int mid = (l + r) / 2;
			build(i * 2, l, mid);
			build(i * 2 + 1, mid + 1, r);
			update(i);
		}
	}

	void change(int pos, int new_val) {
		int cur = 1;
		for ( ;; ) {
			if ( node[cur].l == node[cur].r )
				break;
			int mid = (node[cur].l + node[cur].r) / 2;
			if ( pos <= mid )
				cur = cur * 2;
			else
				cur = cur * 2 + 1;
		}

		node[cur].info.set(new_val);
		for ( cur >>= 1; cur; cur >>= 1 ) 
			update(cur);
	}

	Info ask(int i, int l, int r) {
		if ( l > node[i].r || r < node[i].l )
			return Info(false);
		if ( l <= node[i].l && node[i].r <= r )
			return node[i].info;
		return ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
	}

	int arr[N_MAX], msk[N_MAX];
	int arr_size;

	int solve() {
//		static int ans[N_MAX];

		int res = 0;
		build(1, 1, arr_size);
		for ( int i = arr_size; i >= 1; i -- ) {
			change(arr[i], 1);
			msk[arr[i]] = 1;
			if ( arr[i] == arr_size || arr[i] == 1 )
				continue;
	//		Info I2 = ask(1, arr[i] + 1, arr_size),
	//			 I1 = ask(1, 1, arr[i] - 1);
			Info I1, I2;
			I2.s1 = I2.s0 = I2.f = 0;
			for ( int j = arr[i] + 1; j <= arr_size; j ++ ) {
				if ( msk[j] )
					I2.s1 ++;
				else
					I2.s0 ++;
			}

			I1.s1 = I1.s0 = I1.f = 0;
			for ( int j = 1; j < arr[i]; j ++ ) {
				if ( msk[j] )
					I1.s1 ++;
				else {
					I1.s0 ++;
					for ( int k = j + 1; k < arr[i]; k ++ )
						if ( msk[k] )
							I1.f ++;
				}
			}
			fprintf(stderr, "i=%d, I1.s0 = %d, I1.s1 = %d, I1.f = %d\n", i, I1.s0, I1.s1, I1.f);


			int tmp = ((ll)(I1.f + (((ll)I1.s0 * I2.s1) & MOD)) * I2.s1) & MOD;
			tmp -= ((ll)I2.s1 * I2.s1 * I1.s0) & MOD;
			tmp &= MOD;

			res = (res + tmp) & MOD;
//			ans[i] = tmp;
		}
//		for ( int i = 1; i <= arr_size; i ++ ) 
//			fprintf(stderr, "%d = %d\n", i, ans[i]);

		return res;
	}

	int brute() {
//		static int ans[N_MAX];
		int res = 0;
		for ( int i = 1; i <= arr_size; i ++ )
			for ( int j = i + 1; j <= arr_size; j ++ )
				for ( int k = j + 1; k <= arr_size; k ++ )
					for ( int l = k + 1; l <= arr_size; l ++ ) {
						static int tmp[4];
						tmp[0] = arr[i], tmp[1] = arr[j], tmp[2] = arr[k], tmp[3] = arr[l];
						sort(tmp, tmp + 4);
						if ( tmp[0] == arr[i] && tmp[2] == arr[j] ) {
							res ++;
						//	ans[j] ++;
						}
					}
		//for ( int i = 1; i <= arr_size; i ++ )
		//	fprintf(stderr, "%d = %d\n", i, ans[i]);
		return res & MOD;
	}

	void debug() {
		arr_size = 10;
		for ( int i = 1; i <= arr_size; i ++ )
			arr[i] = i;
		random_shuffle(arr + 1, arr + 1 + arr_size);
		assert(solve() == brute());
	}

}
int main() {
	stat1::debug();
	stat2::debug();
	stat3::debug();
	stat4::debug();
}
