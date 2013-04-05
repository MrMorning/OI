#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> coord_t;
const int N_MAX = 1010;
const int OFFSET[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int n, a[N_MAX][N_MAX];
bool vis[N_MAX][N_MAX];
int nridge, nvalley;
void bfs(int stx, int sty){
	static coord_t Q[N_MAX * N_MAX];
	int qt = 0;
	Q[qt ++] = make_pair(stx, sty);
	vis[stx][sty] = true;
	bool isridge = true, isvalley = true;
	for(int i = 0; i < qt; i ++){
		coord_t u = Q[i];
		for(int d = 0; d < 8; d ++){
			coord_t v;
			v.first = u.first + OFFSET[d][0];
			v.second= u.second+ OFFSET[d][1];
			if(0 <= v.first && v.first < n)
				if(0 <= v.second && v.second < n){
					if(!vis[v.first][v.second] && a[v.first][v.second] == a[stx][sty]){
						vis[v.first][v.second] = true;
						Q[qt ++] = v;
					}
					else if(a[v.first][v.second] != a[stx][sty]){
						if(a[v.first][v.second] > a[stx][sty])
							isridge = false;
						if(a[v.first][v.second] < a[stx][sty])
							isvalley = false;
					}
				}
		}
	}
	nridge += isridge;
	nvalley += isvalley;
}
int main(){
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%d", &a[i][j]);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			if(!vis[i][j])
				bfs(i, j);
	printf("%d %d", nridge, nvalley);
}
