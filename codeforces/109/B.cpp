#include <cstdio>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

set<int> S[100010];
int main() {
	int n, m;

	//freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	while ( m -- ) {
		char cmd[5];
		int x;
		scanf("%s%d", cmd, &x);
		vector<int> vec;
		int tmp = x;
		for ( int i = 2, lim = (int)sqrt(x); i <= lim; i ++ ) {
			if ( tmp % i == 0 ) {
				while ( tmp % i == 0 )
					tmp /= i;
				vec.push_back(i);
			}
		}
		if ( x == 1 || tmp > 1 )
			vec.push_back(tmp);
		if ( cmd[0] == '+' ) {
			set<int>::iterator it = S[vec[0]].lower_bound(x);
			if ( it != S[vec[0]].end()
					&& (*it) == x ) {
				printf("Already on\n");
				continue;
			}

			bool fail = false;
			int mem;
			for ( int i = 0, sz = vec.size(); i < sz; i ++ ) 
				if ( S[vec[i]].size() ) {
					fail = true;
					mem = *S[vec[i]].begin();
					break;
				}
			if ( fail )
				printf("Conflict with %d\n", mem);
			else {
				for ( int i = 0, sz = vec.size(); i < sz; i ++ ) 
					S[vec[i]].insert(x);
				printf("Success\n");
			}
		} else {
			set<int>::iterator it = S[vec[0]].lower_bound(x);
			if ( it == S[vec[0]].end()
					|| (*it) != x ) {
				printf("Already off\n");
				continue;
			}
			for ( int i = 0, sz = vec.size(); i < sz; i ++ ) 
				S[vec[i]].erase(S[vec[i]].lower_bound(x));
			printf("Success\n");
		}
	}	
}
