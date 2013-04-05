#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_MAX = 1000010;
const int INFINITY = 0x3f3f3f3f;

struct Event
{
	int val, deadline;
	Event(int _val = 0, int _deadline = 0):
		val(_val), deadline(_deadline){}
	bool operator< (const Event &another) const
	{
		return val > another.val;
	}
};
priority_queue<Event> PQ[2];
vector<Event> cache[N_MAX];
int f[N_MAX], a[N_MAX];
int n;
int solve()
{
	PQ[0].push(Event(INFINITY, n));
	PQ[1].push(Event(INFINITY, n));

	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	int dividor = 0 + 1 + a[1];
	PQ[0].push(Event(dividor, dividor - 1));
	if(dividor <= n)
		cache[dividor].push_back(Event(- dividor, n));

	for(int i = 1; i <= n; i ++)
	{
		for(int j = 0; j < (int) cache[i].size(); j ++)
			PQ[1].push(cache[i][j]);

		Event ev[2];
		while(1)
		{
			ev[0] = PQ[0].top();
			if(ev[0].deadline >= i)
				break;
			PQ[0].pop();
		}
		ev[1] = PQ[1].top();
		for(int t = 0; t < 2; t ++)
			f[i] = MIN(f[i], ev[t].val + (t * 2 - 1) * i);
		int dividor = i + a[i + 1] + 1;
		PQ[0].push(Event(f[i] + dividor, dividor - 1));
		if(dividor <= n)
			cache[dividor].push_back(Event(f[i] - dividor, n));
	}
	return f[n];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	printf("%d\n", solve());
}
