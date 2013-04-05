#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int V_MAX = 2510;

const int offset[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int N, M;
int svtx;
int Q[V_MAX];
bool inQ[V_MAX];
int dist[V_MAX];
char board[55][55];


int main(){
	freopen("pageant.in", "r", stdin);
	freopen("pageant.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N; i ++){
		static char str[100];
		scanf("%s", str);
		for(int j = 0; j < M; j ++){
			board[i][j] = str[j];
			if(str[j] == 'X')
				svtx = i * M + j;
		}
	}

	memset(dist, 0x3f, sizeof(dist));
	dist[svtx] = 0;
	int qh = 0, qt = 0;
	Q[qt ++] = svtx;
	inQ[svtx] = true;
	while(qh != qt){
		int u = Q[qh];
		inQ[u] = false;
		qh = (qh + 1) % V_MAX;
		for(int d = 0; d < 4; d ++){
			int nx = u / M + offset[d][0],
				ny = u % M + offset[d][1];
			if(0 <= nx && nx < N)
				if(0 <= ny && ny < M){
					int v = nx * M + ny;
					int tmp = dist[u] + (board[nx][ny] == '.');
					if(dist[v] > tmp){
						dist[v] = tmp;
						if(!inQ[v]){
							inQ[v] = true;
							Q[qt] = v;
							qt = (qt + 1) % V_MAX;
						}
					}
				}
		}
	}
	int ans = 0x3f3f3f3f;
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < M; j ++)
			if(board[i][j] == 'X' && dist[i * M + j] > 0)
				ans = min(ans, dist[i * M + j]);
	printf("%d\n", ans);
}
