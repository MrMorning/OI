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
inline int abs(int x)
{
	return x < 0 ? -x : x;
}
int bruce()
{
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 0; j < i; j ++)
			f[i]  = MIN(f[i], f[j] + abs(i - j - 1 - a[j + 1]));
	return f[n];
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	printf("%d\n", bruce());
}
