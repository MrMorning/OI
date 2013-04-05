#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pair_t;
const int N_MAX = 1010;
const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int h[N_MAX][N_MAX], w[N_MAX][N_MAX];
pair_t arr[N_MAX * N_MAX];
int arr_size = 0;
int n, m;
struct Heap {
	pair_t ele[N_MAX * N_MAX];
	int n;
	Heap(){n=0;}
	void push(const pair_t &p) {
		ele[++n]=p;
		int i=n;
		while(i>1&&ele[i>>1]>ele[i])
			swap(ele[i>>1],ele[i]),i>>=1;
	}
	void pop() {
		swap(ele[n],ele[1]);
		n--;
		int i=1;
		while((i<<1)<=n) {
			if(ele[i]<=ele[i<<1]&&((i<<1)+1>n||ele[i]<=ele[(i<<1)+1]))
				break;
			int s=i<<1;
			if((i<<1)+1<=n&&ele[s]>ele[(i<<1)+1])
				s=(i<<1)+1;
			swap(ele[i],ele[s]);
			i=s;
		}
	}
	bool empty(){return n==0;}
	pair_t top() {
		return ele[1];
	}
} PQ;

int main() {
	freopen("t.in", "r", stdin);
	memset(w, 0x3f, sizeof(w));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++) {
			scanf("%d", &h[i][j]);
			if (h[i][j] > 0) {
				pair_t p = make_pair(abs(h[i][j]), (i << 16) + j);
				arr[arr_size ++] = p;
			}
		}
	int ans = 0;
	sort(arr, arr + arr_size);
	for (int i = 0; i < arr_size; i ++) {
		pair_t p = arr[i];
		int x = p.second >> 16,
			y = p.second & ((1 << 16) - 1);
		if (abs(h[x][y]) != w[x][y]) {
			ans ++;
			w[x][y] = abs(h[x][y]);
			PQ.push(p);
		}
		while (!PQ.empty()) {
			pair_t p = PQ.top(); PQ.pop();
			int x = p.second >> 16,
				y = p.second & ((1 << 16) - 1);
			for (int d = 0; d < 4; d ++) {
				int nx = x + offset[d][0],
					ny = y + offset[d][1];
				if (0 <= nx && nx < n)
					if (0 <= ny && ny < m) 
						if (w[nx][ny] > max(w[x][y], abs(h[nx][ny]))){
							w[nx][ny] = max(w[x][y], abs(h[nx][ny]));
							if (!(h[nx][ny] > 0 && w[nx][ny] != abs(h[nx][ny])))
								PQ.push(make_pair(abs(h[nx][ny]), (nx << 16) + ny));
						}
			}
		}
	}
	printf("%d\n", ans);
}
