#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pair_t;

const int N_MAX = 15100;
const int oo = 0x3f3f3f3f;

int n, W[N_MAX], L[N_MAX], P[N_MAX], sum[N_MAX];
bool used[N_MAX];
struct cmp
{
	bool operator() (const int &a, const int &b)
	{
		return L[a] > L[b];
	}
};
priority_queue<int, vector<int>, cmp> PQ;

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d%d", &W[i], &L[i], &P[i]);
	int res = 0;
	int ans = oo;
	int best = -1;
	for(int i = n - 1; i >= 0; i --)
	{
		sum[i] = sum[i + 1] + W[i];
		PQ.push(i);
		res += P[i];
		while(!PQ.empty())
		{
			int x = PQ.top();
			if(L[x] >= sum[i] - sum[x + 1])
				break;
			res -= P[x];
			PQ.pop();
		}
		if(res < ans)
			best = i, ans = res;
	}

	while(!PQ.empty())
		PQ.pop();
	res = 0;
	for(int i = n - 1; i >= best; i --)
	{
		res += P[i];
		used[i] = true;
		PQ.push(i);
		while(!PQ.empty())
		{
			int x = PQ.top();
			if(L[x] >= sum[i] - sum[x + 1])
				break;
			used[x] = false;
			res -= P[x];
			PQ.pop();
		}
	}
//	printf("%d\n", ans);
	for(int i = 0; i < n; i ++)
		if(used[i])
			printf("%d\n", i + 1);
}
