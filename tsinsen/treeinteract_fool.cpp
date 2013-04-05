int size();
int type();
int question(int p, int q);
void submit(int x);
#include <map>
#include <algorithm>
using namespace std;
int treeSz, treeTp;
int myQuest(int p, int q) {
	//if(p == q)
	//  assert(0);
	if ( treeSz <= 5000 && treeTp != 3 ) {
		static map<pair<int, int>, int> mp;
		if ( !mp.count(make_pair(p, q)) ) 
			mp[make_pair(p, q)] = question(p, q);
		return mp[make_pair(p, q)];
	} else return question(p, q);   
}
namespace solve1 {
	const int kLenMax = 300010;
	int a[kLenMax];
	void mySort(int l, int r) {
		static int mem[kLenMax], res[kLenMax];
		if ( l >= r ) return;
		int x = rand() % (r-l+1)+l;
		swap(a[x], a[l]);
		mem[l] = a[l];
		for ( int k = l + 1; k <= r; k ++ ) {
			res[k] = myQuest(a[k], a[l]);
			mem[k] = a[k];
		}
		int p = l, q = r;
		for ( int k = l + 1; k <= r; k ++ ) {
			if ( res[k] == 1 )
				a[p++] = mem[k];
			else
				a[q--] = mem[k];
		}
		a[p] = mem[l];
		mySort(l, p-1);
		mySort(p+1, r);
	}
	void main() {
		int n = size();
		for ( int i = 1; i <= n; i ++ )
			a[i] = i;
		random_shuffle(a+1, a+1+n);
		mySort(1, n);
		for ( int i = 1; i <= n; i ++ )
			submit(a[i]);
	}
}
namespace solve2 {
	const int kLenMax = 300010;
	int pa[kLenMax];
	int a[kLenMax];
	void solve(int l, int r) {
		static int res[kLenMax];
		if ( l > r ) return;
		if ( l == r ) {
			submit(a[l]);
			return;
		}
		int mi1 = -1, mi2 = -1;
		while ( mi1 == -1 || mi2 == -1 ) {
			mi1 = -1, mi2 = -1;
			int x = rand() % (r-l+1)+l;
			for ( int k = l; k <= r; k ++ )
				if ( k != x )
					res[k] = myQuest(a[k], a[x]);
				else
					res[k] = 0;
			mi1 = a[x];
			for ( int k = l; k <= r; k ++ )
				if ( res[k] == 1 ) {
					if ( myQuest(a[k], mi1) == 1 ) {
						mi2 = mi1;
						mi1 = a[k];
					} else if ( mi2 == -1 || myQuest(a[k], mi2) == 1 ) {
						mi2 = a[k];
					}
				}
		}
		static int tmpl[kLenMax], tmpr[kLenMax];
		int lpos = 0, rpos = 0;
		tmpl[lpos++] = mi2;
		for ( int k = l; k <= r; k ++ )
			if ( a[k] != mi1 && a[k] != mi2 ) {
				if ( myQuest(mi2, a[k]) == 1 )
					tmpl[lpos++] = a[k];
				else
					tmpr[rpos++] = a[k];
			}
		a[l] = mi1;
		int t = l+1, tl = lpos;
		while ( lpos ) a[t++] = tmpl[--lpos];
		while ( rpos ) a[t++] = tmpr[--rpos];
		submit(mi1);        
		solve(l+1, l+tl);
		solve(l+tl+1, r);

	}
	void main() {
		int n = size();
		for ( int i = 1; i <= n; i ++ )
			a[i] = i;
		random_shuffle(a+1, a+1+n);
		solve(1, n);
	}
}
int main() {
	srand(42);
	treeSz = size();
	treeTp = type();
	if ( type() == 1 )
		solve1::main();
	else if ( type() == 2 )
		solve2::main();
	else
		solve2::main();
}
