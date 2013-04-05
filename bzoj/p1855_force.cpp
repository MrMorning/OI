#include <cstdio>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"
#define INFINITY 0x3f3f3f3f
namespace Solve
{
	const int MAXN = 2010,
		  MAXP = 2010;
	typedef int Val_t;
#define VAL_T_FMT "%d"
	struct Strategy
	{
		int i, j;
		Strategy(){};
		Strategy(int _i, int _j): i(_i), j(_j){};
	} s[MAXN][MAXP];
	class MonoQueue
	{
		private:
			int q[MAXP], qh, qt;
		public:
			MonoQueue();
			void refresh(int i);
			void push(State x);
			State getMax();
	}
	Val_t f[MAXN][MAXP];
	int ap[MAXN], bp[MAXN], as[MAXN], bs[MAXN];
	int w, maxP, n;
	void solve(FILE *fin, FILE *fout);
	void force(FILE *fin, FILE *fout);
	void workOpt1(FILE *fin,  FILE *fout);
	void update(int k, int l, int i, int j, Val_t val);
}

Solve::MonoQueue::MonoQueue()
{
	qt = qh = 0;
}

void MonoQueue::refresh(int i)
{
	while(q[qt].idx < i)
		qt ++;
}

void MonoQueue::push(State x)
{
	while(qt > 0 && q[qt - 1] < x)
		qt --;
	q[qt ++] = x;
}

Solve::State Solve::MonoQueue::getBest()
{
	return q[qh];
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d %d %d\n", &n, &maxP, &w);
	for(int i = 1; i <= n; i ++)
		fscanf(fin, "%d %d %d %d\n", &ap[i], &bp[i], &as[i], &bs[i]);
//	force(fin, fout);
	workOpt1(fin, fout);
}

void Solve::force(FILE *fin, FILE *fout)/*{{{*/
{
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= maxP; j ++)
			f[i][j] = -INFINITY;
	memset(s, -1, sizeof(s));
	f[0][0] = 0;
	for(int i = 0; i <= n - w - 1; i ++)
		for(int j = 0; j <= maxP; j ++)
		{
			f[i + 1][j] = MAX(f[i + 1][j], f[i][j]);
			for(int k = i + w + 1; k <= n; k ++)
			{
				int uplim = MIN(j + as[k], maxP);
				for(int l = j; l <= uplim; l ++)
					update(k, l, i, j, f[i][j] - ap[k] * (l - j));
				int downlim = MAX(j - bs[k], 0);
				for(int l = downlim; l < j; l ++)
					update(k, l, i, j, f[i][j] + bp[k] * (j - l));
			}
		}
	fprintf(fout, VAL_T_FMT "\n", f[n][0]);
}

void Solve::workOpt1(FILE *fin, FILE *fout)
{
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= maxP; j ++)
			f[i][j] = -INFINITY;
	memset(s, -1, sizeof(s));
	f[0][0] = 0;
	for(int i = 0; i <= n - w - 1; i ++)
		for(int j = 0; j <= maxP; j ++)
		{
			update(i + 1, j, i, j, f[i][j]);
			//f[i + 1][j] = MAX(f[i + 1][j], f[i][j]);
			int k = i + w + 1;
			for(int l = j; l <= MIN(j + as[k], maxP); l ++)
				update(k, l, i, j, f[i][j] - ap[k] * (l - j));
			for(int l = MAX(j - bs[k], 0); l < j; l ++)
				update(k, l, i, j, f[i][j] + bp[k] * (j - l));
		}
	fprintf(fout, VAL_T_FMT "\n", f[n][0]);
	for(int i = 0; i <= n; i ++)
	{
		for(int j = 0; j <= maxP; j ++)
			fprintf(fout, "(%2d, %2d) ", s[i][j].i, s[i][j].j);
		fprintf(fout, "\n");
	}
}/*}}}*/

void Solve::workOpt2(FILE *fin, FILE *fout)
{
	for(int j = 0; j <= maxP; j ++)
		f[0][j] = -INFINITY;
	f[0][0] = 0;
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 0; j <= maxP; j ++)
			update(f[i][j], f[i - 1][j]);
		MonoQueue qA, qB;
		if(i - w - 1 < 0)
			continue;
		for(int k = 0; k < bs[i]; k ++)
			qB.push(State(k, f[i - w - 1][k] + k * bp[i]));
		for(int j = 0; j <= maxP; j ++)
		{
			qA.refresh(MAX(0, j - as[i])), qB.refresh(j);
			qA.push(State(j, f[i - w - 1][j] + j * ap[i]));
			if(j + bs[i] <= maxP)
				qB.push(State(j, f[i - w - 1][j + bs[i]] + (j + bs[i]) * bp[i]));
			update(f[i][j], qA.getMax() - j * ap[i]);
			update(f[i][j], qB.getMax() - j * bp[i]);
		}
	}
	fprintf(fout, "%d\n", f[n][0]);
}

void Solve::update(int k, int l, int i, int j, Val_t val)
{
	if(f[k][l] < val)
	{
		f[k][l] = val;
		s[k][l] = Strategy(i, j);
	}
}

int main()
{
#ifdef JUDGE
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
#endif
}
