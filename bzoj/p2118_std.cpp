#define INPUT "t.in"
#define OUTPUT "t.out"

#include <cstdio>
#include <algorithm>

using std::sort;

namespace Solve
{
	typedef long long int Bignum_t;
#ifdef unix
#define BIGNUM_T_FMT "%lld"
#else
#define BIGNUM_T_FMT "%I64d"
#endif

	const int N_MAX = 12,
		  A_VAL_MAX = 4 * 100000;
	const Bignum_t INFINITE_BIGNUM = 1ll << 60;

	int n;
	Bignum_t Bmin, Bmax;
	int a[N_MAX];
	void solve(FILE *fin, FILE *fout);

	Bignum_t dist[A_VAL_MAX];
	void dijkstra();

	namespace Heap
	{
		const int NVTX_MAX = A_VAL_MAX;
		int n;
		int vtx2pos[NVTX_MAX];
		int pos2vtx[NVTX_MAX];
		int val[NVTX_MAX];
		int extract_min_vtx();
		inline bool empty()
		{ return !n; }
		void decrease_key(int v0, int d0);
		bool in_heap[NVTX_MAX];
		void init(int nvtx);
	}

	Bignum_t calc_valid_state(Bignum_t bound, Bignum_t start);
}

int Solve::Heap::extract_min_vtx()
{
	int ret = pos2vtx[1];
	int vtx = pos2vtx[n];
	int register v = val[n];
	n --;

	int register i = 1, j = 2;
	while (j <= n)
	{
		if (j < n && val[j + 1] < val[j])
			j ++;
		if (v <= val[j])
			break;
		val[i] = val[j];
		pos2vtx[i] = pos2vtx[j];
		vtx2pos[pos2vtx[i]] = i;
		i = j, j <<= 1;
	}
	pos2vtx[i] = vtx;
	vtx2pos[vtx] = i;
	val[i] = v;
	return ret;
}

void Solve::Heap::init(int nvtx)
{
	decrease_key(0, 0);
}

void Solve::Heap::decrease_key(int v0, int d0)
{
	if (!in_heap[v0])
	{
		n ++;
		vtx2pos[v0] = n;
		pos2vtx[n] = v0;
		val[n] = d0;
		in_heap[v0] = true;
	}

	int register j = vtx2pos[v0], i = j >> 1, v = d0;

	while (i)
	{
		if (val[i] <= v)
			break;
		val[j] = val[i];
		pos2vtx[j] = pos2vtx[i];
		vtx2pos[pos2vtx[j]] = j;
		j = i, i >>= 1;
	}

	pos2vtx[j] = v0;
	vtx2pos[v0] = j;
	val[j] = v;
}

void Solve::dijkstra()
{
	int nvtx = a[0];
	for (int i = 1; i < nvtx; i ++)
		dist[i] = INFINITE_BIGNUM;
	dist[0] = 0;

	Heap::init(nvtx);
	while (!Heap::empty())
	{
		int v0 = Heap::extract_min_vtx();
		Bignum_t d0 = dist[v0];
		for (int i = 1; i < n; i ++)
		{
			int v1 = (v0 + a[i]) % nvtx;
			Bignum_t d1 = d0 + a[i];
			if (d1 < dist[v1])
			{
				dist[v1] = d1;
				Heap::decrease_key(v1, d1);
			}
		}
	}
}

Solve::Bignum_t Solve::calc_valid_state(Bignum_t bound, Bignum_t start)
{
	if (bound < start)
		return 0;
	return (bound - start) / a[0] + 1;
}

void Solve::solve(FILE *fin, FILE *fout)
{
	fscanf(fin, "%d" BIGNUM_T_FMT BIGNUM_T_FMT, &n, &Bmin, &Bmax);
	for (int i = 0; i < n; i ++)
		fscanf(fin, "%d", &a[i]);

	sort(a, a + n);

	dijkstra();

	Bignum_t ans = 0;
	for (int i = 0; i < a[0]; i ++)
		ans += calc_valid_state(Bmax, dist[i]) - calc_valid_state(Bmin - 1, dist[i]);

	fprintf(fout, BIGNUM_T_FMT "\n", ans);
}


int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
	fclose(fin);
	fclose(fout);
#endif
}

