#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define MAXN 150010
using std::sort;
using std::priority_queue;
using std::vector;
int n;
struct Stuff
{
	int t1, t2;
	bool operator< (const Stuff &x) const
	{
		return t2 < x.t2 || (t2 == x.t2 && t1 < x.t1);
	}
} stuff[MAXN];

struct cmp
{
	bool operator() (const Stuff &a, const Stuff &b)
	{
		return a.t1 < b.t1;
	}
};

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1, a, b; i <= n; i ++)
	{
		scanf("%d %d\n", &a, &b);
		stuff[i].t1 = a, stuff[i].t2 = b;
	}
	sort(stuff + 1, stuff + n + 1);
	priority_queue<Stuff, vector<Stuff>, cmp> q;
	int end = 0, cnt = 0;
	for(int i = 1; i <= n; i ++)
	{
		if(end + stuff[i].t1 <= stuff[i].t2)
			q.push(stuff[i]), cnt ++, end += stuff[i].t1;
		else
		{
			Stuff tmp = q.top();
			if(tmp.t1 > stuff[i].t1)
				q.pop(), q.push(stuff[i]), end -= tmp.t1 - stuff[i].t1;
		}
	}
	printf("%d\n", cnt);
}
