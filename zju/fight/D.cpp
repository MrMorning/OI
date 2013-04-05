#include <cstring>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
using namespace std;
typedef set<int>::iterator itr_t;

const int N_MAX = 30010;

int idt[N_MAX];
pair<int, int> ele[N_MAX];
int my_set[2][N_MAX];
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

int binsearch(int des[], int n, int x) {
	int lb = 0, rb = n;
	for ( int mid = (lb + rb) / 2; lb < rb - 1;
	   mid = (lb + rb) / 2 ) 
		if ( des[mid] <= x )
			lb = mid;
		else
			rb = mid;
	return lb;
}	

int main() {
	freopen("t.in", "r", stdin);
	while ( scanf("%d%d", &lb, &rb) != EOF ) {
		memset(idt, 0, sizeof(idt));

		int n;
		int m1 = 0, m2 = 0;
		scanf("%d", &n);
		for ( int i = 0; i < n; i ++ ) {
			int k, b;
			scanf("%d%d", &k, &b);
			int y1 = lb * k + b,
				y2 = rb * k + b;
			ele[i].first = y1, ele[i].second = y2;
			my_set[0][m1 ++] = y1;
			my_set[1][m2 ++] = y2;
		}
		sort(my_set[0], my_set[0] + m1);
		sort(my_set[1], my_set[1] + m2);
		for ( int i = 0; i < n; i ++ ) {
			ele[i].first = 1 + binsearch(my_set[0], m1, ele[i].first);
			ele[i].second = 1 + binsearch(my_set[1], m2, ele[i].second);
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
