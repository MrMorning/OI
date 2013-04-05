#include <cstdio>
#include <cstring>

#define HEIVY_THAN 0
#define EQUAL 1
#define LIGHT_THAN 2
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
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
				f[i][j] = f[i][k] | f[j][k];

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

bool satisfy(int t[])
{
	static int eq[5];
	memcpy(eq, t, sizeof(int) * 5);
	for(int i = 1; i <= 2; i ++)
		for(int j = 3; j <= 4; j ++)
			if(eq[i] == eq[j])
				eq[i] = eq[j] = 0;
	if(eq[0] == HEIVY_THAN)
		return down[eq[1]] + down[eq[2]] > up[eq[3]] + up[eq[4]];
	else if(eq[0] == EQUAL)
		return down[eq[1]] + down[eq[2]] == down[eq[3]] + down[eq[4]] &&
			up[eq[1]] + up[eq[2]] == up[eq[3]] + up[eq[4]];
	else
		return up[eq[1]] + up[eq[2]] < down[eq[3]] + down[eq[4]];
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
				{
					printf("%d %d %d %d %d\n", A, B, type, i, j);
					cnt ++;
				}
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
