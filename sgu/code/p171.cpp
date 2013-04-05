#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, ans[16001];
struct Zone
{
	int idx, level, cap;
	bool operator< (const Zone &t) const
	{
		return level < t.level;
	}
} Z[101];

struct Student
{
	int idx, level, weight;
	bool operator< (const Student &t) const
	{
		return weight < t.weight;
	}
} S[16001];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++)
	{
		Z[i].idx = i;
		scanf("%d", &Z[i].cap);
		n += Z[i].cap;
	}
	for(int i = 1; i <= m; i ++)
		scanf("%d", &Z[i].level);
	sort(Z + 1, Z + 1 + m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &S[i].level);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &S[i].weight);
	for(int i = 1; i <= n; i ++)
		S[i].idx = i;
	sort(S + 1, S + 1 + n);
	for(int i = n; i >= 1; i --)
	{
		int j;
		for(j = m; j >= 1; j --)
			if(S[i].level> Z[j].level && Z[j].cap)
				break;
		if(j)
			Z[j].cap --, ans[S[i].idx] = Z[j].idx;
		else
			ans[S[i].idx] = 0;
	}
	int top = 1;
	while(Z[top].cap == 0) top ++;
	for(int i = 1; i <= n; i ++)
		if(ans[i])
			printf("%d ", ans[i]);
		else
		{
			printf("%d ", Z[top].idx);
			Z[top].cap --;
			while(Z[top].cap == 0) top ++;
		}
}
