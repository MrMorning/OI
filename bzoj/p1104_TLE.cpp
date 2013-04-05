#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pair_t;
priority_queue<pair_t, vector<pair_t>, greater<pair_t> > PQ;
const int N_MAX = 1010;
const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int h[N_MAX][N_MAX], w[N_MAX][N_MAX];
bool inQ[N_MAX][N_MAX];
pair_t arr[N_MAX * N_MAX];
int arr_size = 0;
int n, m;

int main() {
	freopen("t.in", "r", stdin);
	memset(w, 0x3f, sizeof(w));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++) {
			scanf("%d", &h[i][j]);
			if (h[i][j] > 0) {
				pair_t p = make_pair(abs(h[i][j]), i * m + j);
				arr[arr_size ++] = p;
			}
		}
	int ans = 0;
	sort(arr, arr + arr_size);
	for (int i = 0; i < arr_size; i ++) {
		pair_t p = arr[i];
		int x = p.second / m,
			y = p.second % m;
		if (abs(h[x][y]) != w[x][y]) {
			ans ++;
			w[x][y] = abs(h[x][y]);
			PQ.push(p);
			inQ[x][y] = true;
		}
		while (!PQ.empty()) {
			pair_t p = PQ.top(); PQ.pop();
			int x = p.second / m,
				y = p.second % m;
			inQ[x][y] = false;
			for (int d = 0; d < 4; d ++) {
				int nx = x + offset[d][0],
					ny = y + offset[d][1];
				if (0 <= nx && nx < n)
					if (0 <= ny && ny < m) 
						if (w[nx][ny] > max(w[x][y], abs(h[nx][ny]))){
							w[nx][ny] = max(w[x][y], abs(h[nx][ny]));
							if (!inQ[nx][ny]) {
								PQ.push(make_pair(abs(h[nx][ny]), nx * m + ny));
								inQ[nx][ny] = true;
							}
						}
			}
		}
	}
	printf("%d\n", ans);
}
