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
	struct State
	{
		int idx;
		Val_t val;
		State(){};
		State(int _idx, Val_t _val): idx(_idx), val(_val){};
	};
	class MonoQueue
	{
		private:
		public:
			State q[MAXP];
			int qh, qt;
			MonoQueue();
			void refresh(int i);
			void push(State x);
			State getMax();
	};
	Val_t f[MAXN][MAXP];
	int ap[MAXN], bp[MAXN], as[MAXN], bs[MAXN];
	int w, maxP, n;
	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin,  FILE *fout);
	void update(Val_t &x, Val_t val);
}

Solve::MonoQueue::MonoQueue()
{
	qt = qh = 0;
	memset(q, 0, sizeof(q));
}

void Solve::MonoQueue::refresh(int i)
{
	while(qh < qt && q[qh].idx < i)
		qh ++;
}

void Solve::MonoQueue::push(State x)
{
	while(qt > qh && q[qt - 1].val < x.val)
		qt --;
	q[qt ++] = x;
}

Solve::State Solve::MonoQueue::getMax()
{
		return q[qh];
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d %d %d\n", &n, &maxP, &w);
	for(int i = 1; i <= n; i ++)
		fscanf(fin, "%d %d %d %d\n", &ap[i], &bp[i], &as[i], &bs[i]);
	work(fin, fout);
}

void Solve::work(FILE *fin, FILE *fout)
{
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= maxP; j ++)
			f[i][j] = -INFINITY;
	f[0][0] = 0;
	for(int i = 1; i <= w; i ++)
		for(int j = 0; j <= as[i]; j ++)
			f[i][j] = - ap[i] * j;
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
				qB.push(State(j + bs[i], f[i - w - 1][j + bs[i]] + (j + bs[i]) * bp[i]));
			update(f[i][j], qA.getMax().val - j * ap[i]);
			update(f[i][j], qB.getMax().val - j * bp[i]);
		}
	}
	fprintf(fout, "%d\n", f[n][0]);
}

void Solve::update(Val_t &x, Val_t val)
{
	x = MAX(x, val);
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
