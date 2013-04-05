#include <cstdio>
const int N_MAX = 300010;
const int M_MAX = 10001;
namespace pre_work
{
	int pre[N_MAX];
	int last[M_MAX];
	int data[N_MAX];
	int buf[N_MAX];
	bool hash[M_MAX];
	int begin[M_MAX], end[M_MAX];

	int n_buf, n_data;

	void init();
	int bsearch_not_bigger(int l, int r, int x);
	int bsearch_not_smaller(int l, int r, int x);
	int ask(int l, int r, int x);
}

struct Info
{
	bool e;
	int l, r, x;
	Info(int _l, int _r, int _x):
		l(_l), r(_r), x(_x){e = true;}
	Info(bool _e = true):
		e(_e){}
};

int n_seq, upperlim;
int seq[N_MAX];

Info operator+ (const Info &a, const Info &b)
{
	if(a.e == false)
		return b;
	if(b.e == false)
		return a;
	int len = b.r - a.l + 1;
	if(a.x != -1 && pre_work::ask(a.l, b.r, a.x) > len / 2)
		return Info(a.l, b.r, a.x);
	else if(b.x != -1 && pre_work::ask(a.l, b.r, b.x) > len / 2)
		return Info(a.l, b.r, b.x);
	return Info(a.l, b.r, -1);
}

namespace sgt
{
	struct Node
	{
		int l, r;
		Info info;
	};

	Node node[N_MAX * 4];
	void update(int i);
	void build(int i, int l, int r);
	Info ask(int i, int l, int r);
}

void sgt::update(int i)
{
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
}

void sgt::build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	if(l == r)
		node[i].info = Info(l, r, seq[l]);
	else
	{
		build(i * 2, l, (l + r) / 2);
		build(i * 2 + 1, (l + r) / 2 + 1, r);
		update(i);
	}
}

Info sgt::ask(int i, int l, int r)
{
	Node &x = node[i];
	if(x.l > r || x.r < l)
		return Info(false);
	if(l <= x.l && x.r <= r)
		return x.info;
	return ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
}

void pre_work::init()
{
	for(int i = 1; i <= n_seq; i ++)
	{
		pre[i] = last[seq[i]];
		last[seq[i]] = i;
	}
	for(int i = n_seq; i >= 1; i --)
		if(! hash[seq[i]])
		{
			n_buf = 0;
			hash[seq[i]] = true;
			int u = i;
			while(u)
			{
				buf[++ n_buf] = u;
				u = pre[u];
			}
			for(int j = 1; j <= n_buf; j ++)
				data[n_data + j] = buf[n_buf + 1 - j];
			begin[seq[i]] = n_data + 1;
			end[seq[i]] = n_data + n_buf;
			n_data += n_buf;
		}
}

int pre_work::bsearch_not_bigger(int l, int r, int x)
{
	r += 1;
	int mid = (l + r) >> 1;
	while(l < r - 1)
	{
		if(data[mid] <= x)
			l = mid;
		else
			r = mid;
		mid = (l + r) >> 1;
	}
	return l;
}

int pre_work::bsearch_not_smaller(int l, int r, int x)
{
	l -= 1;
	int mid = (l + r) >> 1;
	while(l + 1 < r)
	{
		if(data[mid] >= x)
			r = mid;
		else
			l = mid;
		mid = (l + r) >> 1;
	}
	return r;
}

int pre_work::ask(int l, int r, int x)
{
	int a = bsearch_not_smaller(begin[x], end[x], l),
		b = bsearch_not_bigger(begin[x], end[x], r);
	return  b >= a ? b - a + 1 : 0;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &n_seq, &upperlim);
	for(int i = 1; i <= n_seq; i ++)
		scanf("%d", &seq[i]);
	pre_work::init();
	sgt::build(1, 1, n_seq);
	int n_query;
	scanf("%d", &n_query);
	while(n_query --)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		Info ret = sgt::ask(1, l, r);
		if(ret.x != -1)
			printf("yes %d\n", ret.x);
		else
			printf("no\n");
	}
}
