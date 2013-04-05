#include <cstdio>
#include <cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define STDIO
namespace Solve
{
	const int MAXN = 51,
		  MAXM = 51,
		  BABY_MAX = 11,
		  INFINITY = 0x3f3f3f3f;
	int n, m;
	struct Stuff
	{
		int a, d, hp;
	};
	Stuff object[MAXN][MAXM], llx, baby[BABY_MAX];
	int f[MAXN][MAXM][1024], w[MAXN][MAXM][BABY_MAX], lb[1025];
	int upperlim, nBaby;

	int ceilDiv(int a, int b);
	void update(int &x, int y);
	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin, FILE *fout);
}

int Solve::ceilDiv(int a, int b)
{
	if(a % b == 0)
		return a / b;
	else
		return (a + b) / b;
}

void Solve::update(int &x, int y)
{
	x = MAX(x, y);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int cnt = 1;
	for(int i = 0; i <= 10; i ++, cnt *= 2)
		lb[cnt] = i;
	fscanf(fin, "%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			fscanf(fin, "%d", &object[i][j].a);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			fscanf(fin, "%d", &object[i][j].d);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			fscanf(fin, "%d", &object[i][j].hp);
	fscanf(fin, "%d%d%d", &llx.a, &llx.d, &llx.hp);
	fscanf(fin, "%d", &nBaby);
	for(int i = 1; i <= nBaby; i ++)
		fscanf(fin, "%d%d%d", &baby[i].a, &baby[i].d, &baby[i].hp);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			Stuff &lyd = object[i][j];
			if(llx.a <= lyd.d)
				w[i][j][0] = INFINITY;
			else
			{
				int t1 = ceilDiv(lyd.hp, llx.a-lyd.d);
				int tmp = (t1 - 1) * MAX(0, lyd.a - llx.d);
				if(tmp >= llx.hp)
					w[i][j][0] = INFINITY;
				else
					w[i][j][0] = tmp;
			}
			for(int k = 1; k <= nBaby; k ++)
			{
				Stuff &bb = baby[k];
				if(bb.a <= lyd.d)
					w[i][j][k] = INFINITY;
				else
				{
					int t1 = ceilDiv(lyd.hp, bb.a - lyd.d);
					int tmp = (t1 - 1) * MAX(0, lyd.a - bb.d);
					if(tmp >= bb.hp)
					{
						int t2 = ceilDiv(bb.hp, lyd.a - bb.d);
						tmp = t2 * MAX(0, bb.a - lyd.d);
						//baby died
						if(llx.a <= lyd.d)
							w[i][j][k] = INFINITY;
						else
						{
							int t1 = ceilDiv(lyd.hp - tmp, llx.a-lyd.d);
							tmp = (t1 - 1) * MAX(0, lyd.a - llx.d);
							if(tmp >= llx.hp)
								w[i][j][k] = INFINITY;
							else
								w[i][j][k] = tmp;
						}
					}
					else
						w[i][j][k] = 0;
				}
			}
		}
	upperlim = (1 << nBaby) - 1;
	work(fin, fout);
}

void Solve::work(FILE *fin, FILE *fout)
{
	memset(f, 0, sizeof(f));
	for(int j = 1; j <= m; j ++)
		f[0][j][upperlim] = llx.hp;
	for(int i = 0; i < n; i ++)
		for(int j = 1; j <= m; j ++)
		{
			if(f[i][j][0] > 0)
			{
				update(f[i + 1][j][0], f[i][j][0] - w[i + 1][j][0]);
				if(j < m)
					update(f[i + 1][j + 1][0], f[i][j][0] - w[i + 1][j + 1][0]);
				if(j > 1)
					update(f[i + 1][j - 1][0], f[i][j][0] - w[i + 1][j - 1][0]);
			}
			for(int k = 1; k <= upperlim; k ++)
			{
				if(f[i][j][k] == 0)
					continue;
				int tmp = k;
				while(tmp)
				{
					int pos = tmp & ((~ tmp) + 1);
					int t = lb[pos] + 1;
					update(f[i + 1][j][k - pos], f[i][j][k] - w[i + 1][j][t]);
					if(j < m)
						update(f[i + 1][j + 1][k - pos], f[i][j][k] - w[i + 1][j + 1][t]);
					if(j > 1)
						update(f[i + 1][j - 1][k - pos], f[i][j][k] - w[i + 1][j - 1][t]);
					tmp -= pos;
				}
			}
		}
	int ans = 0;
	for(int j = 1; j <= m; j ++)
		for(int k = 0; k <= upperlim; k ++)
			ans = MAX(ans, f[n][j][k]);
	if(ans == 0)
		fprintf(fout, "-1\n");
	else
		fprintf(fout, "%d\n", ans);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen("t.in", "r");
	Solve::solve(fin, stdout);
#endif
}
