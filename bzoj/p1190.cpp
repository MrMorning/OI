#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Object {
	int wei, val;
	int a, b;
	void doit() {
		for ( int i = 0; i <= 30; i ++ ) {
			if ( wei % (1 << i) == 0 ) {
				b = i, a = wei / (1 << i);
				if ( 1 <= a && a <= 10 )
					break;
			}
		}
	}
} obj[110];

int f[33][2010];
vector<int> vec[33];


int main() {
	freopen("t.in", "r", stdin);

	while ( 1 ) {
		int N, W;
		scanf("%d%d", &N, &W);
		if ( N == -1 )
			break;

		memset(vec, 0, sizeof(vec));
		for ( int i = 1; i <= N; i ++ ) {
			scanf("%d%d", &obj[i].wei, &obj[i].val);
			obj[i].doit();
			vec[obj[i].b].push_back(i);
		}
		memset(f, 0, sizeof(f));
		for ( int i = 30, lim = 0; i >= 0; i -- ) {
			for ( int j = 0; j <= lim; j ++ )
				f[i][2 * j + ((W >> i) & 1)] = f[i + 1][j];
			for ( int j = 2 * lim - 1; j >= 0; j -- )
				f[i][j] = max(f[i][j], f[i][j + 1]);
			lim = min(1000, W >> i);

			for ( int sz = vec[i].size(), k = 0; k < sz; k ++ ) {
				int ta = obj[vec[i][k]].a, tw = obj[vec[i][k]].val;
				for ( int j = 0; j + ta <= lim; j ++ ) 
					f[i][j] = max(f[i][j], f[i][j + ta] + tw);
			}
		}

		cout << f[0][0] << '\n';
	}
}
