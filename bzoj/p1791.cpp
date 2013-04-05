#include <cstdio>
#include <cstring>

typedef long long bignum_t;

inline bignum_t MAX(bignum_t a, bignum_t b)
{
	return a > b ? a : b;
}

const int N_VTX_MAX = 1000010;
const int N_EDGE_MAX = N_VTX_MAX * 2;

struct Edge
{
	int vtx, dist;
	Edge *next, *inverse;
};

struct MonoQueue
{
	int head, tail;
	int queue_time[N_VTX_MAX];
	bignum_t queue_val[N_VTX_MAX];
	MonoQueue()
	{
		head = tail = 0;
	}
	void push(int i, bignum_t val)
	{
		while(head < tail && queue_val[tail - 1] <= val)
			tail --;
		queue_val[tail] = val;
		queue_time[tail] = i;
		tail ++;
	}
	bignum_t get_max()
	{
		if(head == tail)
			return - 0x3f3f3f3f;
		else
			return queue_val[head];
	}
	void update(int i)
	{
		while(head < tail && queue_time[head] < i)
			head ++;
	}
};

int n_edge, n_vtx;
Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
bool exist[N_VTX_MAX];
int dgr[N_VTX_MAX], cycle[N_VTX_MAX];
bignum_t f[N_VTX_MAX], pre_sum[N_VTX_MAX];
bignum_t ans;

Edge *make_edge(int u, int v, int dist)
{
	Edge *e = &edge[n_edge ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
	e->dist = dist;
	return e;
}

void add_edge(int u, int v, int dist)
{
	Edge *e1 = make_edge(u, v, dist),
		 *e2 = make_edge(v, u, dist);
	e1->inverse = e2, e2->inverse = e1;
}
void read_data()
{
	scanf("%d", &n_vtx);
	for(int i = 0, u, l; i < n_vtx; i ++)
	{
		scanf("%d%d", &u, &l);
		u --;
		dgr[i] ++, dgr[u] ++;
		add_edge(u, i, l);
	}
}
void topsort()
{
	static int stack[N_VTX_MAX];
	memset(exist, -1, sizeof(bool) * n_vtx);
	int top = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(dgr[i] == 1)
			stack[top ++] = i;
	while(top)
	{
		int u = stack[-- top];
		exist[u] = false;
		for(Edge *e = begin[u]; e; e = e->next)
		{
			int v = e->vtx;
			if(exist[v])
			{
				dgr[v] --;
				if(dgr[v] == 1)
					stack[top ++] = v;
			}
		}
	}
}
bignum_t dp(int u, int p)
{
	static bool f_done[N_VTX_MAX];
	if(f_done[u])
		return f[u];
	f_done[u] = true;
	bignum_t &ret = f[u] = 0;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(exist[v] || v == p)
			continue;
		ans = MAX(ans, dp(v, u) + e->dist + f[u]);
		ret = MAX(ret, dp(v, u) + e->dist);
	}
	return ret;
}
void work_on_cycle(int n, bignum_t sum)
{
	bignum_t ret = 0;
	static MonoQueue MQ;
	MQ.head = MQ.tail = 0;
	for(int i = 0, j = -1; i < n; i ++)
	{
		while(pre_sum[j + 1] < pre_sum[i] - sum / 2)
			j ++;
		MQ.update(j);
		ret = MAX(ret, MQ.get_max() + dp(cycle[i], -1) - pre_sum[i] + sum);
		MQ.push(i, dp(cycle[i], -1) + pre_sum[i]);
	}
	MQ.head = MQ.tail = 0;
	for(int i = 0, j = -1; i < n; i ++)
	{
		while(pre_sum[j + 1] < pre_sum[i] - sum / 2)
		{
			j ++;
			MQ.push(j, dp(cycle[j], -1) - pre_sum[j]);
		}
		ret = MAX(ret, MQ.get_max() + dp(cycle[i], -1) + pre_sum[i]);
	}
	ans = MAX(ret, ans);
}
bignum_t solve()
{
	bignum_t ret = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(exist[i])
		{
			ans = 0;
			int u = i;
			Edge *pre = NULL;
			int cycle_cnt = 0;
			bignum_t sum = 0;
			while(1)
			{
				Edge *e;
				for(e = begin[u]; e; e = e->next)
					if(exist[e->vtx] && (! pre || e != pre->inverse))
						break;
				cycle[cycle_cnt] = e->vtx;
				sum += e->dist;
				if(cycle_cnt)
					pre_sum[cycle_cnt] = pre_sum[cycle_cnt - 1] + e->dist;
				else
					pre_sum[0] = 0;
				cycle_cnt ++;
				pre = e;
				u = e->vtx;
				if(u == i)
					break;
			}
			work_on_cycle(cycle_cnt, sum);
			ret += ans;
			for(int i = 0; i < cycle_cnt; i ++)
				exist[cycle[i]] = false;
		}
	return ret;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	read_data();
	topsort();
	printf("%I64d\n", solve());
}
