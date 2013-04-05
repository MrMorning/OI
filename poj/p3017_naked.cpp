#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"
namespace Solve
{
	typedef long long Val_t;
#define VAL_T_FMT "%lld"
	const int MAXN = 100001;
	const Val_t INFINITY = 99999999999;
	struct State
	{
		int idx;
	    Val_t val;
		State(){};
		State(int _idx, Val_t _val): idx(_idx), val(_val) {};
	};
	class MonoQueue
	{
		private:
			int qh, qt;
			State q[MAXN];
		public:
			MonoQueue();
			Val_t getMin(int cur);
			void push(State x);
			void refresh(int i);
	};
	Val_t f[MAXN];
	int a[MAXN], b[MAXN];
	int n;
	Val_t m;
	void initBound();
	void solve(FILE *fin, FILE *fout);
	void workForce(FILE *fin, FILE *fout);
	void workOpt(FILE *fin, FILE *fout);
	void test();
}

Solve::MonoQueue::MonoQueue()
{
	memset(q, 0, sizeof(q));
	qh = qt = 0;
}

Solve::Val_t Solve::MonoQueue::getMin(int cur)
{
	Val_t minVal = INFINITY;
	for(int i = qh; i < qt; i ++)
		minVal = MIN(minVal, f[q[i].idx] + MAX(i == qt - 1 ? 0 : q[i + 1].val, a[cur]));
	minVal = MIN(minVal, f[b[cur]] + MAX(q[qh].val, a[cur]));
	return minVal;
}

void Solve::MonoQueue::push(State x)
{
	while(qt > qh && q[qt - 1].val < x.val)
		qt --;
	q[qt ++] = x;
}

void Solve::MonoQueue::refresh(int i)
{
	while(q[qh].idx < i)
		qh ++;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d" VAL_T_FMT, &n, &m);
	a[0] = 0;
	for(int i = 1; i <= n; i ++)
		fscanf(fin, "%d", &a[i]);
	initBound();
	for(int i = 1; i <= n; i ++)
		f[i] = INFINITY;
	workForce(fin, fout);
}

void Solve::initBound()
{
	int i = 0, cnt = 0;
	for(int j = 1; j <= n; j ++)
	{
		cnt += a[j];
		while(cnt > m && i < j)
			cnt -= a[++ i];
		b[j] = i;
	}
}

void Solve::workForce(FILE *fin, FILE *fout)
{
	f[0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = b[i]; j < i; j ++)
		{
			Val_t maxNum = 0;
			for(int k = j + 1; k <= i; k ++)
				maxNum = MAX(maxNum, a[k]);
			f[i] = MIN(f[i], f[j] + maxNum);
		}
	if(f[n] == INFINITY)
		f[n] = -1;
	fprintf(fout, VAL_T_FMT "\n", f[n]);
}

void Solve::workOpt(FILE *fin, FILE *fout)
{
	f[0] = 0;
	MonoQueue queue;
	for(int i = 1; i <= n; i ++)
	{
		queue.refresh(b[i]);
		f[i] = queue.getMin(i);
		queue.push(State(i, a[i]));
	}
	if(f[n] == INFINITY)
		f[n] = -1;
	fprintf(fout, VAL_T_FMT "\n", f[n]);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
#endif
}
