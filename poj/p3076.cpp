#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N_MAX = 16 * 16 * 16 + 10; // the maximum size of the input matrix
const int M_MAX = 16 * 16 * 4 + 10;

namespace dancing_link{

	int L[N_MAX * M_MAX], R[N_MAX * M_MAX],
		U[N_MAX * M_MAX], D[N_MAX * M_MAX], C[N_MAX * M_MAX];
	int S[M_MAX], O[N_MAX];

	int match[N_MAX][M_MAX];
	int n_res;

	bool done;

	struct Coord{
		int x, y;
	} pos[N_MAX * M_MAX];

	void cover(int c){
		L[R[c]] = L[c], R[L[c]] = R[c];
		for(int i = D[c]; i != c; i = D[i])
			for(int j = R[i]; j != i; j = R[j])
				U[D[j]] = U[j], D[U[j]] = D[j], S[C[j]] --;
	}

	void uncover(int c){
		for(int i = U[c]; i != c; i = U[i])
			for(int j = L[i]; j != i; j = L[j])
				S[C[j]] ++, U[D[j]] = j, D[U[j]] = j;
		L[R[c]] = c, R[L[c]] = c;
	}

	void search(int k){
		if(R[0] == 0){
			done = true;
			n_res = k;
			return;
		}
		int s = INF, c;
		for(int j = R[0]; j != 0; j = R[j])
			if(S[j] < s)
				c = j, s = S[j];
		cover(c);
		for(int r = D[c]; !done && r != c; r = D[r]){
			O[k] = r;
			for(int j = R[r]; j != r; j = R[j])
				cover(C[j]);
			search(k + 1);
			for(int j = L[r]; j != r; j = L[j])
				uncover(C[j]);
		}
		uncover(c);
	}

	void add(int x, int y, int &cnt){
		match[x][y] = cnt;
		pos[cnt].x = x, pos[cnt].y = y;
		cnt ++;
	}

	void build(int mat[N_MAX][M_MAX], int n, int m){
		memset(match, -1, sizeof(match));
		int cnt = 0;
		add(0, 0, cnt);
		for(int j = 1; j <= m; j ++)
			add(0, j, cnt);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				if(mat[i][j] == 1)
					add(i, j, cnt);
		for(int i = 0; i <= n; i ++){
			static int tmp[N_MAX];
			int n_tmp = 0;
			for(int j = 0; j <= m; j ++)
				if(match[i][j] != -1)
					tmp[n_tmp ++] = match[i][j];
			tmp[n_tmp] = tmp[0];
			for(int k = 0; k < n_tmp; k ++)
				R[tmp[k]] = tmp[k + 1];
			for(int k = 1; k <= n_tmp; k ++)
				L[tmp[k]] = tmp[k - 1];
		}
		for(int j = 0; j <= m; j ++){
			static int tmp[N_MAX];
			int n_tmp = 0;
			for(int i = 0; i <= n; i ++)
				if(match[i][j] != -1)
					tmp[n_tmp ++] = match[i][j], C[match[i][j]] = match[0][j];
			tmp[n_tmp] = tmp[0];
			for(int k = 0; k < n_tmp; k ++)
				D[tmp[k]] = tmp[k + 1];
			for(int k = 1; k <= n_tmp; k ++)
				U[tmp[k]] = tmp[k - 1];
			S[j] = n_tmp;
		}
	}

	bool covered[M_MAX];
	vector<int> main(int mat[N_MAX][M_MAX], int n, int m, const vector<int> &certain){
		build(mat, n, m);
		memset(covered, 0, sizeof(covered));
		for(int i = 0; i < (int)certain.size(); i ++){
			int r = certain[i];
			for(int j = 1; j <= m; j ++)
				if(match[r][j] != -1 && !covered[C[match[r][j]]])
					cover(C[match[r][j]]), covered[C[match[r][j]]] = true;
		}
		done = false;
		search(0);
		vector<int> res = certain;
		for(int i = 0; i < n_res; i ++)
			res.push_back(pos[O[i]].x);
		return res;
	}
}

const int n_row = 16 * 16 * 16, n_col = 4 * 16 * 16;
int mat[N_MAX][M_MAX];
int ans[17][17];
int num[17][17];
vector<int> certain;

void solve(){
	memset(mat, 0, sizeof(mat));
	for(int i = 1; i <= 16; i ++)
		for(int j = 1; j <= 16; j ++){
			int t = (i - 1) / 4 * 4 + (j - 1) / 4 + 1;
			for(int x = 1; x <= 16; x ++){
				int id = (i - 1) * 16 * 16 + (j - 1) * 16 + x;
				mat[id][(i - 1) * 16 + x] = 1;
				mat[id][16 * 16 + (j - 1) * 16 + x] = 1;
				mat[id][16 * 16 * 2 + (t - 1) * 16 + x] = 1;
				mat[id][16 * 16 * 3 + (i - 1) * 16 + j] = 1;
			}
		}
	certain.clear();
	for(int i = 1; i <= 16; i ++)
		for(int j = 1; j <= 16; j ++){
			int x = num[i][j];
			if(x)
				certain.push_back((i - 1) * 16 * 16 + (j - 1) * 16 + x);
		}

	vector<int> res = dancing_link::main(mat, n_row, n_col, certain);
	for(int i = 0; i < (int)res.size(); i ++){
		int t = res[i];
		int r = (t - 1) / (16 * 16) + 1,
			c = (t - 1) % (16 * 16) / 16 + 1,
			x = (t - 1) % 16 + 1;
		ans[r][c] = x;
	}
	for(int i = 1; i <= 16; i ++, puts(""))
		for(int j = 1; j <= 16; j ++)
			printf("%c", ans[i][j] + 'A' - 1);
}
int main(){
	freopen("t.in", "r", stdin);

	bool over = false;
	while(1){
		for(int i = 1; i <= 16; i ++){
			static char str[20];
			if(scanf("%s", str) == EOF){
				over = true;
				break;
			}

			for(int j = 1; j <= 16; j ++){
				char ch = str[j - 1];
				if(ch == '-')
					num[i][j] = 0;
				else
					num[i][j] = ch - 'A' + 1;
			}
		}
		if(over)
			break;
		solve();
		puts("");
	}
}