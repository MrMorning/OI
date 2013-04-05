#include <cstdio>
#include <vector>
#include <algorithm>
#define FOR(i, l, r) for(int i = (l); i < (r); i ++)
#define REP(i, n) for(int i = 0; i < (n); i ++)
#define ALL(x) (x).begin(), (x).end()
#define pb(t) push_back(t)

using namespace std;

int a[1000], n;
vector<int> b;

inline void change(int i, int t)
{
	a[i] = t;
	b.pb(i);
}

void pushBit(int i)
{
	FOR(p, i, n)
		if(a[p] == 2)
		{
			change(p, 0);
			change(p + 1, a[p + 1] + 1);
			return;
		}
}

int main()
{
	freopen("t.in", "r", stdin);
	int m;
	scanf("%d%d", &n, &m);
	while(m --)
	{
		b.clear();
		int x;
		scanf("%d", &x);
		if(a[x] == 0)
			pushBit(x), change(x, 1);
		else if(a[x] == 1)
		{
			if(x == n - 1)
				change(x, 2);
			else if(a[x + 1] == 0)
				change(x, 0), change(x + 1, 1);
			else if(a[x + 1] == 1)
				pushBit(x), change(x, 0), change(x + 1, 2);
			else
				pushBit(x), change(x, 2);
		}
		else
			pushBit(x), change(x, 1);
		stable_sort(ALL(b));
		vector<int>::iterator it = unique(ALL(b));
		b.resize(it - b.begin());
		printf("%d", b.size());
		REP(i, (int)b.size())
			printf(" %d %d", b[i], a[b[i]]);
		printf("\n");
	}
}
