#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MIN(a,b) ((a)<(b)?(a):(b))
#define INPUT "t.in"
#define OUTPUT "t.out"
//#define STDIO
namespace Solve
{
	typedef long long Val_t;
#define VAL_T_FMT "%lld"
	const int MAXN = 100001;
	const Val_t INFINITY = 2000000000000000000ll;
	const Val_t SQRT_INFINITY = 1000000000;
	struct Node
	{
		int l, r;
		int color, tag;
	};
	class SegTree
	{
		private:
			Node node[MAXN << 2];
			void build(int i, int l, int r);
			void setMark(int i, int color);
			void pushMark(int i);
			void update(int i);
			void change(int i, int l, int r, int color);
			int ask(int i, int pos);
		public:
			SegTree();
			void change(int l, int r, int color);
			int ask(int pos);
	};
	int n, l;
	Val_t sum[MAXN], f[MAXN];

	Val_t w(int j, int i);
	void solve(FILE *fin, FILE *fout);
	void work(FILE *fin, FILE *fout);
	void force(FILE *fin, FILE *fout);
	void debug();
}
/*{{{*/
Solve::SegTree::SegTree()
{
	build(1, 1, n);
}

void Solve::SegTree::change(int l, int r, int color)
{
	change(1, l, r, color);
}

int Solve::SegTree::ask(int pos)
{
	return ask(1, pos);
}

void Solve::SegTree::build(int i, int l, int r)
{
	Node &x = node[i];
	x.l = l, x.r = r, x.tag = -1, x.color = 0;
	if(l < r)
		build(i * 2, l, (l + r) / 2), build(i * 2 + 1, (l + r) / 2 + 1, r);
}

void Solve::SegTree::change(int i, int l, int r, int color)
{
	Node &x = node[i];
	if(l > x.r || r < x.l) return;
	if(l <= x.l && x.r <= r)
	{
		setMark(i, color);
		return;
	}
	pushMark(i);
	change(i * 2, l, r, color), change(i * 2 + 1, l, r, color);
	update(i);
}

int Solve::SegTree::ask(int i, int pos)
{
	Node &x = node[i];
	if(pos > x.r || pos < x.l) return 0;
	if(x.l <= pos && pos <= x.r && x.color != -1)
		return x.color;
	pushMark(i);
	int tmp = ask(i * 2, pos) + ask(i * 2 + 1, pos);
	update(i);
	return tmp;
}

void Solve::SegTree::setMark(int i, int color)
{
	Node &x = node[i];
	x.color = color, x.tag = color;
}

void Solve::SegTree::pushMark(int i)
{
	Node &x = node[i];
	if(x.tag != -1)
	{
		setMark(i * 2, x.tag), setMark(i * 2 + 1, x.tag);
		x.tag = -1;
	}
}

void Solve::SegTree::update(int i)
{
	Node &x = node[i], &lch = node[i * 2], &rch = node[i * 2 + 1];
	if(lch.color == rch.color)
		x.color = lch.color;
	else
		x.color = -1;
}/*}}}*/

void Solve::debug()
{
	n = 5;
	SegTree T;
	T.change(1, 1, 1);
	T.change(3, 3, 2);
	T.change(2, 4, 3);
	T.change(2, 4, 1);
	printf("%d\n", T.ask(5));
}

Solve::Val_t Solve::w(int j, int i)
{
	Val_t tmp = sum[i] - sum[j] + i - j - 1 - l;
	if(tmp > SQRT_INFINITY)
		return INFINITY;
	else
		return tmp * tmp;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d%d", &n, &l);
	for(int i = 1; i <= n; i ++)
		f[i] = INFINITY;
	f[0] = 0;
	sum[0] = 0;
	for(int i = 1; i <= n; i ++)
	{
		int t;
		fscanf(fin, "%d", &t);
		sum[i] = sum[i - 1] + t;
	}
//	force(fin, fout);
	work(fin, fout);
}

void Solve::work(FILE *fin, FILE *fout)
{
	SegTree tree;
	for(int i = 1; i <= n; i ++)
	{
		int t = tree.ask(i);
		f[i] = MIN(INFINITY, f[t] + w(t, i));
		int l = i + 1, r = n, mid = (l + r) / 2;
		while(l < r)
		{
			Val_t tmp = MIN(INFINITY, f[i] + w(i, mid));
			int s = tree.ask(mid);
			if(s == 0 || f[s] + w(s, mid) > tmp)
				r = mid;
			else
				l = mid + 1;
			mid = (l + r) / 2;
		}
		tree.change(mid, n, i);
	}
	fprintf(fout, VAL_T_FMT "\n", f[n]);
}

void Solve::force(FILE *fin, FILE *fout)
{
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < i; j ++)
			f[i] = MIN(f[i], f[j] + w(j, i));
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
