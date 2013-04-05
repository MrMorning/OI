#include <cstdio>
#include <algorithm>
using namespace std;

const int N_MAX = 50010;

struct Info
{
	int minVal, maxVal;
	bool e;
	Info(bool _e = true):
		e(_e){}
};

Info operator+ (const Info &I1, const Info &I2)
{
	if(!I1.e) return I2;
	if(!I2.e) return I1;
	Info ret;
	ret.minVal = min(I1.minVal, I2.minVal);
	ret.maxVal = max(I1.maxVal, I2.maxVal);
	return ret;
}

struct Node
{
	int l, r;
	Info info;
};

Node node[N_MAX * 4];
int data[N_MAX];

void update(int i)
{
	node[i].info = node[i * 2].info + node[i * 2 + 1].info;
}

void build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	if(l == r)
		node[i].info.minVal = node[i].info.maxVal = data[l];
	else
	{
		int mid = (l + r) / 2;
		build(i * 2, l, mid);
		build(i * 2 + 1, mid + 1, r);
		update(i);
	}
}

Info ask(int i, int a, int b)
{
	if(node[i].l > b || node[i].r < a)
		return Info(false);
	if(a <= node[i].l && node[i].r <= b)
		return node[i].info;
	return ask(i * 2, a, b) + ask(i * 2 + 1, a, b);
}

int main()
{
	int n, m, a, b;
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
		scanf("%d", &data[i]);
	build(1, 0, n - 1);
	while(m --)
	{
		scanf("%d%d", &a, &b);
		a --, b --;
		Info info = ask(1, a, b);
		printf("%d\n", info.maxVal - info.minVal);
	}
}
