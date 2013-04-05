#include <cstdio>
#include <cstring>

#define HEIVY_THAN 0
#define EQUAL 1
#define LIGHT_THAN 2
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define TRY(b) if(b) return true;
inline void swap(int &a, int &b){int c = a; a = b; b = c;}

const int N_MAX = 61;

int parent[N_MAX];
int find(int x){return parent[x] == x ? x : x = find(parent[x]);}
inline void merge(int x, int y){parent[find(x)] = find(y);}
int n, A, B;
int down[N_MAX], up[N_MAX];
char relation[N_MAX][N_MAX];
bool edge[N_MAX][N_MAX];
int in_dgr[N_MAX], out_dgr[N_MAX];
bool f[N_MAX][N_MAX];

void init()
{
	scanf("%d %d %d\n", &n, &A, &B);
	for(int i = 1; i <= n; i ++)
	{
		parent[i] = i;
		down[i] = 1;
		up[i] = 3;
	}
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 1; j <= n; j ++)
		{
			char ch;
			scanf("%c", &ch);
			relation[i][j] = ch;
			if(ch == '=')
				if(find(i) != find(j))
					merge(i, j);
		}
		getchar();
	}
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(relation[i][j] == '+' || relation[i][j] == '-')
			{
				int p = find(i), q = find(j);
				if(relation[i][j] == '-')
					swap(p, q);
				out_dgr[p] ++, in_dgr[q] ++;
				edge[p][q] = true;
				f[p][q] = true;
			}
}
void process()
{
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++)
				f[i][j] |= f[i][k] && f[k][j];

	for(int i = 1; i <= n; i ++)
	{
		int p = find(i);
		if(out_dgr[p])
		{
			down[p] = MAX(down[p], 2); 
			for(int j = 1; j <= n; j ++)
			{
				int q = find(j);
				if(p == q || ! edge[p][q]) continue;
				if(out_dgr[q])
				{
					down[p] = 3;
					break;
				}
			}
		}
		if(in_dgr[p])
		{
			up[p] = MIN(up[p], 2);
			for(int j = 1; j <= n; j ++)
			{
				int q = find(j);
				if(p == q || ! edge[q][p]) continue;
				if(in_dgr[q])
				{
					up[p] = 1;
					break;
				}
			}
		}
	}
}

inline bool equal(int x, int y)
{
	TRY(find(x) == find(y));
	return down[x] == up[x] && down[y] == up[y] && down[x] == down[y];
}

inline bool larger(int x, int y)
{
	TRY(f[x][y]);
	TRY(down[x] > up[y]);
	return false;
}

inline bool smaller(int x, int y)
{
	return larger(y, x);
}

bool satisfy(int eq[])
{
	int a = eq[1], b = eq[2], c = eq[3], d = eq[4];
	if(eq[0] == HEIVY_THAN)
	{
		TRY((equal(a, c) || down[a] >= up[c]) && larger(b, d));
		TRY(larger(a, c) && (equal(b, d) || down[b] >= up[d]));
		TRY(larger(a,c) && larger(b, d))

		TRY((equal(a, d) || down[a] >= up[d]) && larger(b, c));
		TRY(larger(a, d) && (equal(b, c) || down[b] >= up[c]));
		TRY(larger(a, d) && larger(b, c))
		return false;
	}
	else if(eq[0] == EQUAL)
	{
		TRY(equal(a, c) && equal(b, d));
		TRY(equal(a, d) && equal(b, c));
#define FIX(x) (up[x] == down[x])
		if(FIX(a) && FIX(b) && FIX(c) && FIX(d))
			TRY(up[a] + up[b] == up[c] + up[d]);
		return false;
	}
	else
	{
		TRY((equal(a, c) || up[a] <= down[c]) && smaller(b, d));
		TRY(smaller(a, c) && (equal(b, d) || up[b] <= down[d]));
		TRY(smaller(a, c) && smaller(b, d))

		TRY((equal(a, d) || up[a] <= down[d]) && smaller(b, c));
		TRY(smaller(a, d) && (equal(b, c) || up[b] <= down[c]));
		TRY(smaller(a, d) && smaller(b, c));
		return false;
	}
}

int stat(int type)
{
	int eq[5];
	int cnt = 0;
	eq[0] = type;
	eq[1] = find(A), eq[2] = find(B);
	for(int i = 1; i <= n; i ++)
		for(int j = i + 1; j <= n; j ++)
			if(i != A && i != B && j != A && j != B)
			{
				int p = find(i), q = find(j);
				eq[3] = p, eq[4] = q;
				if(satisfy(eq))
					cnt ++;
			}
	return cnt;
}
int main()
{
	freopen("t.in", "r", stdin);
	init();
	process();
	printf("%d\n", stat(HEIVY_THAN));
	printf("%d\n", stat(EQUAL));
	printf("%d\n", stat(LIGHT_THAN));
}
