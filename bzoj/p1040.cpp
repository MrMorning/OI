#include <cstdio>
#include <cstring>
#include <vector>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef long long val_t;

using std::vector;

const int N_NODE_MAX = 1000000;

struct Node
{
	int w, pre, in_dgr;
	vector<int> son;
};

Node node[N_NODE_MAX];
bool exist[N_NODE_MAX];
int n_vtx;

namespace pre_work
{
	void init();
	void topsort();
	void make_son();
}
namespace tree_dp
{
	val_t f[N_NODE_MAX][2];
	val_t dp(int u, bool c);
}
namespace circle_dp
{
	val_t f[N_NODE_MAX][2];
	int circle[N_NODE_MAX], n_circle;
	val_t work();
}
void pre_work::init()
{
	scanf("%d", &n_vtx);
	for(int i = 0; i < n_vtx; i ++)
	{
		scanf("%d%d", &node[i].w, &node[i].pre);
		node[-- node[i].pre].in_dgr ++;
	}
}
void pre_work::topsort()
{
	static int stack[N_NODE_MAX];
	memset(exist, 1, sizeof(bool) * n_vtx);
	int top = 0;
	for(int i = 0; i < n_vtx; i ++)
		if(node[i].in_dgr == 0)
			stack[top ++] = i;
	while(top)
	{
		int u = stack[-- top];
		exist[u] = false;
		if(-- node[node[u].pre].in_dgr == 0)
			stack[top ++] = node[u].pre;
	}
}

void pre_work::make_son()
{
	for(int i = 0; i < n_vtx; i ++)
		if(! exist[i])
			node[node[i].pre].son.push_back(i);
}

val_t tree_dp::dp(int u, bool c)
{
	static bool f_done[N_NODE_MAX][2];
	if(f_done[u][c])
		return f[u][c];
	f_done[u][c] = true;
	val_t &ret = f[u][c];
	if(c == 0)
	{
		for(int i = 0; i < (int) node[u].son.size(); i ++)
		{
			int v = node[u].son[i];
			ret += MAX(dp(v, 0), dp(v, 1));
		}
	}
	else
	{
		ret = node[u].w;
		for(int i = 0; i < (int) node[u].son.size(); i ++)
		{
			int v = node[u].son[i];
			ret += dp(v, 0);
		}
	}
	return ret;
}
val_t circle_dp::work()
{
	val_t ret = 0;
	for(int i = 0; i < n_vtx; i ++)
	{
		if(exist[i])
		{
			n_circle = 0;
			int u = i;
			while(1)
			{
				circle[n_circle ++] = u;
				exist[u] = false;
				if(node[u].pre == i)
					break;
				u = node[u].pre;
			}
			val_t tmp = 0;

			//do not choose the first item
			f[0][0] = tree_dp::dp(i, 0);
			f[0][1] = 0;
			for(int j = 1; j < n_circle; j ++)
			{
				f[j][0] = tree_dp::dp(circle[j], 0) + MAX(f[j - 1][0], f[j - 1][1]);
				f[j][1] = tree_dp::dp(circle[j], 1) + f[j - 1][0];
			}
			tmp = MAX(tmp, MAX(f[n_circle - 1][0], f[n_circle - 1][1]));

			//choose the first item
			f[0][0] = 0;
			f[0][1] = tree_dp::dp(i, 1);
			for(int j = 1; j < n_circle; j ++)
			{
				f[j][0] = tree_dp::dp(circle[j], 0) + MAX(f[j - 1][0], f[j - 1][1]);
				f[j][1] = tree_dp::dp(circle[j], 1) + f[j - 1][0];
			}
			tmp = MAX(tmp, f[n_circle - 1][0]);

			ret += tmp;
		}
	}
	return ret;
}

int main()
{
	freopen("t.in", "r", stdin);
	pre_work::init();
	pre_work::topsort();
	pre_work::make_son();
	printf("%lld\n", circle_dp::work());
}
