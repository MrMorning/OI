#include <cstdio>
#include <map>
#define MAXN 10050

using std::map;

int n, m;
map<int, int> num_index;
int parent[MAXN], relation[MAXN];
int index = 0;

void Make_Set(int x)
{
	parent[x] = x;
	relation[x] = 0;
}

int Find_Set(int x)
{
	if(x != parent[x])
	{
		int tmp = parent[x];
		parent[x] = Find_Set(parent[x]);
		relation[x] = relation[x] ^ relation[tmp];
	}
	return parent[x];
}

void Union(int x, int y, int d)
{
	int p = Find_Set(x), q = Find_Set(y);
	parent[p] = q;
	relation[p] = relation[x] ^ d ^ relation[y];
}

bool Query(int x, int y, int d)
{
	int p = Find_Set(x), q = Find_Set(y);
	if(p != q)
		Union(x, y, d);
	else
		if(relation[y] != (relation[x] ^ relation[p] ^ d))
			return false;
	return true;
}

int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 1; i <= MAXN; i ++) Make_Set(i);
	scanf("%d\n%d\n",&n,&m);
	int i = 0;
	for(i = 1; i <= m; i ++)
	{
		char ctrl[20];
		int a, a2, b, b2, d;
		scanf("%d %d %s", &a, &b, ctrl);
		if(ctrl[0] == 'e') d = 0;
		else d = 1;
		b ++;
		if(num_index.find(a) == num_index.end())
			num_index[a] = index ++;
		a2 = num_index[a];
		if(num_index.find(b) == num_index.end())
			num_index[b] = index ++;
		b2 = num_index[b];
		if(! Query(a2, b2, d))
			break;
	}
	printf("%d\n", i-1);
}
