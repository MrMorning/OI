#include <cstdio>
#include <cstring>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_MAX = 1001;
struct MonoStack
{
	int stack[N_MAX][2], top;
	void push(int time, int val)
	{
		if(top && val >= stack[top - 1][1])
			return;
		stack[top][1] = val;
		stack[top][0] = time;
		top ++;
	}
	void pop(int deadline)
	{
		while(top && stack[top - 1][0] >= deadline)
			top --;
	}
	int get_min()
	{
		return stack[top - 1][1];
	}

	MonoStack()
	{
		top = 0;
	}
};

int f[4 * N_MAX];
bool map[N_MAX][N_MAX];
int up[N_MAX][N_MAX], ans[N_MAX][N_MAX];
int stack[N_MAX][2];

char next_char()
{
	char ch = getchar();
	while(ch != '.' && ch != '#')
		ch = getchar();
	return ch;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		memset(f, 0, sizeof(f));
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
			{
				map[i][j] = next_char() == '.';
				up[i][j] = map[i][j] ? up[i - 1][j] + 1 : 0;
			}
		for(int i = 1; i <= n; i ++)
		{
			int top = 0;
			MonoStack mono;
			for(int j = 1; j <= m; j ++)
			{
				if(up[i][j] > stack[top - 1][1])
				{
					stack[top][1] = up[i][j];
					stack[top][0] = j;
					top ++;
					mono.push(j, i - up[i][j] + 1 + j);
				}
				else
				{
					while(top && up[i][j] <= stack[top - 1][1])
					{
						mono.pop(stack[top - 1][0]);
						top --;
					}
					if(! map[i][j])
						continue;
					mono.push(stack[top][0], i - up[i][j] + 1 + stack[top][0]);
					stack[top][1] = up[i][j];
					top ++;
				}
				ans[i][j] = 2 * (i + j - mono.get_min() + 2);
				f[ans[i][j]] ++;
			}
		}
		for(int i = 1; i <= 2 * (m + n); i ++)
			if(f[i])
				printf("%d x %d\n", f[i], i);
	}
}
