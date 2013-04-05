#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

const int N_MAX = 50000, K_MAX = 501;
vector<int> son[N_MAX];
int f[N_MAX][K_MAX];
int N, K;
ll res = 0;

void solve(int cur, int pre) {
	int sz = son[cur].size();
	for ( int i = 0; i < sz; i ++ )
		if ( son[cur][i] == pre ) {
			son[cur].erase(son[cur].begin() + i);
			sz --;
			break;
		}
	for ( int i = 0; i < sz; i ++ )
		solve(son[cur][i], cur);
	f[cur][0] = 1;
	for ( int i = 0; i < sz; i ++ ) {
		int t = son[cur][i];
		for ( int j = 0; j < K; j ++ )
			res += f[cur][j] * f[t][K - j - 1];
		for ( int j = 0; j < K; j ++ )
			f[cur][j + 1] += f[t][j];
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	for ( int i = 0; i < N - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a --, b --;
		son[a].push_back(b);
		son[b].push_back(a);
	}
	solve(0, -1);
	cout << res;
}
