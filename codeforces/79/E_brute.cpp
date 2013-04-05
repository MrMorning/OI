#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int N, M, P;
int X[20010], Y[20010];
int f[20][20010];

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> N >> M >> P;
	for ( int i = 0; i < N; i ++ )
		cin >> X[N - i];
	for ( int j = 0; j < M; j ++ )
		cin >> Y[M - j];
	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= M; j ++ ) {
			f[i][j] = max(f[i - 1][j], f[i][j - 1]) + (X[i] + Y[j]) % P;
		}
	cout << f[N][M];
}
