#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long double val_t;

const int WIDTH_MAX = 16;
const int N_ELE_MAX = WIDTH_MAX * WIDTH_MAX * 3;
const int OFFSET[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
const val_t EPS = 10E-9;

#define IS_WALL(x, y) (maze[x][y] == '#')
#define IS_SRC(x, y) (maze[x][y] == '$')
#define IS_COIN(x, y) ('0' < maze[x][y] && maze[x][y] <= '9')
#define IS_PIPE_SRC(x, y) ('a' <= maze[x][y] && maze[x][y] <= 'z')
#define IS_MONSTER(x, y) (maze[x][y] == '!')

#define ABS(x) ((x) > 0 ? (x) : -(x))

int n_row, n_col, n_pixel;
char maze[WIDTH_MAX][WIDTH_MAX];
val_t mat[N_ELE_MAX][N_ELE_MAX];

inline int get_idx(int x, int y)
{
	return x * n_col + y;
}

struct Crdnt
{
	int x, y;
	Crdnt(){}
	Crdnt(int _x, int _y)
		:x(_x), y(_y){}
	Crdnt(int idx)
	{
		x = idx / n_col;
		y = idx % n_col;
	}
};

struct Vertex
{
	vector<int> adj;
	bool is_term;
} vtx[N_ELE_MAX];

void read_data()
{
	scanf("%d %d\n", &n_row, &n_col);
	n_pixel = n_row * n_col;
	for(int i = 0; i < n_row; i ++, scanf("\n"))
		for(int j = 0; j < n_col; j ++)
			scanf("%c", &maze[i][j]);
}

void expand(int x, int y)
{
	if(IS_WALL(x, y))
		return;
	int cur = get_idx(x, y);
	if(IS_PIPE_SRC(x, y))
	{
		for(int i = 0; i < n_row; i ++)
			for(int j = 0; j < n_col; j ++)
				if(maze[x][y] + 'A' - 'a' == maze[i][j])
				{
					vtx[cur].adj.push_back(get_idx(i, j));
					break;
				}
		return;
	}
	for(int dir = 0; dir < 4; dir ++)
	{
		int nx = x + OFFSET[dir][0],
			ny = y + OFFSET[dir][1];
		if(0 <= nx && nx < n_row && 0 <= ny && ny < n_col)
			if(! IS_WALL(nx, ny))
				vtx[cur].adj.push_back(get_idx(nx, ny));
	}
}

void build_graph()
{
	for(int i = 0; i < n_row; i ++)
		for(int j = 0; j < n_col; j ++)
			expand(i, j);
}

bool check_terminal(int x, int y)
{
	static Crdnt queue[N_ELE_MAX];
	static bool vis[N_ELE_MAX];
	memset(vis, 0, sizeof(vis));
	int qh = 0, qt = 0;
	queue[qt ++] = Crdnt(x, y);
	vis[get_idx(x, y)] = true;
	while(qh < qt)
	{
		Crdnt u = queue[qh ++];
		if(IS_COIN(u.x, u.y))
			return false;
		int now = get_idx(u.x, u.y);
		for(vector<int>::iterator it = vtx[now].adj.begin(); it != vtx[now].adj.end(); it ++)
		{
			Crdnt next(*it);
			if(! vis[*it])
			{
				vis[*it] = true;
				queue[qt ++] = next;
			}
		}
	}
	return true;
}

void process_terminal()
{
	for(int i = 0; i < n_row; i ++)
		for(int j = 0; j < n_col; j ++)
			if(! IS_WALL(i, j))
				if(check_terminal(i, j))
					vtx[get_idx(i, j)].is_term = true;
}

void create_equation()
{
	for(int i = 0; i < n_row; i ++)
		for(int j = 0; j < n_col; j ++)
		{
			if(IS_WALL(i, j))
				continue;
			int cur = get_idx(i, j);
			if(vtx[cur].is_term)
				for(int d = 0; d < 3; d ++)
				{
					int tmp = d * n_pixel + cur;
					mat[tmp][tmp] = 1;//, mat[tmp][3 * n_pixel] = 0;
				}
			else
			{
				if(IS_COIN(i, j))
					for(int d = 0; d < 3; d ++)
						mat[d * n_pixel + cur][3 * n_pixel] = maze[i][j] - '0';
				int cnt = vtx[cur].adj.size();
				for(vector<int>::iterator it = vtx[cur].adj.begin(); it != vtx[cur].adj.end(); it ++)
					for(int d = 0; d < 3 - IS_MONSTER(i, j); d ++)
					{
						mat[d * n_pixel + cur][d * n_pixel + cur] = 1;
						mat[d * n_pixel + cur][(d + IS_MONSTER(i, j)) * n_pixel + *it] = -1 * (val_t)1 / cnt;
					}
				if(IS_MONSTER(i, j))
					mat[2 * n_pixel + cur][2 * n_pixel + cur] = 1;
			}
		}
}

void solve_equation()
{
	int j = 0, n = 3 * n_pixel;
	for(int i = 0; i < n; i ++)
	{
		int p = i;
		while(j <= n && ABS(mat[p][j]) < EPS)
		{
			p ++;
			if(p >= n)
				j ++, p = i;
		}
		if(j > n)
			break;
		for(int k = 0; k <= n; k ++)
			swap(mat[i][k], mat[p][k]);
		val_t tmp = mat[i][j];
		for(int k = 0; k <= n; k ++)
			mat[i][k] /= tmp;
		for(p = 0; p < n; p ++)
			if(p != i && ABS(mat[p][j]) > EPS)
			{
				tmp = mat[p][j];
				for(int k = 0; k <= n; k ++)
					mat[p][k] -= tmp * mat[i][k];
			}
	}
}

void output()
{
	Crdnt src;
	bool found = false;
	for(int i = 0; i < n_row && !found; i ++)
		for(int j = 0; j < n_col && !found; j ++)
			if(IS_SRC(i, j))
			{
				src = Crdnt(i, j);
				found = true;
			}
	int cur = get_idx(src.x, src.y);
	for(int k = 0; k < 3 * n_pixel; k ++)
		if(ABS(mat[k][cur] - 1) < EPS)
		{
			for(int j = 0; j < 3 * n_pixel; j ++)
				if(j != cur && ABS(mat[k][j]) > EPS)
				{
					printf("-1\n");
					return;
				}
			printf("%.9Lf\n", mat[k][3 * n_pixel]);
			return;
		}
	printf("-1\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	read_data();
	build_graph();
	//for(vector<int>::iterator it = vtx[3].adj.begin(); it != vtx[3].adj.end(); it ++)
	//	printf("%d\n", *it);
	process_terminal();
	create_equation();
	solve_equation();
	output();
}
