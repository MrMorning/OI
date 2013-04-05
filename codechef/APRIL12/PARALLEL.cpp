#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Triple {
	int first, second, third;
	Triple(int a, int b, int c):
		first(a), second(b), third(c){}
};

vector<vector<Triple> > f(int N) {
	vector<vector<Triple> > res;
	if ( N <= 1 )
		return res;
	vector<Triple> step1;
	for ( int i = 1; i < N; i += 2 )
		step1.push_back(Triple(i - 1, i, i));
	res.push_back(step1);

	vector<vector<Triple> > g = f(N / 2);
	int ng = g.size();
	for ( int i = 0; i < ng; i ++ ) {
		vector<Triple> t = g[i];
		int nt = t.size();
		for ( int j = 0; j < nt; j ++ )
			t[j] = Triple(t[j].first * 2 + 1, t[j].second * 2 + 1, t[j].third * 2 + 1);
		res.push_back(t);
	}

	vector<Triple> step2;
	for ( int i = 2; i < N; i += 2 )
		step2.push_back(Triple(i - 1, i, i));
	res.push_back(step2);

	return res;
}

int main() {
	int N;
	scanf("%d", &N);

	vector<vector<Triple> > ans = f(N);
	int n_ans = ans.size();
	printf("%d\n", n_ans);

	for ( int i = 0; i < n_ans; i ++ ) {
		int m = ans[i].size();
		printf("%d", m);
		for ( int j = 0; j < m; j ++ ) 
			printf(" %d+%d=%d", ans[i][j].first + 1, ans[i][j].second + 1, ans[i][j].third + 1);
		printf("\n");
	}
}
