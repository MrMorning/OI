#include <cstdio>
#include <map>

using namespace std;
typedef pair<int, int> pair_t;
map<pair_t, int> M;
int parent[200000], rank[200000];

int find(int x)
{
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
	int p = find(x), q = find(y);
	if(p == q)
		return;
	if(rank[p] > rank[q])
		swap(p, q);
	parent[p] = q;
	rank[q] ++;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, x1, y1, x2, y2;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		parent[i] = i;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if(x1 == x2 && y1 == y2)
		{
			printf("%d\n", i + 1);
			eturn 0;
		}
		int f1 = -1, f2 = -1;
		pair_t p1 = make_pair(x1, y1),
			   p2 = make_pair(x2, y2);
		if(M.count(p1))
			f1 = M[p1];
		else
			M[p1] = i;
		if(M.count(p2))
			f2 = M[p2];
		else
			M[p2] = i;

		if(f1 == -1 && f2 == -1)
			continue;
		if(f1 != -1 && f2 == -1)
			merge(i, M[p1]);
		else if(f1 == -1 && f2 != -1)
			merge(i, M[p2]);
		else
			if(find(f1) == find(f2))
			{
				printf("%d\n", i + 1);
				return 0;
			}
			else
				merge(f1, f2);
	}
	printf("0\n");
}
