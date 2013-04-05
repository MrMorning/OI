#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
int TST, W, H, N, seed;
map<pair<int, pair<int, int> >, bool> mp;

double rv() {
	return (double)rand() / RAND_MAX * 123 * rand() / RAND_MAX;
}

/*int rv() {
	return rand() % 123;
}*/

int main() {
	freopen("t.in", "w", stdout);
	scanf("%d%d", &TST, &seed);
	srand(seed);
	printf("%d\n", TST);
	while ( TST -- ) {
		mp.clear();
		W = rand()%1000+1, H = rand()%1000+1;
		N = rand() % 30 + 1;
		printf("%d %d %d\n", W, H, N);
		for ( int i = 0; i < N; i ++ ) {
			double a = rv(), b = rv(), c = rv()+1;
		//	while ( mp.count(make_pair(a,make_pair(b,c))) )
		//		a = rv(), b = rv(), c = rv()+1;
		//	mp[make_pair(a,make_pair(b,c))] = true;
			printf("%.3lf %.3lf %.3lf\n", a, b, c);
		//	printf("%d %d %d\n", a, b, c);
		}
	}
}
